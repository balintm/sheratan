/// \file errhdl/test/assert_test.cpp
/// \brief Assertion unit-test file.
/// \ingroup sheratan_errhdl_test
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#include <boost/test/unit_test.hpp>

#include "sheratan/errhdl/assert.hpp"


namespace {


BOOST_AUTO_TEST_SUITE(assert)

  /// \brief Unit-test case: Assertion (error level: warning).
  BOOST_AUTO_TEST_CASE(assert_warn)
  {
    // check that satisfied assertions do nothing
    BOOST_CHECK_NO_THROW(SHERATAN_WARN(true));

    // exception thrown flag
    bool exception_thrown = false;

    // make unsatisfied assertion
    try {
      SHERATAN_WARN(false);
    }
    // catch thrown exception and check error information
    catch(sheratan::errhdl::logic_error &ex) {
      exception_thrown = true;
      BOOST_CHECK(get_code(ex) == sheratan::errhdl::error_code(sheratan::errhdl::assert_errnum::WARNING, sheratan::errhdl::get_assert_category()));
      BOOST_CHECK_EQUAL(get_file(ex), __FILE__);
      BOOST_CHECK_EQUAL(get_line(ex), 28);
      BOOST_CHECK_EQUAL(get_failed_assertion(ex), "false");
    }

    // check that exception was thrown
    BOOST_REQUIRE_EQUAL(exception_thrown, true);
  }

  /// \brief Unit-test case: Assertion (error level: error).
  BOOST_AUTO_TEST_CASE(assert_error)
  {
    // check that satisfied assertions do nothing
    BOOST_CHECK_NO_THROW(SHERATAN_CHECK(true));

    // exception thrown flag
    bool exception_thrown = false;

    // make unsatisfied assertion
    try {
      SHERATAN_CHECK(false);
    }
    // catch thrown exception and check error information
    catch(sheratan::errhdl::logic_error &ex) {
      exception_thrown = true;
      BOOST_CHECK(get_code(ex) == sheratan::errhdl::error_code(sheratan::errhdl::assert_errnum::ERROR, sheratan::errhdl::get_assert_category()));
      BOOST_CHECK_EQUAL(get_file(ex), __FILE__);
      BOOST_CHECK_EQUAL(get_line(ex), 54);
      BOOST_CHECK_EQUAL(get_failed_assertion(ex), "false");
    }

    // check that exception was thrown
    BOOST_REQUIRE_EQUAL(exception_thrown, true);
  }

  /// \brief Unit-test case: Assertion (error level: fatal error).
  BOOST_AUTO_TEST_CASE(assert_fatal)
  {
    // check that satisfied assertions do nothing
    BOOST_CHECK_NO_THROW(SHERATAN_REQUIRE(true));

    // exception thrown flag
    bool exception_thrown = false;

    // make unsatisfied assertion
    try {
      SHERATAN_REQUIRE(false);
    }
    // catch thrown exception and check error information
    catch(sheratan::errhdl::logic_error &ex) {
      exception_thrown = true;
      BOOST_CHECK(get_code(ex) == sheratan::errhdl::error_code(sheratan::errhdl::assert_errnum::FATAL, sheratan::errhdl::get_assert_category()));
      BOOST_CHECK_EQUAL(get_file(ex), __FILE__);
      BOOST_CHECK_EQUAL(get_line(ex), 80);
      BOOST_CHECK_EQUAL(get_failed_assertion(ex), "false");
    }

    // check that exception was thrown
    BOOST_REQUIRE_EQUAL(exception_thrown, true);
  }

BOOST_AUTO_TEST_SUITE_END() // assert


} // anonymous namespace


// vim: set ts=2 sw=2 et:


