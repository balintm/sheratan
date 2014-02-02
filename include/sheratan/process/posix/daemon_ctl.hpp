/// \file sheratan/process/posix/daemon_ctl.hpp
/// \brief POSIX daemon controller interface.
/// \ingroup sheratan_process_posix
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#ifndef HG_SHERATAN_PROCESS_POSIX_DAEMON_CTL_TEMPLATE_HPP
#define HG_SHERATAN_PROCESS_POSIX_DAEMON_CTL_TEMPLATE_HPP


#include "sheratan/process/posix/fwd.hpp"
#include "sheratan/process/posix/exit_status.hpp"


namespace sheratan {

namespace process_impl {

namespace posix {


/// \brief POSIX daemon controller.
/// \ingroup sheratan_process_posix
/// \nosubgrouping
class daemon_ctl
{
  public:

    /// \brief Virtual destructor.
    /// \par Abrahams exception guarantee:
    /// no-throw
    virtual ~daemon_ctl() = 0;

  public:

    /// \brief Clone.
    /// \return Pointer to newly created instance.
    /// \par Abrahams exception guarantee:
    /// strong
    virtual daemon_ctl * clone() const = 0;

  public:

    /// \brief Predaemonize (parent) routine.
    /// \par Abrahams exception guarantee:
    /// strong
    virtual void predaemonize() = 0;

    /// \brief Postdaemonize (parent) routine.
    /// \param daemon_process Daemon process object.
    /// \par Abrahams exception guarantee:
    /// strong
    virtual void postdaemonize(daemon &daemon_process) = 0;

    /// \brief Daemon process routine.
    /// \return Return value of daemon process.
    /// \par Abrahams exception guarantee:
    /// strong
    virtual exit_status::value_type daemonized_child() = 0;
};


} // namespace posix

} // namespace process_impl

} // namespace sheratan


#endif // HG_SHERATAN_PROCESS_POSIX_DAEMON_CTL_TEMPLATE_HPP


// vim: set ts=2 sw=2 et:


