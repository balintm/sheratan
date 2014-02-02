/// \file sheratan/process/posix/daemon_template.hpp
/// \brief POSIX daemon template interface.
/// \ingroup sheratan_process_posix
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#ifndef HG_SHERATAN_PROCESS_POSIX_DAEMON_TEMPLATE_HPP
#define HG_SHERATAN_PROCESS_POSIX_DAEMON_TEMPLATE_HPP


#include "sheratan/process/posix/daemon.hpp"
#include "sheratan/process/posix/daemonizer.hpp"


namespace sheratan {

namespace process_impl {

namespace posix {


/// \brief Daemon template POSIX implementation.
/// \ingroup sheratan_process_posix
/// \nosubgrouping
template<typename Tag>
class daemon_template : public daemon
{
  public:

    /// \brief Default constructor.
    /// \par Abrahams exception guarantee:
    /// no-throw
    /// \post <code>this->valid() == false</code>
    /// \post <code>this->get_pid() == process_id()</code>.
    daemon_template();

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
    /// \par Abrahams exception guarantee:
    /// strong
    /// \pre All redirection paths must be existing, valid and accessible.
    /// \post <code>this->valid() == true</code>
    /// \post <code>this->get_pid() != process_id()</code>.
    explicit daemon_template(
      const daemon_ctl &dc,
      const daemonizer::pid_file_type &pid_file = daemonizer::pid_file_type(),
      const daemonizer::pid_file_mode_type &pid_file_mode = daemonizer::pid_file_mode_type(),
      const daemonizer::working_dir_type &working_dir = daemonizer::working_dir_type(),
      const daemonizer::stdin_redirect_type &stdin_redirect = daemonizer::stdin_redirect_type(),
      const daemonizer::stdout_redirect_type &stdout_redirect = daemonizer::stdout_redirect_type(),
      const daemonizer::stderr_redirect_type &stderr_redirect = daemonizer::stderr_redirect_type(),
      const daemonizer::reset_signals_flag_type &reset_signals_flag = daemonizer::reset_signals_flag_type()
    );

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

  private:

    /// \brief Daemonizer.
    daemonizer daemonizer_;
};


} // namespace posix

} // namespace process_impl

} // namespace sheratan


#include "sheratan/process/posix/daemon_template.ci"


#endif // HG_SHERATAN_PROCESS_POSIX_DAEMON_TEMPLATE_HPP


// vim: set ts=2 sw=2 et:


