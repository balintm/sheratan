/// \file meta/test/if_then_else_test.cpp
/// \brief If-then-else template unit-test file.
/// \ingroup sheratan_meta_test
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#include <boost/test/unit_test.hpp>

#include "sheratan/meta/if_then_else.hpp"


namespace {


/// \brief Test struct (used in 'true' parameter of if_then_else).
/// \ingroup sheratan_meta_test
/// \nosubgrouping
struct class_true
{
  /// \brief Dummy value.
  static const bool val = true;
};

/// \brief Test struct (used in 'false' parameter of if_then_else).
/// \ingroup sheratan_meta_test
/// \nosubgrouping
struct class_false
{
  /// \brief Dummy value.
  static const bool val = false;
};


BOOST_AUTO_TEST_SUITE(if_then_else)

  /// \brief Unit-test case: If-then-else template.
  BOOST_AUTO_TEST_CASE(if_then_else)
  {
    bool val_true = sheratan::meta::if_then_else<true, class_true, class_false>::result::val;
    BOOST_CHECK_EQUAL(val_true, true);

    bool val_false = sheratan::meta::if_then_else<false, class_true, class_false>::result::val;
    BOOST_CHECK_EQUAL(val_false, false);
  }

BOOST_AUTO_TEST_SUITE_END() // if_then_else


} // anonymous namespace


// vim: set ts=2 sw=2 et:


