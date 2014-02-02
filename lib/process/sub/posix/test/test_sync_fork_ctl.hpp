/// \file process/sub/posix/test/test_sync_fork_ctl.hpp
/// \brief Test synchronized fork controller interface.
/// \ingroup sheratan_process_posix_test
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#ifndef HG_SHERATAN_PROCESS_POSIX_TEST_TEST_SYNC_FORK_CTL_HPP
#define HG_SHERATAN_PROCESS_POSIX_TEST_TEST_SYNC_FORK_CTL_HPP


#include "sheratan/process/posix/fork_ctl.hpp"
#include "sheratan/process/posix/parent_child_sync.hpp"


namespace sheratan {

namespace process_impl {

namespace posix {

namespace test {


/// \brief Test synchronized fork controller.
/// \ingroup sheratan_process_posix_test
/// \nosubgrouping
class test_sync_fork_ctl : public sheratan::process_impl::posix::fork_ctl
{
  public:

    /// \brief Constructor.
    /// \param child_exit_status Exit status to be returned from child process.
    /// \param coredump Whether to produce coredump in child process.
    /// \par Abrahams exception guarantee:
    /// strong
    test_sync_fork_ctl(int child_exit_status, bool coredump);

    /// \brief Copy constructor.
    /// \param that Other instance to copy from.
    /// \par Abrahams exception guarantee:
    /// strong
    test_sync_fork_ctl(const test_sync_fork_ctl &that);

  public:

    virtual fork_ctl * clone() const;

  public:

    virtual void prefork();

    virtual void postfork(process &child_process);

    virtual exit_status::value_type child();

    /// \brief Finalize parent-child synchronized fork controller.
    /// \par Abrahams exception guarantee:
    /// strong
    /// \note Call to this method will let synchronizer know that
    /// the sync routine is done and all synchronization resources
    /// may be released.
    /// \note Failure to call this method at all will only result
    /// that synchronization resources will not be released before
    /// destructor is invoked, which is when process object using
    /// this fork controller will be destroyed.
    void finalize();

  public:

    /// \brief Wait for the child.
    /// \par Abrahams exception guarantee:
    /// strong
    /// \note This method is intended to be called from parent,
    /// in order to wait for child while it deems appropriate
    /// for parent to continue to run by calling \c unblock_parent
    /// method.
    void wait_for_child();

    /// \brief Let the child run.
    /// \par Abrahams exception guarantee:
    /// strong
    /// \note This method is intended to be called from parent,
    /// when it deems appropriate for child to continue to run
    /// after it was blocked on call to \c wait_for_parent method.
    void unblock_child();

  private:

    /// \brief Parent-child synchronizer.
    parent_child_sync sync_;

    /// \brief Child exit status.
    int child_exit_status_;

    /// \brief Flag determining, whether to produce core dump in child process.
    bool coredump_;
};


} // namespace test

} // namespace posix

} // namespace process_impl

} // namespace sheratan


#endif // HG_SHERATAN_PROCESS_POSIX_TEST_TEST_SYNC_FORK_CTL_HPP


// vim: set ts=2 sw=2 et:


