/// \file errhdl/test/error_code_test.cpp
/// \brief Error code unit-test file.
/// \ingroup sheratan_errhdl_test
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#include <boost/test/unit_test.hpp>

#include "sheratan/errhdl/error_code.hpp"
#include "sheratan/errhdl/default_category.hpp"
#include "test_category.hpp"

using namespace sheratan::errhdl::test;


namespace {


BOOST_AUTO_TEST_SUITE(error_code)

  /// \brief Unit-test case: Construction.
  BOOST_AUTO_TEST_CASE(construction)
  {
    // default construction
    sheratan::errhdl::error_code default_constructed;
    BOOST_CHECK_EQUAL(default_constructed.get_errnum(), sheratan::errhdl::get_default_category().get_default_errnum());
    BOOST_CHECK(default_constructed.get_category() == sheratan::errhdl::get_default_category());

    // construction with errnum and category arguments
    sheratan::errhdl::error_code errnum_category(test_errnum::ERROR_1, get_test_category());
    BOOST_CHECK_EQUAL(errnum_category.get_errnum(), test_errnum::ERROR_1);
    BOOST_CHECK(errnum_category.get_category() == get_test_category());
  }

  /// \brief Unit-test case: Copy construction.
  BOOST_AUTO_TEST_CASE(copy_construction)
  {
    // create original and its copy via copy construction
    sheratan::errhdl::error_code orig(test_errnum::ERROR_1, get_test_category());
    sheratan::errhdl::error_code copy(orig);

    // test that they are equal
    BOOST_CHECK_EQUAL(copy.get_errnum(), orig.get_errnum());
    BOOST_CHECK(copy.get_category() == orig.get_category());
  }

  /// \brief Unit-test case: Assignment.
  BOOST_AUTO_TEST_CASE(assignment)
  {
    // create original and its copy via assignment
    sheratan::errhdl::error_code orig(test_errnum::ERROR_1, get_test_category());
    sheratan::errhdl::error_code assigned;
    assigned = orig;

    // test that they are equal
    BOOST_CHECK_EQUAL(assigned.get_errnum(), orig.get_errnum());
    BOOST_CHECK(assigned.get_category() == orig.get_category());
  }

  /// \brief Unit-test case: Non-throwing swap.
  BOOST_AUTO_TEST_CASE(swap)
  {
    // create two different error codes
    sheratan::errhdl::error_code code1(test_errnum::ERROR_1, get_test_category());
    sheratan::errhdl::error_code code2(test_errnum::ERROR_2, get_test_category());

    // swap two instances
    using std::swap;
    BOOST_CHECK_NO_THROW(swap(code1, code2));

    // check that two instances are swapped
    BOOST_CHECK_EQUAL(code1.get_errnum(), test_errnum::ERROR_2);
    BOOST_CHECK_EQUAL(code2.get_errnum(), test_errnum::ERROR_1);
  }

  /// \brief Unit-test case: Comparison.
  BOOST_AUTO_TEST_CASE(comparison)
  {
    // create two different error codes
    sheratan::errhdl::error_code code1(test_errnum::ERROR_1, get_test_category());
    sheratan::errhdl::error_code code2(test_errnum::ERROR_2, get_test_category());

    // check comparison operators
    BOOST_CHECK(code1 == code1);
    BOOST_CHECK(code2 == code2);
    BOOST_CHECK(code1 != code2);
    BOOST_CHECK(code2 != code1);
  }

  /// \brief Unit-test case: Set data.
  BOOST_AUTO_TEST_CASE(set_data)
  {
    // create default constructed error code and set its errnum and category using setter method
    sheratan::errhdl::error_code code;
    code.set_error_code(test_errnum::ERROR_1, get_test_category());

    // check that errnum and category was set
    BOOST_CHECK_EQUAL(code.get_errnum(), test_errnum::ERROR_1);
    BOOST_CHECK(code.get_category() == get_test_category());
  }

BOOST_AUTO_TEST_SUITE_END() // error_code


} // anonymous namespace


// vim: set ts=2 sw=2 et:


