/// \file sheratan/process/posix/daemon.hpp
/// \brief Daemon POSIX implementaton interface.
/// \ingroup sheratan_process_posix
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#ifndef HG_SHERATAN_PROCESS_POSIX_DAEMON_HPP
#define HG_SHERATAN_PROCESS_POSIX_DAEMON_HPP


#include <boost/noncopyable.hpp>

#include "sheratan/process/posix/fwd.hpp"
#include "sheratan/process/posix/types.hpp"
#include "sheratan/process/posix/process_id.hpp"


namespace sheratan {

namespace process_impl {

namespace posix {


/// \brief Daemon POSIX implementation.
/// \ingroup sheratan_process_posix
/// \nosubgrouping
class daemon : private boost::noncopyable
{
  public:

    /// \brief Virtual destructor.
    /// \par Abrahams exception guarantee:
    /// no-throw
    virtual ~daemon() = 0;

  private:

    /// \brief Set process ID.
    /// \param pid Process ID.
    /// \par Abrahams exception guarantee:
    /// no-throw
    /// \pre <code>pid != process_id()</code>
    /// \post <code>this->valid() == true</code>
    /// \post <code>this->get_pid() == pid</code>.
    /// \note Only \c daemonizer has access to this method.
    void set_pid(process_id pid);

    friend class daemonizer;

  public:

    /// \brief Get process ID.
    /// \return Process ID.
    /// \par Abrahams exception guarantee:
    /// no-throw
    process_id get_pid() const;

    /// \brief Determine whether the daemon is valid.
    /// \retval true Daemon with valid process ID.
    /// \retval false Not a process.
    /// \par Abrahams exception guarantee:
    /// no-throw
    /// \note There is no way how to find out that the actual
    /// daemon process is still running and/or it was/wasn't
    /// waited for, since it is not direct child of process,
    /// which is using object of this class. Therefore, validiy
    /// of daemon process is based solely on validity of its PID,
    /// which might be invalidated in the meantime.
    bool valid() const;

    /// \brief Send signal to the process.
    /// \param signal Signal number.
    /// \par Abrahams exception guarantee:
    /// strong
    /// \pre <code>before->valid() == true</code>
    /// \pre Specified signal number must be valid.
    /// \note Since "validity" of daemon process is very uncertain
    /// term, it is very well possible that this method will throw
    /// exception with error code "no souch process", although
    /// daemon validity precondition was met. Unfortunately,
    /// there is no way how to really solve this problem - see
    /// \c daemon::valid() method.
    void kill(signal_number_type signal);

  private:

    /// \brief Process ID.
    process_id pid_;
};


} // namespace posix

} // namespace process_impl

} // namespace sheratan


#endif // HG_SHERATAN_PROCESS_POSIX_DAEMON_HPP


// vim: set ts=2 sw=2 et:


