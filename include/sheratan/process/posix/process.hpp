/// \file sheratan/process/posix/process.hpp
/// \brief Process POSIX implementaton interface.
/// \ingroup sheratan_process_posix
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#ifndef HG_SHERATAN_PROCESS_POSIX_PROCESS_HPP
#define HG_SHERATAN_PROCESS_POSIX_PROCESS_HPP


#include <algorithm>

#include <boost/noncopyable.hpp>

#include "sheratan/process/posix/fwd.hpp"
#include "sheratan/process/posix/types.hpp"
#include "sheratan/process/posix/process_id.hpp"
#include "sheratan/process/posix/exit_status.hpp"


namespace sheratan {

namespace process_impl {

namespace posix {


/// \brief Process POSIX implementation.
/// \ingroup sheratan_process_posix
/// \nosubgrouping
/// \todo Implement \c timed_join methods.
class process : private boost::noncopyable
{
  public:

    /// \brief Virtual destructor.
    /// \par Abrahams exception guarantee:
    /// no-throw
    /// \pre <code>this->valid() == false</code>
    virtual ~process() = 0;

  private:

    /// \brief Set process ID.
    /// \param pid Process ID.
    /// \par Abrahams exception guarantee:
    /// no-throw
    /// \pre <code>pid != process_id()</code>
    /// \post <code>this->valid() == true</code>
    /// \post <code>this->get_pid() == pid</code>.
    /// \note Only \c forker has access to this method.
    void set_pid(process_id pid);

    friend class forker;

  public:

    /// \brief Get process ID.
    /// \return Process ID.
    /// \par Abrahams exception guarantee:
    /// no-throw
    process_id get_pid() const;

    /// \brief Determine whether the process is valid.
    /// \retval true Valid process, which was not yet waited for.
    /// \retval false Not a process.
    /// \par Abrahams exception guarantee:
    /// no-throw
    bool valid() const;

    /// \brief Detach process.
    /// \par Abrahams exception guarantee:
    /// strong
    /// \post <code>!after->valid() == false</code>
    /// \note Call to this method will not free any resources.
    /// It will merely change state of the object to from valid
    /// to invalid state, so it fulfills destructors' preconditions.
    /// \note Calling this method on invalid process will have
    /// no effect.
    void detach();

    /// \brief Wait for the process to complete.
    /// \param nonblocking If set, this method will not block. In case the process
    /// did not change its status. In such case, invalid \c exit_status is returned instead
    /// (i.e. <code>retval->valid() == false</code>).
    /// \param stopped If set, this method will return also for process
    /// that is stopped and its status was not yet reported since it stopped.
    /// \param continued If set, this method will return also for process
    /// that has continued and its status was not yet reported since it continued.
    /// \return Exit status of the process.
    /// \par Abrahams exception guarantee:
    /// strong
    /// \pre <code>before->valid() == true</code>
    /// \todo Setting handler of \c SIGCHLD to \c SIG_IGN changes behavior of this method.
    /// It is not necessarily bad thing (although, most probably it is). This issue must
    /// thereherefore, be analyzed in some greater detail. See \c waitpid manpage:
    /// <blockquote>
    /// POSIX.1-2001  specifies  that if the disposition of SIGCHLD is set to SIG_IGN or the SA_NOCLDWAIT flag is set for SIGCHLD (see sigaction(2)), then
    /// children that terminate do not become zombies and a call to wait() or waitpid() will block until all children have terminated, and then fail  with
    /// errno set to ECHILD.  (The original POSIX standard left the behavior of setting SIGCHLD to SIG_IGN unspecified.  Note that even though the default
    /// disposition of SIGCHLD is "ignore", explicitly setting the disposition to SIG_IGN results in different  treatment  of  zombie  process  children.)
    /// Linux 2.6 conforms to this specification.  However, Linux 2.4 (and earlier) does not: if a wait() or waitpid() call is made while SIGCHLD is being
    /// ignored, the call behaves just as though SIGCHLD were not being ignored, that is, the call blocks until the next child terminates and then returns
    /// the process ID and status of that child.
    /// </blockquote>
    exit_status join(bool nonblocking = false, bool stopped = false, bool continued = false);

    # if 0 // NOT IMPLEMENTED
    /// \brief Wait for the process to complete until specified time.
    /// \param time System time, until when to wait for the process completion.
    /// \return Exit status of the process.
    /// \par Abrahams exception guarantee:
    /// strong
    /// \pre <code>before->valid() == true</code>
    /// \post <code>!after->valid() == false</code>: Return value contains
    ///       exit status of completed process.
    /// \post <code>after->valid() == true</code>: Return value is unspecified.
    exit_status timed_join(const system_time_type &time);
    # endif // NOT IMPLEMENTED

    # if 0 // NOT IMPLEMENTED
    /// \brief Wait for the process to complete for specified time.
    /// \param time Duration, while to wait for the process completion.
    /// \return Exit status of the process.
    /// \par Abrahams exception guarantee:
    /// strong
    /// \pre <code>before->valid() == true</code>
    /// \post <code>!after->valid() == false</code>: Return value contains
    ///       exit status of completed process.
    /// \post <code>after->valid() == true</code>: Return value is unspecified.
    template<typename DurationT>
    exit_status timed_join(const DurationT &time);
    # endif // NOT IMPLEMENTED

    /// \brief Send signal to the process.
    /// \param signal Signal number.
    /// \par Abrahams exception guarantee:
    /// strong
    /// \pre <code>before->valid() == true</code>
    /// \pre Specified signal number must be valid.
    void kill(signal_number_type signal);

  private:

    /// \brief Process ID.
    process_id pid_;
};


} // namespace posix

} // namespace process_impl

} // namespace sheratan


#include "sheratan/process/posix/process.ci"


#endif // HG_SHERATAN_PROCESS_POSIX_PROCESS_HPP


// vim: set ts=2 sw=2 et:


