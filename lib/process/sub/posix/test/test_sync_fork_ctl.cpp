/// \file process/sub/posix/test/test_sync_fork_ctl.cpp
/// \brief Test synchronised fork controller implementation.
/// \ingroup sheratan_process_posix_test
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#include "test_sync_fork_ctl.hpp"


namespace sheratan {

namespace process_impl {

namespace posix {

namespace test {


test_sync_fork_ctl::test_sync_fork_ctl(int child_exit_status, bool coredump)
: sync_()
, child_exit_status_(child_exit_status)
, coredump_(coredump)
{
}

test_sync_fork_ctl::test_sync_fork_ctl(const test_sync_fork_ctl &that)
: sync_()  // each copy must contain its own distinct synchronizer
, child_exit_status_(that.child_exit_status_)
, coredump_(that.coredump_)
{
}

fork_ctl * test_sync_fork_ctl::clone() const
{
  return new test_sync_fork_ctl(*this);
}

void test_sync_fork_ctl::prefork()
{
  // let synchronizer know that fork is about to be executed
  this->sync_.prefork();
}

void test_sync_fork_ctl::postfork(process &child_process)
{
  // let synchronizer know fork is done and this is parent process
  this->sync_.postfork(child_process);
}

exit_status::value_type test_sync_fork_ctl::child()
{
  // let synchronizer know fork is done and this is child process
  exit_status::value_type rc = this->sync_.child();
  if(rc != exit_status::SUCCESS) {
    return rc;
  }

  // wait for parent
  this->sync_.wait_for_parent();

  // synchronizer will not be needed anymore, let it release its resources
  this->sync_.finalize();

  // produce coredump if requested
  if(this->coredump_) {
    int *null_ptr = NULL;
    *null_ptr = 42;
  }

  // just return
  return this->child_exit_status_;
}

void test_sync_fork_ctl::finalize()
{
  this->sync_.finalize();
}

void test_sync_fork_ctl::wait_for_child()
{
  this->sync_.wait_for_child();
}

void test_sync_fork_ctl::unblock_child()
{
  this->sync_.unblock_child();
}


} // namespace test

} // namespace posix

} // namespace process_impl

} // namespace sheratan


// vim: set ts=2 sw=2 et:


