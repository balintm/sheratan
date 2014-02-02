/// \file process/sub/posix/test/daemon_test.cpp
/// \brief Daemon POSIX implementation unit-test file.
/// \ingroup sheratan_process_posix_test
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#include <boost/test/unit_test.hpp>
#include "boost_test_sigchld_suppressor.hpp"

#include "sheratan/errhdl/exception.hpp"
#include "sheratan/process/posix/daemon_template.hpp"
#include "test_daemon_ctl.hpp"


using namespace sheratan::process_impl::posix::test;


namespace {

/// \brief Test daemon type definition.
typedef sheratan::process_impl::posix::daemon_template<struct test_daemon_tag> test_daemon;

BOOST_AUTO_TEST_SUITE(daemon)

  /// \brief Unit-test case: Default construction.
  BOOST_AUTO_TEST_CASE(default_construction)
  {
    // default construction
    test_daemon default_constructed;
    BOOST_CHECK_EQUAL(default_constructed.valid(), false);
    BOOST_CHECK_EQUAL(default_constructed.get_pid(), sheratan::process_impl::posix::process_id());
  }

  /// \brief Unit-test case: Daemon.
  BOOST_AUTO_TEST_CASE(daemon)
  {
    // ignore SIGCHLD in order to make Boost.Test shut up
    // about child process exiting with nonzero status
    sheratan::process_impl::posix::test::boost_test_sigchld_suppressor sigchld_suppressor;
    // make compiler shut up about unused variable sigchld_suppressor
    sigchld_suppressor.no_op();

    // create daemon
    test_daemon_ctl dc;
    test_daemon daemon_process(
      dc,
      sheratan::process_impl::posix::daemonizer::pid_file_type("/tmp/sheratan_process_posix_daemon.pid"),
      sheratan::process_impl::posix::daemonizer::pid_file_mode_type(
        sheratan::process_impl::posix::file_permissions::USER_READ
        |
        sheratan::process_impl::posix::file_permissions::USER_WRITE
        |
        sheratan::process_impl::posix::file_permissions::GROUP_READ
        |
        sheratan::process_impl::posix::file_permissions::GROUP_WRITE
      ),
      /// \todo Investigate case with non-existent working dir.
      sheratan::process_impl::posix::daemonizer::working_dir_type("./"),
      sheratan::process_impl::posix::daemonizer::stdin_redirect_type("/dev/null"),
      sheratan::process_impl::posix::daemonizer::stdout_redirect_type("/dev/null"),
      sheratan::process_impl::posix::daemonizer::stderr_redirect_type("/dev/null"),
      sheratan::process_impl::posix::daemonizer::reset_signals_flag_type(true)
    );

    // check that valid daemon process exists (or at least existed)
    BOOST_CHECK_EQUAL(daemon_process.valid(), true);
    BOOST_CHECK_NE(daemon_process.get_pid(), sheratan::process_impl::posix::process_id());
  }

BOOST_AUTO_TEST_SUITE_END() // process


} // anonymous namespace


// vim: set ts=2 sw=2 et:


