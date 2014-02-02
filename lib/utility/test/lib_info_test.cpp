/// \file utility/test/lib_info_test.cpp
/// \brief Library information unit-test file.
/// \ingroup sheratan_utility_test
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#include <boost/test/unit_test.hpp>

#include "sheratan/utility/lib_info.hpp"


namespace {


BOOST_AUTO_TEST_SUITE(lib_info)

  /// \brief Unit-test case: Library name.
  BOOST_AUTO_TEST_CASE(lib_name)
  {
    BOOST_CHECK_EQUAL(std::string(sheratan::utility::lib_name), std::string(SHERATAN_LIB_NAME));
  }

  /// \brief Unit-test case: Library version.
  BOOST_AUTO_TEST_CASE(lib_version)
  {
    BOOST_CHECK_EQUAL(std::string(sheratan::utility::lib_version), std::string(SHERATAN_LIB_VERSION));
  }

  /// \brief Unit-test case: Library version tag.
  BOOST_AUTO_TEST_CASE(lib_version_tag)
  {
    BOOST_CHECK_EQUAL(sheratan::utility::lib_version_tag, SHERATAN_LIB_VERSION_TAG);
  }

BOOST_AUTO_TEST_SUITE_END() // lib_info


} // anonymous namespace


// vim: set ts=2 sw=2 et:


