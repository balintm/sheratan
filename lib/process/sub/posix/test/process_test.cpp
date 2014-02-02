/// \file process/sub/posix/test/process_test.cpp
/// \brief Process POSIX implementation unit-test file.
/// \ingroup sheratan_process_posix_test
/// \author Marek Balint \c (mareq[A]balint[D]eu)
/// \todo Probably because Boost.Test is trying to manage processes
/// behind the scenes in order to report also this kind of errors,
/// it is impossible to simulate stopping/continuing process. Some
/// workaround is needed, or this functionality must be at least tested
/// by other means.


#include <boost/test/unit_test.hpp>
#include "boost_test_sigchld_suppressor.hpp"

#include "sheratan/process/posix/process.hpp"
#include "sheratan/process/posix/process_template.hpp"
#include "test_sync_fork_ctl.hpp"


using namespace sheratan::process_impl::posix::test;


namespace {


/// \brief Test process type definition.
typedef sheratan::process_impl::posix::process_template<struct test_parent_child_sync_process_tag> test_parent_child_sync_process;


BOOST_AUTO_TEST_SUITE(process)

  /// \brief Unit-test case: Default construction.
  BOOST_AUTO_TEST_CASE(default_construction)
  {
    // default construction
    test_parent_child_sync_process default_constructed;
    BOOST_CHECK_EQUAL(default_constructed.valid(), false);
    BOOST_CHECK_EQUAL(default_constructed.get_pid(), sheratan::process_impl::posix::process_id());
  }

  /// \brief Unit-test case: Child process with normal exit.
  BOOST_AUTO_TEST_CASE(child_normal_exit)
  {
    // ignore SIGCHLD in order to make Boost.Test shut up
    // about child process exiting with nonzero status
    sheratan::process_impl::posix::test::boost_test_sigchld_suppressor sigchld_suppressor;
    // make compiler shut up about unused variable sigchld_suppressor
    sigchld_suppressor.no_op();

    // create child process and let it run
    test_parent_child_sync_process child(test_sync_fork_ctl(42, false));
    test_sync_fork_ctl &fc = dynamic_cast<test_sync_fork_ctl &>(child.get_fork_ctl());
    fc.unblock_child();
    fc.finalize();

    // check that valid child process exists
    BOOST_CHECK_EQUAL(child.valid(), true);
    BOOST_CHECK_NE(child.get_pid(), sheratan::process_impl::posix::process_id());

    // wait for the child process
    sheratan::process_impl::posix::exit_status exit_status = child.join();

    // check that child process does not exist anymore
    BOOST_CHECK_EQUAL(child.valid(), false);
    BOOST_CHECK_EQUAL(child.get_pid(), sheratan::process_impl::posix::process_id());

    // check exit status of the child process
    BOOST_CHECK_EQUAL(exit_status.exited(), true);
    BOOST_CHECK_EQUAL(exit_status.signaled(), false);
    BOOST_CHECK_EQUAL(exit_status.stopped(), false);
    BOOST_CHECK_EQUAL(exit_status.continued(), false);
    BOOST_CHECK_EQUAL(exit_status.dumped_core(), false);
    BOOST_CHECK_EQUAL(exit_status.get_status(), 42);
  }

  /// \brief Unit-test case: Child process with exit by signal.
  BOOST_AUTO_TEST_CASE(child_signal_exit)
  {
    // ignore SIGCHLD in order to make Boost.Test shut up
    // about child process exiting with nonzero status
    sheratan::process_impl::posix::test::boost_test_sigchld_suppressor sigchld_suppressor;
    // make compiler shut up about unused variable sigchld_suppressor
    sigchld_suppressor.no_op();

    // create child process
    test_parent_child_sync_process child(test_sync_fork_ctl(42, false));
    test_sync_fork_ctl &fc = dynamic_cast<test_sync_fork_ctl &>(child.get_fork_ctl());
    fc.finalize();

    // check that valid child process exists
    BOOST_CHECK_EQUAL(child.valid(), true);
    BOOST_CHECK_NE(child.get_pid(), sheratan::process_impl::posix::process_id());

    // send child TERM signal
    child.kill(SIGTERM);

    // wait for the child process
    sheratan::process_impl::posix::exit_status term_status = child.join();

    // check that child process does not exist anymore
    BOOST_CHECK_EQUAL(child.valid(), false);
    BOOST_CHECK_EQUAL(child.get_pid(), sheratan::process_impl::posix::process_id());

    // check exit status of the child process
    BOOST_CHECK_EQUAL(term_status.exited(), false);
    BOOST_CHECK_EQUAL(term_status.signaled(), true);
    BOOST_CHECK_EQUAL(term_status.stopped(), false);
    BOOST_CHECK_EQUAL(term_status.continued(), false);
    BOOST_CHECK_EQUAL(term_status.dumped_core(), false);
    BOOST_CHECK_EQUAL(term_status.get_term_signal(), SIGTERM);
  }

BOOST_AUTO_TEST_SUITE_END() // process


} // anonymous namespace


// vim: set ts=2 sw=2 et:


