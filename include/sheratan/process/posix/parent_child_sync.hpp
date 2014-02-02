/// \file sheratan/process/posix/parent_child_sync.hpp
/// \brief POSIX parent-child synchronizer interface.
/// \ingroup sheratan_process_posix
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#ifndef HG_SHERATAN_PROCESS_POSIX_PARENT_CHILD_SYNC_HPP
#define HG_SHERATAN_PROCESS_POSIX_PARENT_CHILD_SYNC_HPP


#include <cstdio>

#include <boost/noncopyable.hpp>

#include "sheratan/process/posix/fwd.hpp"
#include "sheratan/process/posix/exit_status.hpp"


namespace sheratan {

namespace process_impl {

namespace posix {


/// \brief Parent-child synchronizer.
/// \ingroup sheratan_process_posix
/// \nosubgrouping
class parent_child_sync : private boost::noncopyable
{
  public:

    /// \brief Default constructor
    /// \par Abrahams exception guarantee:
    /// strong
    parent_child_sync();

  public:

    /// \brief Prefork (parent) callback.
    /// \par Abrahams exception guarantee:
    /// strong
    void prefork();

    /// \brief Postfork (parent) callback.
    /// \par Abrahams exception guarantee:
    /// strong
    void postfork(process &);

    /// \brief Child process callback.
    /// \return Child execution status:
    /// - <code>exit_status::SUCCESS</code>: Success.
    /// - otherwise: Failure.
    /// \par Abrahams exception guarantee:
    /// strong
    exit_status::value_type child();

    /// \brief Finalize parent-child sync.
    /// \par Abrahams exception guarantee:
    /// strong
    /// \note Call to this method will let synchronizer know that
    /// the sync routine is done and all synchronization resources
    /// may be released.
    /// \note Failure to call this method at all will only result
    /// that synchronization resources will not be released before
    /// destructor is invoked, which is when process object using
    /// this synchronizer will be destroyed.
    void finalize();

  public:

    /// \brief Wait for the parent.
    /// \par Abrahams exception guarantee:
    /// strong
    /// \note This method is intended to be called from child,
    /// in order to wait for parent while it deems appropriate
    /// for child to continue to run by calling \c unblock_child
    /// method.
    void wait_for_parent();

    /// \brief Let the child run.
    /// \par Abrahams exception guarantee:
    /// strong
    /// \note This method is intended to be called from parent,
    /// when it deems appropriate for child to continue to run
    /// after it was blocked on call to \c wait_for_parent method.
    void unblock_child();

    /// \brief Wait for the child.
    /// \par Abrahams exception guarantee:
    /// strong
    /// \note This method is intended to be called from parent,
    /// in order to wait for child while it deems appropriate
    /// for parent to continue to run by calling \c unblock_parent
    /// method.
    void wait_for_child();

    /// \brief Let the parent run.
    /// \par Abrahams exception guarantee:
    /// strong
    /// \note This method is intended to be called from child,
    /// when it deems appropriate for parent to continue to run
    /// after it was blocked on call to \c wait_for_child method.
    void unblock_parent();

  private:

    /// \brief Create parent-child synchronization pipe.
    /// \par Abrahams exception guarantee:
    /// strong
    void create_sync_pipe();

    /// \brief Close parent-child synchronization pipe.
    /// \par Abrahams exception guarantee:
    /// no-throw
    void close_sync_pipe();

    /// \brief Wait on synchronization pipe.
    /// \par Abrahams exception guarantee:
    /// strong
    void wait_sync_pipe();

    /// \brief Unblock synchronization pipe.
    /// \par Abrahams exception guarantee:
    /// strong
    void unblock_sync_pipe();

  private:

    /// \brief Parent-child synchronization pipe read-end.
    std::FILE *sync_pipe_r_;

    /// \brief Parent-child synchronization pipe write-end.
    std::FILE *sync_pipe_w_;
};


} // namespace posix

} // namespace process_impl

} // namespace sheratan


#endif // HG_SHERATAN_PROCESS_POSIX_PARENT_CHILD_SYNC_HPP


// vim: set ts=2 sw=2 et:


