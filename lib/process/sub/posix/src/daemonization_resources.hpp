/// \file process/sub/posix/src/daemonization_resources.hpp
/// \brief POSIX daemonization resources interface.
/// \ingroup sheratan_process_posix
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#ifndef HGI_SHERATAN_PROCESS_POSIX_DAEMONIZATION_RESOURCES_HPP
#define HGI_SHERATAN_PROCESS_POSIX_DAEMONIZATION_RESOURCES_HPP


#include <vector>

#include <unistd.h>
#include <signal.h>
#include <sys/resource.h>

#include <boost/noncopyable.hpp>
#include <boost/array.hpp>

#include "sheratan/errhdl/exception.hpp"
#include "sheratan/process/posix/daemonizer.hpp"
#include "sheratan/process/posix/daemon_ctl.hpp"
#include "sheratan/process/posix/process_id.hpp"


namespace sheratan {

namespace process_impl {

namespace posix {


/// \brief POSIX daemonization resources.
/// \ingroup sheratan_process_posix
/// \nosubgrouping
class daemonization_resources : private boost::noncopyable
{
  public:

    /// \brief Pipe ID.
    /// \ingroup sheratan_process_posix
    /// \nosubgrouping
    struct pipe_id
    {
      /// \brief Return code pipe IDs.
      typedef enum
      {
        CHILD = 0, ///< Parent-child return code pipe.
        DAEMON,    ///< Parent-child-daemon return code pipe.
        COUNT      ///< Number of distinct return code pipe IDs.
      } value_type;
    };

    /// \brief Pipe end.
    /// \ingroup sheratan_process_posix
    /// \nosubgrouping
    struct pipe_end
    {
      /// \brief Pipe ends.
      typedef enum
      {
        READ = 0, ///< Read-end.
        WRITE = 1 ///< Write-end.
      } value_type;
    };

    /// \brief file descriptors list type definition.
    typedef std::vector<file_descriptor_type> fd_list_type;

  public:

    /// \brief Default constructor
    /// \par Abrahams exception guarantee:
    /// strong
    daemonization_resources();

    /// \brief Constructor.
    /// \param dc Daemon controller.
    /// \param pid_file Path to the daemon's PID file. No PID file will be
    /// used, if ommited.
    /// \param pid_file_mode Mode to be used for creation of PID file.
    /// \param working_dir Path to the daemon's working directory. Working
    /// directory will not be changed, if ommited.
    /// \param stdin_redirect Standard input redirection path. Standard input
    /// will not be redirected, if ommited.
    /// \param stdout_redirect Standard output redirection path. Standard output
    /// will not be redirected, if ommited.
    /// \param stderr_redirect Standard error redirection path. Standard error
    /// will not be redirected, if ommited.
    /// \param reset_signals_flag Reset all signal handlers to default values
    /// in the daemon process.
    /// \par Abrahams exception guarantee: /// strong
    explicit daemonization_resources(
      const daemon_ctl &dc,
      const daemonizer::pid_file_type &pid_file = daemonizer::pid_file_type(),
      const daemonizer::pid_file_mode_type &pid_file_mode = daemonizer::pid_file_mode_type(),
      const daemonizer::working_dir_type &working_dir = daemonizer::working_dir_type(),
      const daemonizer::stdin_redirect_type &stdin_redirect = daemonizer::stdin_redirect_type(),
      const daemonizer::stdout_redirect_type &stdout_redirect = daemonizer::stdout_redirect_type(),
      const daemonizer::stderr_redirect_type &stderr_redirect = daemonizer::stderr_redirect_type(),
      const daemonizer::reset_signals_flag_type &reset_signals_flag = daemonizer::reset_signals_flag_type()
    );

    /// \brief Destructor
    /// \par Abrahams exception guarantee:
    /// no-throw
    ~daemonization_resources();

  public:

    /// \brief Free all resources.
    /// \par Abrahams exception guarantee:
    /// no-throw
    void finalize();

  public:

    /// \brief Get daemon controller.
    /// \return Daemon controller.
    /// \par Abrahams exception guarantee:
    /// no-throw
    /// \pre Object must not be created by default constructor.
    const daemon_ctl & get_daemon_ctl() const;

    /// \brief Get daemon controller.
    /// \return Daemon controller.
    /// \par Abrahams exception guarantee:
    /// no-throw
    /// \pre Object must not be created by default constructor.
    daemon_ctl & get_daemon_ctl();

  public:

    /// \brief Create return code pipe.
    /// \param pipe_id Return code pipe ID.
    /// \par Abrahams exception guarantee:
    /// strong
    void create_rc_pipe(daemonization_resources::pipe_id::value_type pipe_id);

    /// \brief Close return code pipe.
    /// \param pipe_id Return code pipe ID.
    /// \param pipe_end Return code pipe end.
    /// \par Abrahams exception guarantee:
    /// no-throw
    void close_rc_pipe(daemonization_resources::pipe_id::value_type pipe_id, daemonization_resources::pipe_end::value_type pipe_end);

  public:

    /// \brief Daemon initialization: parent process.
    /// \par Abrahams exception guarantee:
    /// weak
    void daemon_init_parent();

    /// \brief Daemon initialization: child process.
    /// \par Abrahams exception guarantee:
    /// weak
    void daemon_init_child();

    /// \brief Daemon initialization: daemon process.
    /// \param excluded_fds List of file descriptors, which are not
    /// to be closed. Note that standard streams (\c stdin, \c stdout
    /// and \c stderr) are always implicitly excluded, i.e. also in case
    /// they are not explicitly listed on this list. The very same
    /// applies to file descriptors owned by \c daemonization_resources
    /// class, which are managed separately.
    /// \par Abrahams exception guarantee:
    /// weak
    void daemon_init_daemon(const daemonization_resources::fd_list_type &excluded_fds);

  public:

    /// \brief Report PID.
    /// \param pipe_id Return code pipe ID.
    /// \param pid Process ID to be reported.
    /// \par Abrahams exception guarantee:
    /// strong
    void report_pid(daemonization_resources::pipe_id::value_type pipe_id, const process_id::value_type &pid);

    /// \brief Set daemon process ID.
    /// \param pipe_id Return code pipe ID.
    /// \par Abrahams exception guarantee:
    /// no-throw
    void retrieve_daemon_pid(daemonization_resources::pipe_id::value_type pipe_id);

    /// \brief Get daemon process ID.
    /// \return Daemon process ID.
    /// \par Abrahams exception guarantee:
    /// no-throw
    process_id::value_type get_daemon_pid() const;

    /// \brief Report logic exception.
    /// \param pipe_id Return code pipe ID.
    /// \param ex Exception to be reported.
    /// \par Abrahams exception guarantee:
    /// no-throw
    void report_ex(daemonization_resources::pipe_id::value_type pipe_id, const sheratan::errhdl::logic_error &ex);

    /// \brief Report runtime exception.
    /// \param pipe_id Return code pipe ID.
    /// \param ex Exception to reported.
    /// \par Abrahams exception guarantee:
    /// no-throw
    void report_ex(daemonization_resources::pipe_id::value_type pipe_id, const sheratan::errhdl::runtime_error &ex);

    /// \brief Report unknown exception.
    /// \param pipe_id Return code pipe ID.
    /// \par Abrahams exception guarantee:
    /// no-throw
    void report_unknown_ex(daemonization_resources::pipe_id::value_type pipe_id);

    /// \brief Retrieve exception.
    /// \param pipe_id Return code pipe ID.
    /// \param logic_error Sheratan logic error exception object.
    /// \param runtime_error Sheratan runtime error exception object.
    /// \return Retrieved exception.
    /// \par Abrahams exception guarantee:
    /// weak
    /// \note Pointer to one of exception objects passed via parameters,
    /// is returned, depending on return code on rc-pipe. Caller owns
    /// and therefore is fully responsible for managing both of these
    /// exception objects. Furthermore, it is strongly recommended to
    /// allocate these objects on stack.
    /// \note In case when unknown exception is reported to rc-pipe,
    /// Sheratan runtime error exception with default error category
    /// is returned.
    sheratan::errhdl::exception * retrieve_ex(daemonization_resources::pipe_id::value_type pipe_id, sheratan::errhdl::logic_error &logic_error, sheratan::errhdl::runtime_error &runtime_error);

  private:
    
    /// \brief Return code pipe type definition.
    typedef boost::array<FILE *, daemonization_resources::pipe_id::COUNT> rc_pipe_type;

    /// \brief Signal disposition type definition.
    /// \ingroup sheratan_process_posix
    /// \nosubgrouping
    struct signal_disposition
    {
      /// \brief Signal number.
      signal_number_type signal_number;

      /// \brief Signal disposition.
      struct sigaction signal_sigaction;
    };

    /// \brief Signal dispositions type definition.
    typedef std::vector<signal_disposition> signal_dispositions_type;

  private:

    /// \brief Restore signal dispositions.
    /// \param allow_throw Flag determining required Abrahams exception guarantee.
    /// \par Abrahams exception guarantee:
    /// - <code>allow_throw == true</code>: strong
    /// - <code>allow_throw == false</code>: no-throw
    void restore_signal_dispositions(bool allow_throw = true);

  private:

    /// \brief Daemon controller.
    std::auto_ptr<daemon_ctl> daemon_ctl_;

    /// \brief PID file.
    daemonizer::pid_file_type::value_type pid_file_;

    /// \brief PID file mode.
    daemonizer::pid_file_mode_type::value_type pid_file_mode_;

    /// \brief Working directory.
    daemonizer::working_dir_type::value_type working_dir_;

    /// \brief Standard input redirection path.
    daemonizer::stdin_redirect_type::value_type stdin_redirect_;

    /// \brief Standard output redirection path.
    daemonizer::stdout_redirect_type::value_type stdout_redirect_;

    /// \brief Standard error redirection path.
    daemonizer::stderr_redirect_type::value_type stderr_redirect_;

    /// \brief Reset signal dispositions to default values flag.
    daemonizer::reset_signals_flag_type::value_type reset_signals_flag_;

    /// \brief Daemon process ID.
    process_id::value_type daemon_pid_;

    /// \brief Return code pipe read-end.
    daemonization_resources::rc_pipe_type rc_pipe_r_;

    /// \brief Return code pipe write-end.
    daemonization_resources::rc_pipe_type rc_pipe_w_;

    /// \brief Maximum number of file descriptors limit.
    struct rlimit filedescs_rlimit_;

    /// \brief Original signal dispositions.
    daemonization_resources::signal_dispositions_type signal_dispositions_;
};


} // namespace posix

} // namespace process_impl

} // namespace sheratan


#endif // HGI_SHERATAN_PROCESS_POSIX_DAEMONIZATION_RESOURCES_HPP


// vim: set ts=2 sw=2 et:


