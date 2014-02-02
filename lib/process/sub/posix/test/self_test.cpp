/// \file process/sub/posix/test/self_test.cpp
/// \brief Self process POSIX implementation unit-test file.
/// \ingroup sheratan_process_posix_test
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#include <sys/types.h>
#include <unistd.h>

#include <boost/test/unit_test.hpp>

#include "sheratan/process/posix/self.hpp"


namespace {


BOOST_AUTO_TEST_SUITE(process)

  /// \brief Unit-test case: Process ID.
  BOOST_AUTO_TEST_CASE(process_id)
  {
    BOOST_CHECK_EQUAL(sheratan::process_impl::posix::self::get_pid().get_value(), getpid());
  }

  /// \brief Unit-test case: Parent process ID.
  BOOST_AUTO_TEST_CASE(parent_process_id)
  {
    BOOST_CHECK_EQUAL(sheratan::process_impl::posix::self::get_parent_pid().get_value(), getppid());
  }

BOOST_AUTO_TEST_SUITE_END() // process


} // anonymous namespace


// vim: set ts=2 sw=2 et:


