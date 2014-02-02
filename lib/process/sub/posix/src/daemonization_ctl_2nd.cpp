/// \file process/sub/posix/src/daemonization_ctl_2nd.cpp
/// \brief POSIX daemonization 2nd fork controller implementation.
/// \ingroup sheratan_process_posix
/// \author Marek Balint \c (mareq[A]balint[D]eu)


// pipe(2): http://pubs.opengroup.org/onlinepubs/009695399/functions/pipe.html
// sigaction(2): http://pubs.opengroup.org/onlinepubs/009695399/functions/sigaction.html
// sigemptyset(3): http://pubs.opengroup.org/onlinepubs/009695399/functions/sigemptyset.html
// sleep(3): http://pubs.opengroup.org/onlinepubs/009695399/functions/sleep.html


#include <cerrno>
#include <cstdio>

#include <signal.h>

#include "sheratan/errhdl/exception.hpp"
#include "sheratan/errhdl/assert.hpp"
#include "sheratan/errhdl/throw.hpp"
#include "sheratan/process/posix/error_category.hpp"
#include "sheratan/process/posix/self.hpp"
#include "sheratan/process/posix/process.hpp"

#include "daemonization_ctl_2nd.hpp"
#include "daemonization_resources.hpp"


namespace sheratan {

namespace process_impl {

namespace posix {


daemonization_ctl_2nd::daemonization_ctl_2nd(daemonization_resources &resources)
: resources_(resources)
, sync_pipe_r_(NULL)
, sync_pipe_w_(NULL)
{ }

daemonization_ctl_2nd::daemonization_ctl_2nd(const daemonization_ctl_2nd &that)
: resources_(that.resources_)
, sync_pipe_r_(NULL)  // each copy must contain its own distinct synchronization pipe
, sync_pipe_w_(NULL)  // each copy must contain its own distinct synchronization pipe 
{
}

daemonization_ctl_2nd::~daemonization_ctl_2nd()
{
  this->close_sync_pipe();
}

fork_ctl * daemonization_ctl_2nd::clone() const
{
  return new daemonization_ctl_2nd(*this);
}

void daemonization_ctl_2nd::prefork()
{
  // close read end of child pipe
  this->resources_.close_rc_pipe(daemonization_resources::pipe_id::CHILD, daemonization_resources::pipe_end::READ);

  // close read end of daemon pipe
  this->resources_.close_rc_pipe(daemonization_resources::pipe_id::DAEMON, daemonization_resources::pipe_end::READ);

  // create synchronization pipe
  this->create_sync_pipe();

  // set up SIGCHLD handler
  this->setup_sigchld();
}

void daemonization_ctl_2nd::postfork(process &child_process)
{
  try {
    // close write end of daemon pipe
    this->resources_.close_rc_pipe(daemonization_resources::pipe_id::DAEMON, daemonization_resources::pipe_end::WRITE);

    // wait for daemon to initalize (or fail)
    while(1) {
      try {
        // daemon will either call unblock_sync_pipe (in which case this call returns successfully),
        // or it will die before calling unblock_parent (in which case an exception will be thrown).
        this->wait_sync_pipe();
        break;
      }
      catch(sheratan::errhdl::runtime_error &ex) {
        sheratan::errhdl::error_code ec = get_code(ex);
        // EINTR: daemon exited due to some error before calling unblock_parent
        if((ec.get_category() == sheratan::process_impl::posix::get_error_category()) && (ec.get_errnum() == errnum::POSIX_SYSTEM) && (get_posix_errnum(ex) == EINTR)) {
          SHERATAN_CHECK(child_process.valid());
          exit_status es = child_process.join(true);
          if(es.valid()) {
            // valid exit status means that daemon exited prematurely due to some error
            SHERATAN_THROW_EXCEPTION(sheratan::errhdl::runtime_error(), sheratan::errhdl::error_code(errnum::DAEMON_ERROR, get_error_category()));
            break;
          }
        }
        // some other error occured
        else {
          throw;
        }
      }
    }

    // close write end of child pipe
    this->resources_.close_rc_pipe(daemonization_resources::pipe_id::CHILD, daemonization_resources::pipe_end::WRITE);
  }
  catch(...) {
    // attempt to kill daemon process (a.k.a. 2nd child) if still running
    if(child_process.valid()) {
      // exit status
      exit_status status;
      // at first, ask politely
      child_process.kill(SIGTERM);
      ::sleep(1);
      // get result
      status = child_process.join(true);
      // if it does not work
      if(!status.valid()) {
        // try to give it little more time
        ::sleep(5);
        status = child_process.join(true);
        // if it still does not work
        if(!status.valid()) {
          // stop being polite and just plain kill it
          child_process.kill(SIGKILL);
          status = child_process.join();
        }
      }
    }
    throw;
  }
}

exit_status::value_type daemonization_ctl_2nd::child()
{
  try {
    // close write end of child pipe
    this->resources_.close_rc_pipe(daemonization_resources::pipe_id::CHILD, daemonization_resources::pipe_end::WRITE);

    // execute common daemon initialization procedure
    daemonization_resources::fd_list_type exclusion_list;
    exclusion_list.push_back(::fileno(this->sync_pipe_r_));
    exclusion_list.push_back(::fileno(this->sync_pipe_w_));
    this->resources_.daemon_init_daemon(exclusion_list);

    /// report daemon process ID to parent
    this->resources_.report_pid(daemonization_resources::pipe_id::DAEMON, self::get_pid().get_value());

    // finalize daemonization resources
    this->resources_.finalize();

    // let parent process (our parent, globally known as "child process") run
    this->unblock_sync_pipe();

    // close synchronization pipe
    this->close_sync_pipe();

    // let user's daemon controller know that daemonization is done and this is a daemon process
    return this->resources_.get_daemon_ctl().daemonized_child();
  }
  catch(sheratan::errhdl::runtime_error &ex) {
    // report failure
    this->resources_.report_ex(daemonization_resources::pipe_id::DAEMON, ex);

    // finalize daemonization resources
    this->resources_.finalize();

    // close synchronization pipe
    this->close_sync_pipe();

    // unsuccessful return
    return exit_status::FAILURE;
  }
  catch(sheratan::errhdl::logic_error &ex) {
    // report failure
    this->resources_.report_ex(daemonization_resources::pipe_id::DAEMON, ex);

    // finalize daemonization resources
    this->resources_.finalize();

    // close synchronization pipe
    this->close_sync_pipe();

    // unsuccessful return
    return exit_status::FAILURE;
  }
  catch(...) {
    // report failure
    this->resources_.report_unknown_ex(daemonization_resources::pipe_id::DAEMON);

    // finalize daemonization resources
    this->resources_.finalize();

    // close synchronization pipe
    this->close_sync_pipe();

    // unsuccessful return
    return exit_status::FAILURE;
  }
}

void daemonization_ctl_2nd::create_sync_pipe()
{
  SHERATAN_CHECK(this->sync_pipe_r_ == NULL);
  SHERATAN_CHECK(this->sync_pipe_w_ == NULL);

  int saved_errnum = 0;
  int sync_pipe_fd[2] = {-1, -1};

  // create synchronization pipe
  if(::pipe(sync_pipe_fd) != 0) {
    saved_errnum = errno;
    goto error;
  }
  this->sync_pipe_r_ = ::fdopen(sync_pipe_fd[0], "r");
  if(this->sync_pipe_r_ == NULL) {
    saved_errnum = errno;
    goto error;
  }
  this->sync_pipe_w_ = ::fdopen(sync_pipe_fd[1], "w");
  if(this->sync_pipe_w_ == NULL) {
    saved_errnum = errno;
    goto error;
  }

  // successful return
  return;

  // ERROR HANDLING
  error:

  // free all possibly allocated resources
  if((this->sync_pipe_r_ == NULL) && (sync_pipe_fd[0] != -1)) {
    ::close(sync_pipe_fd[0]);
  }
  if((this->sync_pipe_w_ == NULL) && (sync_pipe_fd[1] != -1)) {
    ::close(sync_pipe_fd[1]);
  }
  this->close_sync_pipe();

  // throw exception
  sheratan::errhdl::runtime_error ex_to_throw;
  ex_to_throw << error_category::error_info::posix_errnum(saved_errnum);
  SHERATAN_THROW_EXCEPTION(ex_to_throw, sheratan::errhdl::error_code(errnum::POSIX_SYSTEM, get_error_category()));
}

void daemonization_ctl_2nd::close_sync_pipe()
{
  if(this->sync_pipe_r_ != NULL) {
    std::fclose(this->sync_pipe_r_);
    this->sync_pipe_r_ = NULL;
  }
  if(this->sync_pipe_w_ != NULL) {
    std::fclose(this->sync_pipe_w_);
    this->sync_pipe_w_ = NULL;
  }
}


namespace {


/// \brief Data to be sent over synchronization pipe.
static const char sync_pipe_data = 42;


} // anonymous namespace


void daemonization_ctl_2nd::wait_sync_pipe()
{
  errno = 0;
  int data;
  if((data = std::fgetc(this->sync_pipe_r_)) == EOF) {
    int saved_errnum = errno;
    sheratan::errhdl::runtime_error ex_to_throw;
    ex_to_throw << error_category::error_info::posix_errnum(saved_errnum);
    SHERATAN_THROW_EXCEPTION(ex_to_throw, sheratan::errhdl::error_code(errnum::POSIX_SYSTEM, get_error_category()));
  }

  SHERATAN_CHECK(data == sync_pipe_data);
}

void daemonization_ctl_2nd::unblock_sync_pipe()
{
  errno = 0;
  if(std::fputc(sync_pipe_data, this->sync_pipe_w_) == EOF) {
    int saved_errnum = errno;
    sheratan::errhdl::runtime_error ex_to_throw;
    ex_to_throw << error_category::error_info::posix_errnum(saved_errnum);
    SHERATAN_THROW_EXCEPTION(ex_to_throw, sheratan::errhdl::error_code(errnum::POSIX_SYSTEM, get_error_category()));
  }
}

void daemonization_ctl_2nd::setup_sigchld()
{
  // install SIGCHLD handler
  struct sigaction signal_sigaction;
  signal_sigaction.sa_handler = daemonization_ctl_2nd::sigchld_handler;
  if(::sigemptyset(&signal_sigaction.sa_mask) != 0) {
    int saved_errnum = errno;
    sheratan::errhdl::runtime_error ex_to_throw;
    ex_to_throw << error_category::error_info::posix_errnum(saved_errnum);
    SHERATAN_THROW_EXCEPTION(ex_to_throw, sheratan::errhdl::error_code(errnum::POSIX_SYSTEM, get_error_category()));
  }
  signal_sigaction.sa_flags = 0;
  if(::sigaction(SIGCHLD, &signal_sigaction, NULL) != 0) {
    int saved_errnum = errno;
    sheratan::errhdl::runtime_error ex_to_throw;
    ex_to_throw << error_category::error_info::posix_errnum(saved_errnum);
    SHERATAN_THROW_EXCEPTION(ex_to_throw, sheratan::errhdl::error_code(errnum::POSIX_SYSTEM, get_error_category()));
  }
}

void daemonization_ctl_2nd::sigchld_handler(int)
{
  // nop
}


} // namespace posix

} // namespace process_impl

} // namespace sheratan


// vim: set ts=2 sw=2 et:


