/// \file utility/test/explicit_value_test.cpp
/// \brief Explicit value unit-test file.
/// \ingroup sheratan_utility_test
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#include <boost/test/unit_test.hpp>

#include "sheratan/utility/explicit_value.hpp"


namespace {


/// \brief Test value traits.
/// \ingroup sheratan_utility_test
/// \nosubgrouping
struct test_value_traits
{
  /// \brief Value type.
  typedef int value_type;

  /// \brief Value tag.
  /// \ingroup sheratan_utility_test
  /// \nosubgrouping
  struct tag
  {
    /// \brief Value tag values.
    typedef enum
    {
      TEST_VALUE  ///< Test value.
    } value_type;
  };

  /// \brief Default value.
  /// \return Default value.
  /// \par Abrahams exception guarantee:
  /// strong
  static test_value_traits::value_type default_value();
};


test_value_traits::value_type test_value_traits::default_value()
{
  return 42;
}


/// \brief Test value type definition.
typedef sheratan::utility::explicit_value<test_value_traits, test_value_traits::tag::TEST_VALUE> test_value_type;


BOOST_AUTO_TEST_SUITE(explicit_value)

  /// \brief Unit-test case: Default construction.
  BOOST_AUTO_TEST_CASE(default_construction)
  {
    // default construct the value
    test_value_type value;

    // check that it contains correct default value
    BOOST_CHECK_EQUAL(value, test_value_traits::default_value());
    BOOST_CHECK_EQUAL(value.get_value(), test_value_traits::default_value());
  }

  /// \brief Unit-test case: Explicit construction.
  BOOST_AUTO_TEST_CASE(explicit_construction)
  {
    // explicitly construct the value
    test_value_type value(23);

    // check that it contains correct value
    BOOST_CHECK_EQUAL(value, 23);
    BOOST_CHECK_EQUAL(value.get_value(), 23);
  }

  /// \brief Unit-test case: Copy construction.
  BOOST_AUTO_TEST_CASE(copy_construction)
  {
    // create original and its copy via copy construction
    test_value_type orig(23);
    test_value_type copy(orig);

    // test that they are equal
    BOOST_CHECK_EQUAL(copy, orig);
    BOOST_CHECK_EQUAL(copy.get_value(), orig.get_value());
  }

  /// \brief Unit-test case: Assignment.
  BOOST_AUTO_TEST_CASE(assignment)
  {
    // create original and its copy via assignment
    test_value_type orig(23);
    test_value_type assigned;
    assigned = orig;

    // test that they are equal
    BOOST_CHECK_EQUAL(assigned, orig);
    BOOST_CHECK_EQUAL(assigned.get_value(), orig.get_value());
  }

  /// \brief Unit-test case: Implicit conversion to underlying type.
  BOOST_AUTO_TEST_CASE(implicit_conversion)
  {
    // create original and its copy via implicit conversion to underlying type
    test_value_type orig(23);
    int converted = orig;

    // test that they are equal
    BOOST_CHECK_EQUAL(converted, orig);
    BOOST_CHECK_EQUAL(converted, orig.get_value());
  }

  /// \brief Unit-test case: Set value.
  BOOST_AUTO_TEST_CASE(set_value)
  {
    // create default constructed value and set its value using setter method
    test_value_type value;
    value.set_value(23);

    // check that value was set
    BOOST_CHECK_EQUAL(value, 23);
    BOOST_CHECK_EQUAL(value.get_value(), 23);
  }

BOOST_AUTO_TEST_SUITE_END() // explicit_value


} // anonymous namespace


// vim: set ts=2 sw=2 et:


