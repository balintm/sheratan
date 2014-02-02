/// \file errhdl/test/default_category_test.cpp
/// \brief Default error category unit-test file.
/// \ingroup sheratan_errhdl_test
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#include <boost/test/unit_test.hpp>

#include "sheratan/errhdl/default_category.hpp"


namespace {


BOOST_AUTO_TEST_SUITE(default_category)

  /// \brief Unit-test case: Get name.
  BOOST_AUTO_TEST_CASE(name)
  {
    BOOST_CHECK_EQUAL(sheratan::errhdl::get_default_category().get_name(), "unknown error");
  }

  /// \brief Unit-test case: Comparison.
  BOOST_AUTO_TEST_CASE(comparison)
  {
    BOOST_CHECK(sheratan::errhdl::get_default_category() == sheratan::errhdl::get_default_category());
    BOOST_CHECK(!(sheratan::errhdl::get_default_category() != sheratan::errhdl::get_default_category()));
    BOOST_CHECK(!(sheratan::errhdl::get_default_category() < sheratan::errhdl::get_default_category()));
  }

BOOST_AUTO_TEST_SUITE_END() // default_category


} // anonymous namespace


// vim: set ts=2 sw=2 et:


