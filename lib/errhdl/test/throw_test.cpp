/// \file errhdl/test/throw_test.cpp
/// \brief Exception throwing unit-test file.
/// \ingroup sheratan_errhdl_test
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#include <boost/test/unit_test.hpp>

#include "sheratan/errhdl/throw.hpp"
#include "test_category.hpp"


using namespace sheratan::errhdl::test;


namespace {


BOOST_AUTO_TEST_SUITE(throw_exception)

  /// \brief Unit-test case: Throwing exception.
  BOOST_AUTO_TEST_CASE(throw_exception)
  {
    // exception thrown flag
    bool exception_thrown = false;

    // throw exception
    try {
      sheratan::errhdl::runtime_error ex_to_throw;
      ex_to_throw << test_category::error_info::testing_data(42);
      SHERATAN_THROW_EXCEPTION(ex_to_throw, sheratan::errhdl::error_code(test_errnum::ERROR_1, get_test_category()));
    }
    // catch it and check error information
    catch(sheratan::errhdl::exception &ex) {
      exception_thrown = true;
      BOOST_CHECK(get_code(ex) == sheratan::errhdl::error_code(test_errnum::ERROR_1, get_test_category()));
      BOOST_CHECK_EQUAL(get_file(ex), __FILE__);
      BOOST_CHECK_EQUAL(get_line(ex), 31);
      BOOST_CHECK_EQUAL(get_testing_data(ex), 42);
    }

    // check that exception was thrown
    BOOST_REQUIRE_EQUAL(exception_thrown, true);
  }

  /// \brief Unit-test case: Translating exception.
  BOOST_AUTO_TEST_CASE(translate_exception)
  {
    // exception thrown flag
    bool exception_translated = false;

    // throw exception
    try {
      try {
        sheratan::errhdl::logic_error ex_to_throw;
        ex_to_throw << test_category::error_info::testing_data(42);
        SHERATAN_THROW_EXCEPTION(ex_to_throw, sheratan::errhdl::error_code(test_errnum::ERROR_1, get_test_category()));
      }
      // catch and translate exception
      catch(sheratan::errhdl::exception &ex) {
        BOOST_CHECK(get_code(ex) == sheratan::errhdl::error_code(test_errnum::ERROR_1, get_test_category()));
        BOOST_CHECK_EQUAL(get_file(ex), __FILE__);
        BOOST_CHECK_EQUAL(get_line(ex), 57);
        BOOST_CHECK_EQUAL(get_testing_data(ex), 42);

        sheratan::errhdl::runtime_error ex_to_throw;
        ex_to_throw << test_category::error_info::testing_data(23);
        SHERATAN_TRANSLATE_EXCEPTION(ex_to_throw, sheratan::errhdl::error_code(test_errnum::ERROR_2, get_test_category()), ex);
      }
    }
    // catch it and check error information
    catch(sheratan::errhdl::exception &ex) {
      exception_translated = true;
      BOOST_CHECK(get_code(ex) == sheratan::errhdl::error_code(test_errnum::ERROR_2, get_test_category()));
      BOOST_CHECK_EQUAL(get_file(ex), __FILE__);
      BOOST_CHECK_EQUAL(get_line(ex), 68);
      BOOST_CHECK_EQUAL(get_testing_data(ex), 23);
      sheratan::errhdl::exception::iterator cause = ex.begin();
      ++cause;
      BOOST_CHECK(get_code(*cause) == sheratan::errhdl::error_code(test_errnum::ERROR_1, get_test_category()));
      BOOST_CHECK_EQUAL(get_file(*cause), __FILE__);
      BOOST_CHECK_EQUAL(get_line(*cause), 57);
      BOOST_CHECK_EQUAL(get_testing_data(*cause), 42);
    }

    // check that exception was translated
    BOOST_REQUIRE_EQUAL(exception_translated, true);
  }

BOOST_AUTO_TEST_SUITE_END() // throw_exception


} // anonymous namespace


// vim: set ts=2 sw=2 et:


