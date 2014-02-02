/// \file process/sub/posix/test/exit_status_test.cpp
/// \brief Process exit status POSIX implementation unit-test file.
/// \ingroup sheratan_process_posix_test
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#include <sys/wait.h>

#include <boost/test/unit_test.hpp>

#include "sheratan/process/posix/exit_status.hpp"
#include "accessor.hpp"


namespace {


BOOST_AUTO_TEST_SUITE(exit_status)

  /// \brief Unit-test case: Construction.
  BOOST_AUTO_TEST_CASE(construction)
  {
    // default construction
    sheratan::process_impl::posix::exit_status default_constructed;
    BOOST_CHECK_EQUAL(default_constructed.valid(), false);

    // construction with value argument
    sheratan::process_impl::posix::test::accessor::exit_status_ptr status = sheratan::process_impl::posix::test::accessor::exit_status__exit_status(42);
    BOOST_CHECK_EQUAL(status->valid(), true);
    BOOST_CHECK_EQUAL(status->get_value(), 42);
  }

  /// \brief Unit-test case: Copy construction.
  BOOST_AUTO_TEST_CASE(copy_construction)
  {
    // create original and its copy via copy construction
    sheratan::process_impl::posix::test::accessor::exit_status_ptr orig = sheratan::process_impl::posix::test::accessor::exit_status__exit_status(42);
    sheratan::process_impl::posix::exit_status copy(*orig);

    // test that they are equal
    BOOST_CHECK_EQUAL(copy.valid(), true);
    BOOST_CHECK_EQUAL(copy.get_value(), orig->get_value());
  }

  /// \brief Unit-test case: Non-throwing swap.
  BOOST_AUTO_TEST_CASE(swap)
  {
    // create two different exit statuses
    sheratan::process_impl::posix::test::accessor::exit_status_ptr status1 = sheratan::process_impl::posix::test::accessor::exit_status__exit_status(42);
    sheratan::process_impl::posix::test::accessor::exit_status_ptr status2 = sheratan::process_impl::posix::test::accessor::exit_status__exit_status(23);

    // swap two instances
    using std::swap;
    BOOST_CHECK_NO_THROW(swap(*status1, *status2));

    // check that two instances are swapped
    BOOST_CHECK_EQUAL(status1->valid(), true);
    BOOST_CHECK_EQUAL(status1->get_value(), 23);
    BOOST_CHECK_EQUAL(status2->valid(), true);
    BOOST_CHECK_EQUAL(status2->get_value(), 42);
  }

  /// \brief Unit-test case: Exited flag.
  BOOST_AUTO_TEST_CASE(exited_flag)
  {
    // create exit status with exited flag set
    // - Linux: value & 0x7f == 0
    sheratan::process_impl::posix::test::accessor::exit_status_ptr exited = sheratan::process_impl::posix::test::accessor::exit_status__exit_status(0);

    // check that exited flag is set
    BOOST_CHECK_EQUAL(exited->valid(), true);
    BOOST_CHECK_EQUAL(exited->exited(), true);

    // create exit status with exited flag cleared
    // - Linux: value & 0x7f != 0
    sheratan::process_impl::posix::test::accessor::exit_status_ptr not_exited = sheratan::process_impl::posix::test::accessor::exit_status__exit_status(1);

    // check that exited flag is not set
    BOOST_CHECK_EQUAL(not_exited->valid(), true);
    BOOST_CHECK_EQUAL(not_exited->exited(), false);
  }

  /// \brief Unit-test case: Exit status.
  BOOST_AUTO_TEST_CASE(exit_status)
  {
    // create exit status with exited flag set and status 42
    // - Linux: value & 0x7f == 0, (value >> 8) & 0xff == status
    sheratan::process_impl::posix::test::accessor::exit_status_ptr status = sheratan::process_impl::posix::test::accessor::exit_status__exit_status(42 << 8);

    // exited flag must be set
    BOOST_CHECK_EQUAL(status->valid(), true);
    BOOST_CHECK_EQUAL(status->exited(), true);
    BOOST_CHECK_EQUAL(status->get_status(), 42);

    // all other flags must be celared
    BOOST_CHECK_EQUAL(status->signaled(), false);
    BOOST_CHECK_EQUAL(status->stopped(), false);
    BOOST_CHECK_EQUAL(status->continued(), false);
    BOOST_CHECK_EQUAL(status->dumped_core(), false);
  }

  /// \brief Unit-test case: Signaled flag.
  BOOST_AUTO_TEST_CASE(signaled_flag)
  {
    // create exit status with signaled flag set
    // - Linux: (signed char) ((value & 0x7f) + 1) >> 1 > 0
    sheratan::process_impl::posix::test::accessor::exit_status_ptr signaled = sheratan::process_impl::posix::test::accessor::exit_status__exit_status(1);

    // check that signaled flag is set
    BOOST_CHECK_EQUAL(signaled->valid(), true);
    BOOST_CHECK_EQUAL(signaled->signaled(), true);

    // create exit status with signaled flag cleared
    // - Linux: (signed char) ((value & 0x7f) + 1) >> 1 <= 0
    sheratan::process_impl::posix::test::accessor::exit_status_ptr not_signaled  = sheratan::process_impl::posix::test::accessor::exit_status__exit_status(0);

    // check that signaled flag is not set
    BOOST_CHECK_EQUAL(not_signaled->signaled(), false);
  }

  /// \brief Unit-test case: Terminating signal.
  BOOST_AUTO_TEST_CASE(terminating_signal)
  {
    // create exit status with signaled flag set and terminating signal 42
    // - Linux: (signed char) ((value & 0x7f) + 1) >> 1 > 0, value & 0x7f == signal
    sheratan::process_impl::posix::test::accessor::exit_status_ptr status = sheratan::process_impl::posix::test::accessor::exit_status__exit_status(42);

    // signaled flag must be set
    BOOST_CHECK_EQUAL(status->valid(), true);
    BOOST_CHECK_EQUAL(status->signaled(), true);

    // all other flags must be celared
    BOOST_CHECK_EQUAL(status->exited(), false);
    BOOST_CHECK_EQUAL(status->stopped(), false);
    BOOST_CHECK_EQUAL(status->continued(), false);
    BOOST_CHECK_EQUAL(status->dumped_core(), false);

    // check terminating signal
    BOOST_CHECK_EQUAL(status->get_term_signal(), 42);
  }

  /// \brief Unit-test case: Stopped flag.
  BOOST_AUTO_TEST_CASE(stopped_flag)
  {
    // create exit status with stopped flag set
    // - Linux: value & 0xff == 0x7f
    sheratan::process_impl::posix::test::accessor::exit_status_ptr stopped = sheratan::process_impl::posix::test::accessor::exit_status__exit_status(0x7f);

    // check that stopped flag is set
    BOOST_CHECK_EQUAL(stopped->valid(), true);
    BOOST_CHECK_EQUAL(stopped->stopped(), true);

    // create exit status with stopped flag cleared
    // - Linux: value & 0xff != 0x7f
    sheratan::process_impl::posix::test::accessor::exit_status_ptr not_stopped  = sheratan::process_impl::posix::test::accessor::exit_status__exit_status(0);

    // check that stopped flag is not set
    BOOST_CHECK_EQUAL(not_stopped->valid(), true);
    BOOST_CHECK_EQUAL(not_stopped->stopped(), false);
  }

  /// \brief Unit-test case: Stop signal.
  BOOST_AUTO_TEST_CASE(stop_signal)
  {
    // create exit status with stopped flag set and stop signal 42
    // - Linux: value & 0xff == 0x7f, (value >> 8) & 0xff == stop signal
    sheratan::process_impl::posix::test::accessor::exit_status_ptr status = sheratan::process_impl::posix::test::accessor::exit_status__exit_status((42 << 8) + 0x7f);

    // stop flag must be set
    BOOST_CHECK_EQUAL(status->valid(), true);
    BOOST_CHECK_EQUAL(status->stopped(), true);

    // all other flags must be celared
    BOOST_CHECK_EQUAL(status->exited(), false);
    BOOST_CHECK_EQUAL(status->signaled(), false);
    BOOST_CHECK_EQUAL(status->continued(), false);
    BOOST_CHECK_EQUAL(status->dumped_core(), false);

    // check terminating signal
    BOOST_CHECK_EQUAL(status->get_stop_signal(), 42);
  }

  /// \brief Unit-test case: Continued flag.
  BOOST_AUTO_TEST_CASE(continued_flag)
  {
    // create exit status with continued flag set
    // - Linux: value == 0xffff
    sheratan::process_impl::posix::test::accessor::exit_status_ptr continued = sheratan::process_impl::posix::test::accessor::exit_status__exit_status(0xffff);

    // create exit status with continued flag cleared
    // - Linux: value != 0xffff
    sheratan::process_impl::posix::test::accessor::exit_status_ptr not_continued = sheratan::process_impl::posix::test::accessor::exit_status__exit_status(0);

#   ifdef WIFCONTINUED
      // check continued flag value
      BOOST_CHECK_EQUAL(continued->valid(), true);
      BOOST_CHECK_EQUAL(continued->continued(), true);
      BOOST_CHECK_EQUAL(not_continued->continued(), false);
#   else
      // check continued flag value
      BOOST_CHECK_EQUAL(continued->valid(), true);
      BOOST_CHECK_EQUAL(continued->continued(), false);
      BOOST_CHECK_EQUAL(not_continued->continued(), false);
#   endif
  }

  /// \brief Unit-test case: Coredump flag.
  BOOST_AUTO_TEST_CASE(coredump_flag)
  {
    // create exit status with coredump flag set
    // - Linux: value & 0x80 == 0x80
    sheratan::process_impl::posix::test::accessor::exit_status_ptr coredump = sheratan::process_impl::posix::test::accessor::exit_status__exit_status(0x80);

    // create exit status with coredump flag cleared
    // - Linux: value & 0x80 == 0x80
    sheratan::process_impl::posix::test::accessor::exit_status_ptr not_coredump  = sheratan::process_impl::posix::test::accessor::exit_status__exit_status(0);

#   ifdef WCOREDUMP
      // check coredump flag value
      BOOST_CHECK_EQUAL(coredump->valid(), true);
      BOOST_CHECK_EQUAL(coredump->dumped_core(), true);
      BOOST_CHECK_EQUAL(not_coredump->dumped_core(), false);
#   else
      // check that coredump flag is not set in any case
      BOOST_CHECK_EQUAL(coredump->valid(), true);
      BOOST_CHECK_EQUAL(coredump->dumped_core(), false);
      BOOST_CHECK_EQUAL(not_coredump->dumped_core(), false);
#   endif
  }

BOOST_AUTO_TEST_SUITE_END() // exit_status


} // anonymous namespace


// vim: set ts=2 sw=2 et:


