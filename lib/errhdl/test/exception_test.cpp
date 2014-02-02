/// \file errhdl/test/exception_test.cpp
/// \brief Exception unit-test file.
/// \ingroup sheratan_errhdl_test
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#include <boost/test/unit_test.hpp>

#include "sheratan/errhdl/exception.hpp"
#include "test_category.hpp"


using namespace sheratan::errhdl::test;


namespace {


BOOST_AUTO_TEST_SUITE(exception)

  /// \brief Unit-test case: Error information.
  BOOST_AUTO_TEST_CASE(error_info)
  {
    // create exception with error information
    sheratan::errhdl::runtime_error runtime_error;
    runtime_error
      << sheratan::errhdl::error_info::code(sheratan::errhdl::error_code(test_errnum::ERROR_1, get_test_category()))
      << sheratan::errhdl::error_info::file(__FILE__)
      << sheratan::errhdl::error_info::line(42)
      << sheratan::errhdl::error_info::seconds(2048)
      << sheratan::errhdl::error_info::useconds(1024)
      << sheratan::errhdl::test::test_category::error_info::testing_data(32)
    ;

    // check stored error information
    BOOST_CHECK(get_code(runtime_error) == sheratan::errhdl::error_code(test_errnum::ERROR_1, get_test_category()));
    BOOST_CHECK_EQUAL(get_file(runtime_error), __FILE__);
    BOOST_CHECK_EQUAL(get_line(runtime_error), 42);
    BOOST_CHECK_EQUAL(get_seconds(runtime_error), 2048);
    BOOST_CHECK_EQUAL(get_useconds(runtime_error), 1024);
    BOOST_CHECK_EQUAL(get_testing_data(runtime_error), 32);

    // create exception with error information
    sheratan::errhdl::logic_error logic_error;
    logic_error
      << sheratan::errhdl::error_info::code(sheratan::errhdl::error_code(test_errnum::ERROR_2, get_test_category()))
      << sheratan::errhdl::error_info::file(__FILE__)
      << sheratan::errhdl::error_info::line(23)
      << sheratan::errhdl::error_info::seconds(4096)
      << sheratan::errhdl::error_info::useconds(2048)
      << sheratan::errhdl::test::test_category::error_info::testing_data(32)
    ;

    // check stored error information
    BOOST_CHECK(get_code(logic_error) == sheratan::errhdl::error_code(test_errnum::ERROR_2, get_test_category()));
    BOOST_CHECK_EQUAL(get_file(logic_error), __FILE__);
    BOOST_CHECK_EQUAL(get_line(logic_error), 23);
    BOOST_CHECK_EQUAL(get_seconds(logic_error), 4096);
    BOOST_CHECK_EQUAL(get_useconds(logic_error), 2048);
    BOOST_CHECK_EQUAL(get_testing_data(logic_error), 32);
  }

  /// \brief Unit-test case: Error information in catched exception.
  BOOST_AUTO_TEST_CASE(catched_error_info)
  {
    // throw exception with error information
    try {
      throw sheratan::errhdl::runtime_error()
        << sheratan::errhdl::error_info::code(sheratan::errhdl::error_code(test_errnum::ERROR_1, get_test_category()))
        << sheratan::errhdl::error_info::file(__FILE__)
        << sheratan::errhdl::error_info::line(42)
        << sheratan::errhdl::error_info::seconds(2048)
        << sheratan::errhdl::error_info::useconds(1024)
        << sheratan::errhdl::test::test_category::error_info::testing_data(32)
      ;
    }
    // catch it and check stored information
    catch(sheratan::errhdl::exception &ex) {
      BOOST_CHECK(get_code(ex) == sheratan::errhdl::error_code(test_errnum::ERROR_1, get_test_category()));
      BOOST_CHECK_EQUAL(get_file(ex), __FILE__);
      BOOST_CHECK_EQUAL(get_line(ex), 42);
      BOOST_CHECK_EQUAL(get_seconds(ex), 2048);
      BOOST_CHECK_EQUAL(get_useconds(ex), 1024);
      BOOST_CHECK_EQUAL(get_testing_data(ex), 32);
    }

    // throw exception with error information
    try {
      throw sheratan::errhdl::logic_error()
        << sheratan::errhdl::error_info::code(sheratan::errhdl::error_code(test_errnum::ERROR_2, get_test_category()))
        << sheratan::errhdl::error_info::file(__FILE__)
        << sheratan::errhdl::error_info::line(23)
        << sheratan::errhdl::error_info::seconds(4096)
        << sheratan::errhdl::error_info::useconds(2048)
        << sheratan::errhdl::test::test_category::error_info::testing_data(32)
      ;
    }
    // catch it and check stored information
    catch(sheratan::errhdl::exception &ex) {
      BOOST_CHECK(get_code(ex) == sheratan::errhdl::error_code(test_errnum::ERROR_2, get_test_category()));
      BOOST_CHECK_EQUAL(get_file(ex), __FILE__);
      BOOST_CHECK_EQUAL(get_line(ex), 23);
      BOOST_CHECK_EQUAL(get_seconds(ex), 4096);
      BOOST_CHECK_EQUAL(get_useconds(ex), 2048);
      BOOST_CHECK_EQUAL(get_testing_data(ex), 32);
    }
  }

  /// \brief Unit-test case: Error trace.
  BOOST_AUTO_TEST_CASE(error_trace)
  {
    // create exception with error trace
    sheratan::errhdl::runtime_error ex0;
    ex0 << sheratan::errhdl::error_info::code(sheratan::errhdl::error_code(test_errnum::UNKNOWN, get_test_category()));
    sheratan::errhdl::logic_error ex1;
    ex1 << sheratan::errhdl::error_info::code(sheratan::errhdl::error_code(test_errnum::ERROR_1, get_test_category()));
    ex1 << sheratan::errhdl::error_info::cause(sheratan::errhdl::error_info::cause_type(ex0.clone()));
    sheratan::errhdl::runtime_error ex2;
    ex2 << sheratan::errhdl::error_info::code(sheratan::errhdl::error_code(test_errnum::ERROR_2, get_test_category()));
    ex2 << sheratan::errhdl::error_info::cause(sheratan::errhdl::error_info::cause_type(ex1.clone()));
    sheratan::errhdl::exception &ex = ex2;
    const sheratan::errhdl::exception &cex = ex2;

    // initialize trace iterators
    sheratan::errhdl::exception::iterator ex_i = ex.begin();
    sheratan::errhdl::exception::iterator ex_end = ex.end();
    sheratan::errhdl::exception::const_iterator ex_ci = cex.begin();
    sheratan::errhdl::exception::const_iterator ex_cend = cex.end();
    sheratan::errhdl::exception::const_iterator ex_cci = ex_i;
    sheratan::errhdl::exception::const_iterator ex_ccend = ex_end;

    // check the first trace item
    BOOST_REQUIRE(ex_i != ex_end);
    BOOST_CHECK(get_code(*ex_i) == sheratan::errhdl::error_code(test_errnum::ERROR_2, get_test_category()));
    BOOST_REQUIRE(ex_ci != ex_cend);
    BOOST_CHECK(get_code(*ex_ci) == sheratan::errhdl::error_code(test_errnum::ERROR_2, get_test_category()));
    BOOST_REQUIRE(ex_cci != ex_ccend);
    BOOST_CHECK(get_code(*ex_cci) == sheratan::errhdl::error_code(test_errnum::ERROR_2, get_test_category()));
    BOOST_REQUIRE(static_cast<sheratan::errhdl::exception::const_iterator>(ex_i) != static_cast<sheratan::errhdl::exception::const_iterator>(ex_end));
    BOOST_CHECK(get_code(*static_cast<sheratan::errhdl::exception::const_iterator>(ex_i)) == sheratan::errhdl::error_code(test_errnum::ERROR_2, get_test_category()));
    BOOST_REQUIRE(static_cast<sheratan::errhdl::exception::const_iterator>(ex_ci) != static_cast<sheratan::errhdl::exception::const_iterator>(ex_cend));
    BOOST_CHECK(get_code(*static_cast<sheratan::errhdl::exception::const_iterator>(ex_ci)) == sheratan::errhdl::error_code(test_errnum::ERROR_2, get_test_category()));

    // move to the second trace item
    ++ex_i; ++ex_ci; ++ex_cci;

    // check the second trace item
    BOOST_REQUIRE(ex_i != ex_end);
    BOOST_CHECK(get_code(*ex_i) == sheratan::errhdl::error_code(test_errnum::ERROR_1, get_test_category()));
    BOOST_REQUIRE(ex_ci != ex_cend);
    BOOST_CHECK(get_code(*ex_ci) == sheratan::errhdl::error_code(test_errnum::ERROR_1, get_test_category()));
    BOOST_REQUIRE(ex_cci != ex_ccend);
    BOOST_CHECK(get_code(*ex_cci) == sheratan::errhdl::error_code(test_errnum::ERROR_1, get_test_category()));
    BOOST_REQUIRE(static_cast<sheratan::errhdl::exception::const_iterator>(ex_i) != static_cast<sheratan::errhdl::exception::const_iterator>(ex_end));
    BOOST_CHECK(get_code(*static_cast<sheratan::errhdl::exception::const_iterator>(ex_i)) == sheratan::errhdl::error_code(test_errnum::ERROR_1, get_test_category()));
    BOOST_REQUIRE(static_cast<sheratan::errhdl::exception::const_iterator>(ex_ci) != static_cast<sheratan::errhdl::exception::const_iterator>(ex_cend));
    BOOST_CHECK(get_code(*static_cast<sheratan::errhdl::exception::const_iterator>(ex_ci)) == sheratan::errhdl::error_code(test_errnum::ERROR_1, get_test_category()));

    // move to the third trace item
    ++ex_i; ++ex_ci; ++ex_cci;

    // check the third trace item
    BOOST_REQUIRE(ex_i != ex_end);
    BOOST_CHECK(get_code(*ex_i) == sheratan::errhdl::error_code(test_errnum::UNKNOWN, get_test_category()));
    BOOST_REQUIRE(ex_ci != ex_cend);
    BOOST_CHECK(get_code(*ex_ci) == sheratan::errhdl::error_code(test_errnum::UNKNOWN, get_test_category()));
    BOOST_REQUIRE(ex_cci != ex_ccend);
    BOOST_CHECK(get_code(*ex_cci) == sheratan::errhdl::error_code(test_errnum::UNKNOWN, get_test_category()));
    BOOST_REQUIRE(static_cast<sheratan::errhdl::exception::const_iterator>(ex_i) != static_cast<sheratan::errhdl::exception::const_iterator>(ex_end));
    BOOST_CHECK(get_code(*static_cast<sheratan::errhdl::exception::const_iterator>(ex_i)) == sheratan::errhdl::error_code(test_errnum::UNKNOWN, get_test_category()));
    BOOST_REQUIRE(static_cast<sheratan::errhdl::exception::const_iterator>(ex_ci) != static_cast<sheratan::errhdl::exception::const_iterator>(ex_cend));
    BOOST_CHECK(get_code(*static_cast<sheratan::errhdl::exception::const_iterator>(ex_ci)) == sheratan::errhdl::error_code(test_errnum::UNKNOWN, get_test_category()));

    // move past-the-end of trace
    ++ex_i; ++ex_ci; ++ex_cci;

    // check that iterators point past-the-end of trace
    BOOST_CHECK(ex_i == ex_end);
    BOOST_CHECK(ex_ci == ex_cend);
    BOOST_CHECK(ex_cci == ex_ccend);
    BOOST_CHECK(static_cast<sheratan::errhdl::exception::const_iterator>(ex_i) == static_cast<sheratan::errhdl::exception::const_iterator>(ex_end));
  }

  /// \brief Unit-test case: Error trace in catched exception.
  BOOST_AUTO_TEST_CASE(catched_error_trace)
  {
    // create exception with error trace
    try {
      try {
        try {
          throw sheratan::errhdl::runtime_error()
            << sheratan::errhdl::error_info::code(sheratan::errhdl::error_code(test_errnum::UNKNOWN, get_test_category()))
          ;
        }
        catch(sheratan::errhdl::exception &ex) {
          throw sheratan::errhdl::logic_error()
            << sheratan::errhdl::error_info::code(sheratan::errhdl::error_code(test_errnum::ERROR_1, get_test_category()))
            << sheratan::errhdl::error_info::cause(sheratan::errhdl::error_info::cause_type(ex.clone()))
          ;
        }
      }
      catch(sheratan::errhdl::exception &ex) {
        throw sheratan::errhdl::runtime_error()
          << sheratan::errhdl::error_info::code(sheratan::errhdl::error_code(test_errnum::ERROR_2, get_test_category()))
          << sheratan::errhdl::error_info::cause(sheratan::errhdl::error_info::cause_type(ex.clone()))
        ;
      }
    }
    catch(sheratan::errhdl::exception &ex) {
      const sheratan::errhdl::exception &cex = ex;

      // initialize trace iterators
      sheratan::errhdl::exception::iterator ex_i = ex.begin();
      sheratan::errhdl::exception::iterator ex_end = ex.end();
      sheratan::errhdl::exception::const_iterator ex_ci = cex.begin();
      sheratan::errhdl::exception::const_iterator ex_cend = cex.end();
      sheratan::errhdl::exception::const_iterator ex_cci = ex_i;
      sheratan::errhdl::exception::const_iterator ex_ccend = ex_end;

      // check the first trace item
      BOOST_REQUIRE(ex_i != ex_end);
      BOOST_CHECK(get_code(*ex_i) == sheratan::errhdl::error_code(test_errnum::ERROR_2, get_test_category()));
      BOOST_REQUIRE(ex_ci != ex_cend);
      BOOST_CHECK(get_code(*ex_ci) == sheratan::errhdl::error_code(test_errnum::ERROR_2, get_test_category()));
      BOOST_REQUIRE(ex_cci != ex_ccend);
      BOOST_CHECK(get_code(*ex_cci) == sheratan::errhdl::error_code(test_errnum::ERROR_2, get_test_category()));
      BOOST_REQUIRE(static_cast<sheratan::errhdl::exception::const_iterator>(ex_i) != static_cast<sheratan::errhdl::exception::const_iterator>(ex_end));
      BOOST_CHECK(get_code(*static_cast<sheratan::errhdl::exception::const_iterator>(ex_i)) == sheratan::errhdl::error_code(test_errnum::ERROR_2, get_test_category()));
      BOOST_REQUIRE(static_cast<sheratan::errhdl::exception::const_iterator>(ex_ci) != static_cast<sheratan::errhdl::exception::const_iterator>(ex_cend));
      BOOST_CHECK(get_code(*static_cast<sheratan::errhdl::exception::const_iterator>(ex_ci)) == sheratan::errhdl::error_code(test_errnum::ERROR_2, get_test_category()));

      // move to the second trace item
      ++ex_i; ++ex_ci; ++ex_cci;

      // check the second trace item
      BOOST_REQUIRE(ex_i != ex_end);
      BOOST_CHECK(get_code(*ex_i) == sheratan::errhdl::error_code(test_errnum::ERROR_1, get_test_category()));
      BOOST_REQUIRE(ex_ci != ex_cend);
      BOOST_CHECK(get_code(*ex_ci) == sheratan::errhdl::error_code(test_errnum::ERROR_1, get_test_category()));
      BOOST_REQUIRE(ex_cci != ex_ccend);
      BOOST_CHECK(get_code(*ex_cci) == sheratan::errhdl::error_code(test_errnum::ERROR_1, get_test_category()));
      BOOST_REQUIRE(static_cast<sheratan::errhdl::exception::const_iterator>(ex_i) != static_cast<sheratan::errhdl::exception::const_iterator>(ex_end));
      BOOST_CHECK(get_code(*static_cast<sheratan::errhdl::exception::const_iterator>(ex_i)) == sheratan::errhdl::error_code(test_errnum::ERROR_1, get_test_category()));
      BOOST_REQUIRE(static_cast<sheratan::errhdl::exception::const_iterator>(ex_ci) != static_cast<sheratan::errhdl::exception::const_iterator>(ex_cend));
      BOOST_CHECK(get_code(*static_cast<sheratan::errhdl::exception::const_iterator>(ex_ci)) == sheratan::errhdl::error_code(test_errnum::ERROR_1, get_test_category()));

      // move to the third trace item
      ++ex_i; ++ex_ci; ++ex_cci;

      // check the third trace item
      BOOST_REQUIRE(ex_i != ex_end);
      BOOST_CHECK(get_code(*ex_i) == sheratan::errhdl::error_code(test_errnum::UNKNOWN, get_test_category()));
      BOOST_REQUIRE(ex_ci != ex_cend);
      BOOST_CHECK(get_code(*ex_ci) == sheratan::errhdl::error_code(test_errnum::UNKNOWN, get_test_category()));
      BOOST_REQUIRE(ex_cci != ex_ccend);
      BOOST_CHECK(get_code(*ex_cci) == sheratan::errhdl::error_code(test_errnum::UNKNOWN, get_test_category()));
      BOOST_REQUIRE(static_cast<sheratan::errhdl::exception::const_iterator>(ex_i) != static_cast<sheratan::errhdl::exception::const_iterator>(ex_end));
      BOOST_CHECK(get_code(*static_cast<sheratan::errhdl::exception::const_iterator>(ex_i)) == sheratan::errhdl::error_code(test_errnum::UNKNOWN, get_test_category()));
      BOOST_REQUIRE(static_cast<sheratan::errhdl::exception::const_iterator>(ex_ci) != static_cast<sheratan::errhdl::exception::const_iterator>(ex_cend));
      BOOST_CHECK(get_code(*static_cast<sheratan::errhdl::exception::const_iterator>(ex_ci)) == sheratan::errhdl::error_code(test_errnum::UNKNOWN, get_test_category()));

      // move past-the-end of trace
      ++ex_i; ++ex_ci; ++ex_cci;

      // check that iterators point past-the-end of trace
      BOOST_CHECK(ex_i == ex_end);
      BOOST_CHECK(ex_ci == ex_cend);
      BOOST_CHECK(ex_cci == ex_ccend);
      BOOST_CHECK(static_cast<sheratan::errhdl::exception::const_iterator>(ex_i) == static_cast<sheratan::errhdl::exception::const_iterator>(ex_end));
    }
  }

BOOST_AUTO_TEST_SUITE_END() // exception


} // anonymous namespace


// vim: set ts=2 sw=2 et:


