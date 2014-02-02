/// \file process/sub/posix/src/daemonization_resources.cpp 
/// \brief POSIX daemonization resources implementation.
/// \ingroup sheratan_process_posix
/// \author Marek Balint \c (mareq[A]balint[D]eu)


// pipe(2): http://pubs.opengroup.org/onlinepubs/009695399/functions/pipe.html
// sigemptyset(2): http://pubs.opengroup.org/onlinepubs/009695399/functions/sigemptyset.html
// sigaction(2): http://pubs.opengroup.org/onlinepubs/009695399/functions/sigaction.html
// getrlimit(2): http://pubs.opengroup.org/onlinepubs/009695399/functions/getrlimit.html
// setsid(2): http://pubs.opengroup.org/onlinepubs/009695399/functions/setsid.html
// umask(2): http://pubs.opengroup.org/onlinepubs/009695399/functions/umask.html
// chdir(2): http://pubs.opengroup.org/onlinepubs/009695399/functions/chdir.html
// close(2): http://pubs.opengroup.org/onlinepubs/009695399/functions/close.html
// open(2): http://pubs.opengroup.org/onlinepubs/009695399/functions/open.html
// dup2(2): http://pubs.opengroup.org/onlinepubs/009695399/functions/dup2.html 
// fcntl(2): http://pubs.opengroup.org/onlinepubs/009695399/functions/fcntl.html
// ftruncate(2): http://pubs.opengroup.org/onlinepubs/009695399/functions/ftruncate.html


#include <cerrno>
#include <cstdlib>
#include <cstdio>

#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "sheratan/errhdl/assert.hpp"
#include "sheratan/errhdl/throw.hpp"
#include "sheratan/errhdl/default_category.hpp"
#include "sheratan/process/posix/error_category.hpp"
#include "daemonization_resources.hpp"


namespace sheratan {

namespace process_impl {

namespace posix {


/// \def NSIG
/// \brief Number of signals defined by the system.
# ifndef NSIG
#   ifdef _NSIG
#     define NSIG _NSIG
#   else
#     define NSIG 32
#   endif
# endif


daemonization_resources::daemonization_resources()
: daemon_ctl_()
, pid_file_()
, pid_file_mode_()
, working_dir_()
, stdin_redirect_()
, stdout_redirect_()
, stderr_redirect_()
, reset_signals_flag_()
, daemon_pid_()
, rc_pipe_r_()
, rc_pipe_w_()
{
  /// \todo Old versions of Boost does not define <code>boost::array::fill</code>
  /// method. Now deprecated method <code>boost::array::assign</code>
  /// needs to be used in old version.
  this->rc_pipe_r_.fill(NULL);
  this->rc_pipe_w_.fill(NULL);
}

daemonization_resources::daemonization_resources(
  const daemon_ctl &dc,
  const daemonizer::pid_file_type &pid_file,
  const daemonizer::pid_file_mode_type &pid_file_mode,
  const daemonizer::working_dir_type &working_dir,
  const daemonizer::stdin_redirect_type &stdin_redirect,
  const daemonizer::stdout_redirect_type &stdout_redirect,
  const daemonizer::stderr_redirect_type &stderr_redirect,
  const daemonizer::reset_signals_flag_type &reset_signals_flag
)
: daemon_ctl_(dc.clone())
, pid_file_(pid_file)
, pid_file_mode_(pid_file_mode)
, working_dir_(working_dir)
, stdin_redirect_(stdin_redirect)
, stdout_redirect_(stdout_redirect)
, stderr_redirect_(stderr_redirect)
, reset_signals_flag_(reset_signals_flag)
, daemon_pid_()
, rc_pipe_r_()
, rc_pipe_w_()
, filedescs_rlimit_()
, signal_dispositions_()
{
  std::memset(&(this->filedescs_rlimit_), 0, sizeof(this->filedescs_rlimit_));

  if(!this->reset_signals_flag_) {
    this->signal_dispositions_.reserve(NSIG);
  }
}

daemonization_resources::~daemonization_resources()
{
  this->finalize();
}

void daemonization_resources::finalize()
{
  this->close_rc_pipe(daemonization_resources::pipe_id::CHILD, daemonization_resources::pipe_end::READ);
  this->close_rc_pipe(daemonization_resources::pipe_id::CHILD, daemonization_resources::pipe_end::WRITE);
  this->close_rc_pipe(daemonization_resources::pipe_id::DAEMON, daemonization_resources::pipe_end::READ);
  this->close_rc_pipe(daemonization_resources::pipe_id::DAEMON, daemonization_resources::pipe_end::WRITE);
  this->restore_signal_dispositions(false); // forbid throwing exceptions from restore_signal_dispositions method
}

const daemon_ctl & daemonization_resources::get_daemon_ctl() const
{
  SHERATAN_CHECK(this->daemon_ctl_.get() != NULL);

  return *this->daemon_ctl_;
}

daemon_ctl & daemonization_resources::get_daemon_ctl()
{
  SHERATAN_CHECK(this->daemon_ctl_.get() != NULL);

  return *this->daemon_ctl_;
}

void daemonization_resources::create_rc_pipe(daemonization_resources::pipe_id::value_type pipe_id)
{
  SHERATAN_CHECK(pipe_id < daemonization_resources::pipe_id::COUNT);
  SHERATAN_CHECK(this->rc_pipe_r_[pipe_id] == NULL);
  SHERATAN_CHECK(this->rc_pipe_w_[pipe_id] == NULL);

  int saved_errnum = 0;
  int rc_pipe_fd[2] = {-1, -1};

  // create rc-pipe
  if(::pipe(rc_pipe_fd) != 0) {
    saved_errnum = errno;
    goto error;
  }
  this->rc_pipe_r_[pipe_id] = ::fdopen(rc_pipe_fd[0], "r");
  if(this->rc_pipe_r_[pipe_id] == NULL) {
    saved_errnum = errno;
    goto error;
  }
  this->rc_pipe_w_[pipe_id] = ::fdopen(rc_pipe_fd[1], "w");
  if(this->rc_pipe_w_[pipe_id] == NULL) {
    saved_errnum = errno;
    goto error;
  }

  // successful return
  return;

  // ERROR HANDLING
  error:

  // free all possibly allocated resources
  if((this->rc_pipe_r_[pipe_id] == NULL) && (rc_pipe_fd[0] != -1)) {
    ::close(rc_pipe_fd[0]);
  }
  if((this->rc_pipe_w_[pipe_id] == NULL) && (rc_pipe_fd[1] != -1)) {
    ::close(rc_pipe_fd[1]);
  }
  this->close_rc_pipe(pipe_id, daemonization_resources::pipe_end::READ);
  this->close_rc_pipe(pipe_id, daemonization_resources::pipe_end::WRITE);

  // throw exception
  sheratan::errhdl::runtime_error ex_to_throw;
  ex_to_throw << error_category::error_info::posix_errnum(saved_errnum);
  SHERATAN_THROW_EXCEPTION(ex_to_throw, sheratan::errhdl::error_code(errnum::POSIX_SYSTEM, get_error_category()));
}

void daemonization_resources::close_rc_pipe(daemonization_resources::pipe_id::value_type pipe_id, daemonization_resources::pipe_end::value_type pipe_end)
{
  SHERATAN_CHECK(pipe_id < daemonization_resources::pipe_id::COUNT);

  switch(pipe_end) {
    case daemonization_resources::pipe_end::READ:
      if(this->rc_pipe_r_[pipe_id] != NULL) {
        std::fclose(this->rc_pipe_r_[pipe_id]);
        this->rc_pipe_r_[pipe_id] = NULL;
      }
      break;
    case daemonization_resources::pipe_end::WRITE:
      if(this->rc_pipe_w_[pipe_id] != NULL) {
        std::fclose(this->rc_pipe_w_[pipe_id]);
        this->rc_pipe_w_[pipe_id] = NULL;
      }
      break;
  }
}


namespace {


/// \brief Map of file descriptor redirection (pairs <path, file descriptor>) type definition.
typedef std::map<std::string, int> redirection_map_type;


/// \brief Redirect file descriptor to newly opened file on specified path.
/// \param fd File descriptor to be redirected.
/// \param path Path to redirect to.
/// \param redirection_map Map of already redirected file descriptors.
/// \par Abrahams exception guarantee:
/// weak
/// \pre Redirection path must be existing, valid and accessible.
static void redirect_file_descriptor(int fd, const std::string &path, redirection_map_type redirection_map)
{
  redirection_map_type::const_iterator i = redirection_map.find(path);
  if(i == redirection_map.end()) {
    int retval = ::open(path.c_str(), O_RDWR);
    if(retval < 0) {
      int saved_errnum = errno;
      sheratan::errhdl::runtime_error ex_to_throw;
      ex_to_throw << error_category::error_info::posix_errnum(saved_errnum);
      SHERATAN_THROW_EXCEPTION(ex_to_throw, sheratan::errhdl::error_code(errnum::POSIX_SYSTEM, get_error_category()));
    }
    SHERATAN_CHECK(retval != STDIN_FILENO);
    SHERATAN_CHECK(retval != STDOUT_FILENO);
    SHERATAN_CHECK(retval != STDERR_FILENO);
    std::pair<redirection_map_type::const_iterator, bool> rc = redirection_map.insert(redirection_map_type::value_type(path, retval));
    SHERATAN_CHECK(rc.second == true);
    i = rc.first;
  }
  int retval = ::dup2(i->second, fd);
  if(retval < 0) {
    int saved_errnum = errno;
    sheratan::errhdl::runtime_error ex_to_throw;
    ex_to_throw << error_category::error_info::posix_errnum(saved_errnum);
    SHERATAN_THROW_EXCEPTION(ex_to_throw, sheratan::errhdl::error_code(errnum::POSIX_SYSTEM, get_error_category()));
  }
  SHERATAN_CHECK(retval == fd);
}


} // anonymous namespace


void daemonization_resources::daemon_init_parent()
{
  // ignore all signals
  struct sigaction signal_sigaction;
  if(::sigemptyset(&signal_sigaction.sa_mask) != 0) {
    int saved_errnum = errno;
    sheratan::errhdl::runtime_error ex_to_throw;
    ex_to_throw << error_category::error_info::posix_errnum(saved_errnum);
    SHERATAN_THROW_EXCEPTION(ex_to_throw, sheratan::errhdl::error_code(errnum::POSIX_SYSTEM, get_error_category()));
  }
  signal_sigaction.sa_flags = 0;
  for(signal_number_type i = 1; i < NSIG; ++i) {
    if((i == SIGKILL) || (i == SIGSTOP)) {
      continue;
    }
    if(i == SIGCHLD) {
      // For SIGCHLD, default action is ignore, but explicitly setting SIG_IGN
      // will change behavior of waitpid, which is not desirable (in fact, daemonization
      // algorithm relies on default waitpid's behavior, which must not be changed)
      signal_sigaction.sa_handler = SIG_DFL;
    }
    else {
      signal_sigaction.sa_handler = SIG_IGN;
    }
    daemonization_resources::signal_disposition original_disposition;
    int retval = ::sigaction(i, &signal_sigaction, &(original_disposition.signal_sigaction));
    // retpor invalid signal number error only for standard POSIX signals
    if((retval != 0) && ((i < 32) || (errno != EINVAL))) {
      int saved_errnum = errno;
      sheratan::errhdl::runtime_error ex_to_throw;
      ex_to_throw << error_category::error_info::posix_errnum(saved_errnum);
      SHERATAN_THROW_EXCEPTION(ex_to_throw, sheratan::errhdl::error_code(errnum::POSIX_SYSTEM, get_error_category()));
    }
    original_disposition.signal_number = i;
    this->signal_dispositions_.push_back(original_disposition);
  }

  // get maximum number of file descriptors
  if(::getrlimit(RLIMIT_NOFILE, &(this->filedescs_rlimit_)) != 0) {
    int saved_errnum = errno;
    sheratan::errhdl::runtime_error ex_to_throw;
    ex_to_throw << error_category::error_info::posix_errnum(saved_errnum);
    SHERATAN_THROW_EXCEPTION(ex_to_throw, sheratan::errhdl::error_code(errnum::POSIX_SYSTEM, get_error_category()));
  }
  if(this->filedescs_rlimit_.rlim_max == RLIM_INFINITY) {
    this->filedescs_rlimit_.rlim_max = 1024;
  }
}

void daemonization_resources::daemon_init_child()
{
  // become a session leader to lose controlling tty
  if(::setsid() == static_cast<pid_t>(-1)) {
    int saved_errnum = errno;
    sheratan::errhdl::runtime_error ex_to_throw;
    ex_to_throw << error_category::error_info::posix_errnum(saved_errnum);
    SHERATAN_THROW_EXCEPTION(ex_to_throw, sheratan::errhdl::error_code(errnum::POSIX_SYSTEM, get_error_category()));
  }
}

void daemonization_resources::daemon_init_daemon(const daemonization_resources::fd_list_type &excluded_fds)
{
  // clear file creation mask
  ::umask(0);

  // set working directory
  if(this->working_dir_ != daemonizer::working_dir_type().get_value()) {
    if(::chdir(this->working_dir_.c_str()) != 0) {
      int saved_errnum = errno;
      sheratan::errhdl::runtime_error ex_to_throw;
      ex_to_throw << error_category::error_info::posix_errnum(saved_errnum);
      SHERATAN_THROW_EXCEPTION(ex_to_throw, sheratan::errhdl::error_code(errnum::POSIX_SYSTEM, get_error_category()));
    }
  }

  // close all file descriptors
  int filedescs_max = static_cast<int>(this->filedescs_rlimit_.rlim_max);
  daemonization_resources::fd_list_type exclusion_list(excluded_fds);
  exclusion_list.push_back(STDIN_FILENO);
  exclusion_list.push_back(STDOUT_FILENO);
  exclusion_list.push_back(STDERR_FILENO);
  for(size_t i = 0; i < daemonization_resources::pipe_id::COUNT; ++i) {
    if(this->rc_pipe_r_[i] != NULL) {
      exclusion_list.push_back(::fileno(this->rc_pipe_r_[i]));
    }
    if(this->rc_pipe_w_[i] != NULL) {
      exclusion_list.push_back(::fileno(this->rc_pipe_w_[i]));
    }
  }
  daemonization_resources::fd_list_type::const_iterator begin = exclusion_list.begin();
  daemonization_resources::fd_list_type::const_iterator end = exclusion_list.end();
  for(int fd = 0; fd < filedescs_max; ++fd) {
    // skip file descriptors from exclusion list
    if(std::find(begin, end, fd) != end) {
      continue;
    }
    // close file descriptor
    if(::close(fd) != 0) {
      int saved_errnum = errno;
      if(saved_errnum != EBADF) {
        sheratan::errhdl::runtime_error ex_to_throw;
        ex_to_throw << error_category::error_info::posix_errnum(saved_errnum);
        SHERATAN_THROW_EXCEPTION(ex_to_throw, sheratan::errhdl::error_code(errnum::POSIX_SYSTEM, get_error_category()));
      }
    }
  }

  // redirect standard I/O streams
  redirection_map_type redirection_map;
  if(this->stdin_redirect_ != daemonizer::stdin_redirect_type().get_value()) {
    redirect_file_descriptor(STDIN_FILENO, this->stdin_redirect_, redirection_map);
  }
  if(this->stdout_redirect_ != daemonizer::stdin_redirect_type().get_value()) {
    redirect_file_descriptor(STDOUT_FILENO, this->stdout_redirect_, redirection_map);
  }
  if(this->stderr_redirect_ != daemonizer::stderr_redirect_type().get_value()) {
    redirect_file_descriptor(STDERR_FILENO, this->stderr_redirect_, redirection_map);
  }


  // acquire PID file and write daemon's PID into it
  if(this->pid_file_ != daemonizer::pid_file_type().get_value()) {
    int pidfile_fd = ::open(this->pid_file_.c_str(), O_RDWR|O_CREAT, this->pid_file_mode_);
    if(pidfile_fd < 0) {
      int saved_errnum = errno;
      sheratan::errhdl::runtime_error ex_to_throw;
      ex_to_throw << error_category::error_info::posix_errnum(saved_errnum);
      SHERATAN_THROW_EXCEPTION(ex_to_throw, sheratan::errhdl::error_code(errnum::POSIX_SYSTEM, get_error_category()));
    }
    FILE *pidfile_fp = ::fdopen(pidfile_fd, "r+");
    if(pidfile_fp == NULL) {
      int saved_errnum = errno;
      sheratan::errhdl::runtime_error ex_to_throw;
      ex_to_throw << error_category::error_info::posix_errnum(saved_errnum);
      SHERATAN_THROW_EXCEPTION(ex_to_throw, sheratan::errhdl::error_code(errnum::POSIX_SYSTEM, get_error_category()));
    }
    struct flock pidfile_flock;
    pidfile_flock.l_type = F_WRLCK;
    pidfile_flock.l_start = 0;
    pidfile_flock.l_whence = SEEK_SET;
    pidfile_flock.l_len = 0;
    pidfile_flock.l_pid = 0;
    if(::fcntl(pidfile_fd, F_SETLK, &pidfile_flock) != 0) {
      SHERATAN_THROW_EXCEPTION(sheratan::errhdl::runtime_error(), sheratan::errhdl::error_code(errnum::PIDFILE_LOCKED, get_error_category()));
    }
    if(::ftruncate(pidfile_fd, 0) != 0) {
      int saved_errnum = errno;
      sheratan::errhdl::runtime_error ex_to_throw;
      ex_to_throw << error_category::error_info::posix_errnum(saved_errnum);
      SHERATAN_THROW_EXCEPTION(ex_to_throw, sheratan::errhdl::error_code(errnum::POSIX_SYSTEM, get_error_category()));
    }
    errno = 0;
    if(std::fprintf(pidfile_fp, "%d\n", ::getpid()) < 0) {
      int saved_errnum = errno;
      sheratan::errhdl::runtime_error ex_to_throw;
      ex_to_throw << error_category::error_info::posix_errnum(saved_errnum);
      SHERATAN_THROW_EXCEPTION(ex_to_throw, sheratan::errhdl::error_code(errnum::POSIX_SYSTEM, get_error_category()));
    }
    if(std::fflush(pidfile_fp) != 0) {
      int saved_errnum = errno;
      sheratan::errhdl::runtime_error ex_to_throw;
      ex_to_throw << error_category::error_info::posix_errnum(saved_errnum);
      SHERATAN_THROW_EXCEPTION(ex_to_throw, sheratan::errhdl::error_code(errnum::POSIX_SYSTEM, get_error_category()));
    }
  }

  // set default signal dispositions or restore original signal dispositions
  if(this->reset_signals_flag_) {
    struct sigaction default_disposition;
    default_disposition.sa_handler = SIG_DFL;
    if(sigemptyset(&default_disposition.sa_mask) != 0) {
      int saved_errnum = errno;
      sheratan::errhdl::runtime_error ex_to_throw;
      ex_to_throw << error_category::error_info::posix_errnum(saved_errnum);
      SHERATAN_THROW_EXCEPTION(ex_to_throw, sheratan::errhdl::error_code(errnum::POSIX_SYSTEM, get_error_category()));
    }
    default_disposition.sa_flags = 0;
    for(signal_number_type i = 1; i < NSIG; ++i) {
      if((i == SIGKILL) || (i == SIGSTOP)) {
        continue;
      }
      int retval = sigaction(i, &default_disposition, NULL);
      if((retval != 0) && (i < 32)) {  // report error only for standard POSIX signals
        int saved_errnum = errno;
        sheratan::errhdl::runtime_error ex_to_throw;
        ex_to_throw << error_category::error_info::posix_errnum(saved_errnum);
        SHERATAN_THROW_EXCEPTION(ex_to_throw, sheratan::errhdl::error_code(errnum::POSIX_SYSTEM, get_error_category()));
      }
    }
  }
  else {
    this->restore_signal_dispositions();
  }
}


namespace {


/// \brief Return code pipe tag type definition.
typedef char rc_pipe_tag_type;

/// \brief Return code pipe PID tag.
static const rc_pipe_tag_type rc_pipe_pid_tag = 42;

/// \brief Return code pipe exception tag.
static const rc_pipe_tag_type rc_pipe_ex_tag = 23;

/// \brief Return code pipe exception type.
/// \ingroup sheratan_process_posix
/// \nosubgrouping
struct rc_pipe_extype
{
  /// \brief Return code pipe exception type values.
  typedef enum
  {
    LOGIC_ERROR    = 0,  ///< Sheratan logic error.
    RUNTIME_ERROR  = 1   ///< Sheratan runtime error.
  } value_type;
};

/// \brief Return code pipe exception category.
/// \ingroup sheratan_process_posix
/// \nosubgrouping
struct rc_pipe_excategory
{
  /// \brief Return code pipe exception category values.
  typedef enum
  {
    UNKNOWN = 0,  ///< Unknown/other exception category.
    ASSERT  = 1,  ///< Assert exception category.
    PROCESS = 2   ///< POSIX Process exception category.
  } value_type;
};


/// \brief Write exception into the file.
/// \param fd File descriptor to be written to.
/// \param ex Exception to be written.
/// \param extype Exception type.
/// \par Abrahams exception guarantee:
/// no-throw
static void write_ex(FILE *fd, const sheratan::errhdl::exception &ex, rc_pipe_extype::value_type extype)
{
  std::fwrite(&rc_pipe_ex_tag, sizeof(rc_pipe_ex_tag), 1, fd);

  std::fwrite(&extype, sizeof(extype), 1, fd);

  bool is_assert_ex = (get_code(ex).get_category() == sheratan::errhdl::get_assert_category());
  bool is_process_ex = (get_code(ex).get_category() == sheratan::process_impl::posix::get_error_category());
  rc_pipe_excategory::value_type excategory = rc_pipe_excategory::UNKNOWN;
  if(is_assert_ex) {
    excategory = rc_pipe_excategory::ASSERT;
  }
  else if(is_process_ex) {
    excategory = rc_pipe_excategory::PROCESS;
  }
  errno = 0;
  std::fwrite(&excategory, sizeof(excategory), 1, fd);

  sheratan::errhdl::error_category::errnum_type en = get_code(ex).get_errnum();
  std::fwrite(&en, sizeof(en), 1, fd);

  if(is_process_ex) {
    switch(static_cast<errnum::value_type>(en)) {
      case errnum::POSIX_SYSTEM:
      {
        error_category::error_info::posix_errnum_type posix_en = get_posix_errnum(ex);
        std::fwrite(&posix_en, sizeof(posix_en), 1, fd);
        break;
      }
      case errnum::BOOST_SYSTEM:
      {
        error_category::error_info::boost_errnum_type boost_en = get_boost_errnum(ex);
        std::fwrite(&boost_en, sizeof(boost_en), 1, fd);
        break;
      }
      case errnum::UNKNOWN:
      case errnum::DAEMON_ERROR:
      case errnum::PIDFILE_LOCKED:
      {
        // nothing to do
        break;
      }
    }
  }

  sheratan::errhdl::error_info::line_type l = get_line(ex);
  std::fwrite(&l, sizeof(l), 1, fd);

  sheratan::errhdl::error_info::seconds_type s = get_seconds(ex);
  std::fwrite(&s, sizeof(s), 1, fd);

  sheratan::errhdl::error_info::useconds_type u = get_useconds(ex);
  std::fwrite(&u, sizeof(u), 1, fd);
}


} // anonymous namespace


void daemonization_resources::report_pid(daemonization_resources::pipe_id::value_type pipe_id, const process_id::value_type &pid)
{
  SHERATAN_CHECK(pipe_id < daemonization_resources::pipe_id::COUNT);
  SHERATAN_CHECK(this->rc_pipe_w_[pipe_id] != NULL);

  errno = 0;
  if(std::fwrite(&rc_pipe_pid_tag, sizeof(rc_pipe_pid_tag), 1, this->rc_pipe_w_[pipe_id]) != 1) {
    int saved_errnum = errno;
    sheratan::errhdl::runtime_error ex_to_throw;
    ex_to_throw << error_category::error_info::posix_errnum(saved_errnum);
    SHERATAN_THROW_EXCEPTION(ex_to_throw, sheratan::errhdl::error_code(errnum::POSIX_SYSTEM, get_error_category()));
  }

  errno = 0;
  if(std::fwrite(&pid, sizeof(pid), 1, this->rc_pipe_w_[pipe_id]) != 1) {
    int saved_errnum = errno;
    sheratan::errhdl::runtime_error ex_to_throw;
    ex_to_throw << error_category::error_info::posix_errnum(saved_errnum);
    SHERATAN_THROW_EXCEPTION(ex_to_throw, sheratan::errhdl::error_code(errnum::POSIX_SYSTEM, get_error_category()));
  }
}

void daemonization_resources::retrieve_daemon_pid(daemonization_resources::pipe_id::value_type pipe_id)
{
  SHERATAN_CHECK(pipe_id < daemonization_resources::pipe_id::COUNT);
  SHERATAN_CHECK(this->rc_pipe_r_[pipe_id] != NULL);

  rc_pipe_tag_type pid_tag;
  errno = 0;
  if(std::fread(&pid_tag, sizeof(pid_tag), 1, this->rc_pipe_r_[pipe_id]) != 1) {
    int saved_errnum = errno;
    sheratan::errhdl::runtime_error ex_to_throw;
    ex_to_throw << error_category::error_info::posix_errnum(saved_errnum);
    SHERATAN_THROW_EXCEPTION(ex_to_throw, sheratan::errhdl::error_code(errnum::POSIX_SYSTEM, get_error_category()));
  }
  SHERATAN_CHECK(pid_tag == rc_pipe_pid_tag);

  process_id::value_type pid;
  errno = 0;
  if(std::fread(&pid, sizeof(pid), 1, this->rc_pipe_r_[pipe_id]) != 1) {
    int saved_errnum = errno;
    sheratan::errhdl::runtime_error ex_to_throw;
    ex_to_throw << error_category::error_info::posix_errnum(saved_errnum);
    SHERATAN_THROW_EXCEPTION(ex_to_throw, sheratan::errhdl::error_code(errnum::POSIX_SYSTEM, get_error_category()));
  }

  this->daemon_pid_ = pid;
}

process_id::value_type daemonization_resources::get_daemon_pid() const
{
  return this->daemon_pid_;
}

void daemonization_resources::report_ex(daemonization_resources::pipe_id::value_type pipe_id, const sheratan::errhdl::logic_error &ex)
{
  SHERATAN_CHECK(pipe_id < daemonization_resources::pipe_id::COUNT);
  SHERATAN_CHECK(this->rc_pipe_w_[pipe_id] != NULL);

  write_ex(this->rc_pipe_w_[pipe_id], ex, rc_pipe_extype::LOGIC_ERROR);
}

void daemonization_resources::report_ex(daemonization_resources::pipe_id::value_type pipe_id, const sheratan::errhdl::runtime_error &ex)
{
  SHERATAN_CHECK(pipe_id < daemonization_resources::pipe_id::COUNT);
  SHERATAN_CHECK(this->rc_pipe_w_[pipe_id] != NULL);

  write_ex(this->rc_pipe_w_[pipe_id], ex, rc_pipe_extype::RUNTIME_ERROR);
}

void daemonization_resources::report_unknown_ex(daemonization_resources::pipe_id::value_type pipe_id)
{
  SHERATAN_CHECK(pipe_id < daemonization_resources::pipe_id::COUNT);
  SHERATAN_CHECK(this->rc_pipe_w_[pipe_id] != NULL);

  sheratan::errhdl::runtime_error ex_to_report;
  sheratan::errhdl::error_code code_to_report(sheratan::errhdl::default_errnum::UNKNOWN, sheratan::errhdl::get_default_category());
  ex_to_report
    << sheratan::errhdl::error_info::code(code_to_report)
    << sheratan::errhdl::error_info::file("")
    << sheratan::errhdl::error_info::line(0)
  ;

  write_ex(this->rc_pipe_w_[pipe_id], ex_to_report, rc_pipe_extype::RUNTIME_ERROR);
}

sheratan::errhdl::exception * daemonization_resources::retrieve_ex(daemonization_resources::pipe_id::value_type pipe_id, sheratan::errhdl::logic_error &logic_error, sheratan::errhdl::runtime_error &runtime_error)
{
  SHERATAN_CHECK(pipe_id < daemonization_resources::pipe_id::COUNT);
  SHERATAN_CHECK(this->rc_pipe_r_[pipe_id] != NULL);

  rc_pipe_tag_type ex_tag;
  errno = 0;
  if(std::fread(&ex_tag, sizeof(ex_tag), 1, this->rc_pipe_r_[pipe_id]) != 1) {
    int saved_errnum = errno;
    sheratan::errhdl::runtime_error ex_to_throw;
    ex_to_throw << error_category::error_info::posix_errnum(saved_errnum);
    SHERATAN_THROW_EXCEPTION(ex_to_throw, sheratan::errhdl::error_code(errnum::POSIX_SYSTEM, get_error_category()));
  }
  SHERATAN_CHECK(ex_tag == rc_pipe_ex_tag);

  rc_pipe_extype::value_type extype;
  errno = 0;
  if(std::fread(&extype, sizeof(extype), 1, this->rc_pipe_r_[pipe_id]) != 1) {
    int saved_errnum = errno;
    sheratan::errhdl::runtime_error ex_to_throw;
    ex_to_throw << error_category::error_info::posix_errnum(saved_errnum);
    SHERATAN_THROW_EXCEPTION(ex_to_throw, sheratan::errhdl::error_code(errnum::POSIX_SYSTEM, get_error_category()));
  }
  sheratan::errhdl::exception *ex_to_return = NULL;
  switch(extype) {
    case rc_pipe_extype::LOGIC_ERROR:
    {
      ex_to_return = &logic_error;
      break;
    }
    case rc_pipe_extype::RUNTIME_ERROR:
    {
      ex_to_return = &runtime_error;
      break;
    }
  }
  SHERATAN_CHECK(ex_to_return != NULL);

  rc_pipe_excategory::value_type excategory;
  errno = 0;
  if(std::fread(&excategory, sizeof(excategory), 1, this->rc_pipe_r_[pipe_id]) != 1) {
    int saved_errnum = errno;
    sheratan::errhdl::runtime_error ex_to_throw;
    ex_to_throw << error_category::error_info::posix_errnum(saved_errnum);
    SHERATAN_THROW_EXCEPTION(ex_to_throw, sheratan::errhdl::error_code(errnum::POSIX_SYSTEM, get_error_category()));
  }
  sheratan::errhdl::error_category::errnum_type en;
  errno = 0;
  if(std::fread(&en, sizeof(en), 1, this->rc_pipe_r_[pipe_id]) != 1) {
    int saved_errnum = errno;
    sheratan::errhdl::runtime_error ex_to_throw;
    ex_to_throw << error_category::error_info::posix_errnum(saved_errnum);
    SHERATAN_THROW_EXCEPTION(ex_to_throw, sheratan::errhdl::error_code(errnum::POSIX_SYSTEM, get_error_category()));
  }
  switch(excategory) {
    case rc_pipe_excategory::UNKNOWN:
    {
      sheratan::errhdl::error_code code_to_report(static_cast<sheratan::errhdl::default_errnum::value_type>(en), sheratan::errhdl::get_default_category());
      *ex_to_return << sheratan::errhdl::error_info::code(code_to_report);
      break;
    }
    case rc_pipe_excategory::ASSERT:
    {
      sheratan::errhdl::error_code code_to_report(static_cast<sheratan::errhdl::assert_errnum::value_type>(en), sheratan::errhdl::get_assert_category());
      *ex_to_return << sheratan::errhdl::error_info::code(code_to_report);
      break;
    }
    case rc_pipe_excategory::PROCESS:
    {
      sheratan::errhdl::error_code code_to_report(static_cast<sheratan::process_impl::posix::errnum::value_type>(en), sheratan::process_impl::posix::get_error_category());
      *ex_to_return << sheratan::errhdl::error_info::code(code_to_report);
      break;
    }
  }

  *ex_to_return << sheratan::errhdl::error_info::file("");

  sheratan::errhdl::error_info::line_type l;
  errno = 0;
  if(std::fread(&l, sizeof(l), 1, this->rc_pipe_r_[pipe_id]) != 1) {
    int saved_errnum = errno;
    sheratan::errhdl::runtime_error ex_to_throw;
    ex_to_throw << error_category::error_info::posix_errnum(saved_errnum);
    SHERATAN_THROW_EXCEPTION(ex_to_throw, sheratan::errhdl::error_code(errnum::POSIX_SYSTEM, get_error_category()));
  }
  *ex_to_return << sheratan::errhdl::error_info::line(l);

  sheratan::errhdl::error_info::seconds_type s;
  errno = 0;
  if(std::fread(&s, sizeof(s), 1, this->rc_pipe_r_[pipe_id]) != 1) {
    int saved_errnum = errno;
    sheratan::errhdl::runtime_error ex_to_throw;
    ex_to_throw << error_category::error_info::posix_errnum(saved_errnum);
    SHERATAN_THROW_EXCEPTION(ex_to_throw, sheratan::errhdl::error_code(errnum::POSIX_SYSTEM, get_error_category()));
  }
  *ex_to_return << sheratan::errhdl::error_info::seconds(s);

  sheratan::errhdl::error_info::useconds_type u;
  errno = 0;
  if(std::fread(&u, sizeof(u), 1, this->rc_pipe_r_[pipe_id]) != 1) {
    int saved_errnum = errno;
    sheratan::errhdl::runtime_error ex_to_throw;
    ex_to_throw << error_category::error_info::posix_errnum(saved_errnum);
    SHERATAN_THROW_EXCEPTION(ex_to_throw, sheratan::errhdl::error_code(errnum::POSIX_SYSTEM, get_error_category()));
  }
  *ex_to_return << sheratan::errhdl::error_info::useconds(u);

  return ex_to_return;
}

void daemonization_resources::restore_signal_dispositions(bool allow_throw)
{
  daemonization_resources::signal_dispositions_type::const_iterator end = this->signal_dispositions_.end();
  for(daemonization_resources::signal_dispositions_type::const_iterator i = this->signal_dispositions_.begin(); i != end; ++i) {
    if((::sigaction(i->signal_number, &(i->signal_sigaction), NULL) != 0) && (allow_throw)) {
      int saved_errnum = errno;
      sheratan::errhdl::runtime_error ex_to_throw;
      ex_to_throw << error_category::error_info::posix_errnum(saved_errnum);
      SHERATAN_THROW_EXCEPTION(ex_to_throw, sheratan::errhdl::error_code(errnum::POSIX_SYSTEM, get_error_category()));
    }
  }
}


} // namespace posix

} // namespace process_impl

} // namespace sheratan


// vim: set ts=2 sw=2 et:


