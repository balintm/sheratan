/// \file utility/test/id_test.cpp
/// \brief ID unit-test file.
/// \ingroup sheratan_utility_test
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#include <boost/test/unit_test.hpp>

#include <sstream>

#include "sheratan/utility/id_io.hpp"

#include "test_id.hpp"
#include "test_id_counters.hpp"


namespace {


BOOST_AUTO_TEST_SUITE(id)

  /// \brief Unit-test case: Explicit construction.
  BOOST_AUTO_TEST_CASE(explicit_construction)
  {
    // reset object counter
    sheratan::utility::test::id_impl_counter = 0;

    {
      // explicitly construct the ID
      sheratan::utility::test::test_id_type id(sheratan::utility::test::test_id_impl_type(23));

      // check that it contains correct value
      BOOST_CHECK_EQUAL(dynamic_cast<sheratan::utility::test::test_id_impl_type &>(id.get_value()).get_value(), 23);
    }

    // check object counter
    BOOST_CHECK_EQUAL(sheratan::utility::test::id_impl_counter, 0);
  }

  /// \brief Unit-test case: Copy construction.
  BOOST_AUTO_TEST_CASE(copy_construction)
  {
    // reset object counter
    sheratan::utility::test::id_impl_counter = 0;

    {
      // create original and its copy via copy construction
      sheratan::utility::test::test_id_type orig(sheratan::utility::test::test_id_impl_type(23));
      sheratan::utility::test::test_id_type copy(orig);

      // test that they are equal
      BOOST_CHECK_EQUAL(dynamic_cast<sheratan::utility::test::test_id_impl_type &>(orig.get_value()).get_value(), dynamic_cast<sheratan::utility::test::test_id_impl_type &>(copy.get_value()).get_value());
    }

    // check object counter
    BOOST_CHECK_EQUAL(sheratan::utility::test::id_impl_counter, 0);
  }

  /// \brief Unit-test case: Assignment.
  BOOST_AUTO_TEST_CASE(assignment)
  {
    // reset object counter
    sheratan::utility::test::id_impl_counter = 0;

    {
      // create original and its copy via assignment
      sheratan::utility::test::test_id_type orig(sheratan::utility::test::test_id_impl_type(23));
      sheratan::utility::test::test_id_type assigned(sheratan::utility::test::test_id_impl_type(42));
      assigned = orig;

      // test that they are equal
      BOOST_CHECK_EQUAL(dynamic_cast<sheratan::utility::test::test_id_impl_type &>(orig.get_value()).get_value(), dynamic_cast<sheratan::utility::test::test_id_impl_type &>(assigned.get_value()).get_value());
    }

    // check object counter
    BOOST_CHECK_EQUAL(sheratan::utility::test::id_impl_counter, 0);
  }

  /// \brief Unit-test case: Less-than comparison.
  BOOST_AUTO_TEST_CASE(less)
  {
    // reset object counter
    sheratan::utility::test::id_impl_counter = 0;

    {
      // create two IDs with different values
      sheratan::utility::test::test_id_type lesser(sheratan::utility::test::test_id_impl_type(1));
      sheratan::utility::test::test_id_type greater(sheratan::utility::test::test_id_impl_type(2));

      // test that they compare correctly
      BOOST_CHECK(!lesser.less(lesser));
      BOOST_CHECK(lesser.less(greater));
      BOOST_CHECK(!greater.less(lesser));
      BOOST_CHECK(!greater.less(greater));
    }

    // check object counter
    BOOST_CHECK_EQUAL(sheratan::utility::test::id_impl_counter, 0);
  }

  /// \brief Unit-test case: Set value.
  BOOST_AUTO_TEST_CASE(set_value)
  {
    // reset object counter
    sheratan::utility::test::id_impl_counter = 0;

    {
      // create ID and set its value using setter method
      sheratan::utility::test::test_id_type id(sheratan::utility::test::test_id_impl_type(42));
      id.set_value(sheratan::utility::test::test_id_impl_type(23));

      // check that value was set
      BOOST_CHECK_EQUAL(dynamic_cast<sheratan::utility::test::test_id_impl_type &>(id.get_value()).get_value(), 23);
    }

    // check object counter
    BOOST_CHECK_EQUAL(sheratan::utility::test::id_impl_counter, 0);
  }

  /// \brief Unit-test case: Equality comparison operator.
  BOOST_AUTO_TEST_CASE(equals_operator)
  {
    // reset object counter
    sheratan::utility::test::id_impl_counter = 0;

    {
      // create two IDs with different values
      sheratan::utility::test::test_id_type lesser(sheratan::utility::test::test_id_impl_type(1));
      sheratan::utility::test::test_id_type same_as_lesser(sheratan::utility::test::test_id_impl_type(1));
      sheratan::utility::test::test_id_type greater(sheratan::utility::test::test_id_impl_type(2));

      // test that they compare correctly
      BOOST_CHECK(lesser == lesser);
      BOOST_CHECK(lesser == same_as_lesser);
      BOOST_CHECK(!(lesser == greater));
      BOOST_CHECK(!(greater == lesser));
      BOOST_CHECK(!(greater == same_as_lesser));
      BOOST_CHECK(greater == greater);
    }

    // check object counter
    BOOST_CHECK_EQUAL(sheratan::utility::test::id_impl_counter, 0);
  }

  /// \brief Unit-test case: Inequality comparison operator.
  BOOST_AUTO_TEST_CASE(not_equals_operator)
  {
    // reset object counter
    sheratan::utility::test::id_impl_counter = 0;

    {
      // create two IDs with different values
      sheratan::utility::test::test_id_type lesser(sheratan::utility::test::test_id_impl_type(1));
      sheratan::utility::test::test_id_type same_as_lesser(sheratan::utility::test::test_id_impl_type(1));
      sheratan::utility::test::test_id_type greater(sheratan::utility::test::test_id_impl_type(2));

      // test that they compare correctly
      BOOST_CHECK(!(lesser != lesser));
      BOOST_CHECK(!(lesser != same_as_lesser));
      BOOST_CHECK(lesser != greater);
      BOOST_CHECK(greater != lesser);
      BOOST_CHECK(greater != same_as_lesser);
      BOOST_CHECK(!(greater != greater));
    }

    // check object counter
    BOOST_CHECK_EQUAL(sheratan::utility::test::id_impl_counter, 0);
  }

  /// \brief Unit-test case: Less-than comparison operator.
  BOOST_AUTO_TEST_CASE(less_operator)
  {
    // reset object counter
    sheratan::utility::test::id_impl_counter = 0;

    {
      // create two IDs with different values
      sheratan::utility::test::test_id_type lesser(sheratan::utility::test::test_id_impl_type(1));
      sheratan::utility::test::test_id_type greater(sheratan::utility::test::test_id_impl_type(2));

      // test that they compare correctly
      BOOST_CHECK(!(lesser < lesser));
      BOOST_CHECK(lesser < greater);
      BOOST_CHECK(!(greater < lesser));
      BOOST_CHECK(!(greater < greater));
    }

    // check object counter
    BOOST_CHECK_EQUAL(sheratan::utility::test::id_impl_counter, 0);
  }

  /// \brief Unit-test case: Less-than or equals comparison operator.
  BOOST_AUTO_TEST_CASE(less_equals_operator)
  {
    // reset object counter
    sheratan::utility::test::id_impl_counter = 0;

    {
      // create two IDs with different values
      sheratan::utility::test::test_id_type lesser(sheratan::utility::test::test_id_impl_type(1));
      sheratan::utility::test::test_id_type same_as_lesser(sheratan::utility::test::test_id_impl_type(1));
      sheratan::utility::test::test_id_type greater(sheratan::utility::test::test_id_impl_type(2));

      // test that they compare correctly
      BOOST_CHECK(lesser <= lesser);
      BOOST_CHECK(lesser <= same_as_lesser);
      BOOST_CHECK(lesser <= greater);
      BOOST_CHECK(!(greater <= lesser));
      BOOST_CHECK(!(greater <= same_as_lesser));
      BOOST_CHECK(greater <= greater);
    }

    // check object counter
    BOOST_CHECK_EQUAL(sheratan::utility::test::id_impl_counter, 0);
  }

  /// \brief Unit-test case: Greater-than comparison operator.
  BOOST_AUTO_TEST_CASE(greater_operator)
  {
    // reset object counter
    sheratan::utility::test::id_impl_counter = 0;

    {
      // create two IDs with different values
      sheratan::utility::test::test_id_type lesser(sheratan::utility::test::test_id_impl_type(1));
      sheratan::utility::test::test_id_type greater(sheratan::utility::test::test_id_impl_type(2));

      // test that they compare correctly
      BOOST_CHECK(!(lesser > lesser));
      BOOST_CHECK(!(lesser > greater));
      BOOST_CHECK(greater > lesser);
      BOOST_CHECK(!(greater > greater));
    }

    // check object counter
    BOOST_CHECK_EQUAL(sheratan::utility::test::id_impl_counter, 0);
  }

  /// \brief Unit-test case: Greater-than or equals comparison operator.
  BOOST_AUTO_TEST_CASE(greater_equals_operator)
  {
    // reset object counter
    sheratan::utility::test::id_impl_counter = 0;

    {
      // create two IDs with different values
      sheratan::utility::test::test_id_type lesser(sheratan::utility::test::test_id_impl_type(1));
      sheratan::utility::test::test_id_type greater(sheratan::utility::test::test_id_impl_type(2));
      sheratan::utility::test::test_id_type same_as_greater(sheratan::utility::test::test_id_impl_type(2));

      // test that they compare correctly
      BOOST_CHECK(lesser >= lesser);
      BOOST_CHECK(!(lesser >= greater));
      BOOST_CHECK(!(lesser >= same_as_greater));
      BOOST_CHECK(greater >= lesser);
      BOOST_CHECK(greater >= greater);
      BOOST_CHECK(greater >= same_as_greater);
    }

    // check object counter
    BOOST_CHECK_EQUAL(sheratan::utility::test::id_impl_counter, 0);
  }

  /// \brief Unit-test case: Output operator.
  BOOST_AUTO_TEST_CASE(output_operator)
  {
    // reset object counter
    sheratan::utility::test::id_impl_counter = 0;

    {
      // create ID
      sheratan::utility::test::test_id_type id(sheratan::utility::test::test_id_impl_type(23));

      // output ID
      std::ostringstream os;
      os << id;

      // check output
      BOOST_CHECK_EQUAL(os.str(), "23");
    }

    // check object counter
    BOOST_CHECK_EQUAL(sheratan::utility::test::id_impl_counter, 0);
  }

BOOST_AUTO_TEST_SUITE_END() // id


} // anonymous namespace


// vim: set ts=2 sw=2 et:


