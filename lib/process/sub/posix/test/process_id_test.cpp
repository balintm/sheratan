/// \file process/sub/posix/test/process_id_test.cpp
/// \brief Process ID POSIX implementation unit-test file.
/// \ingroup sheratan_process_posix_test
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#include <boost/test/unit_test.hpp>

#include "sheratan/process/posix/process_id.hpp"
#include "accessor.hpp"


namespace {


BOOST_AUTO_TEST_SUITE(process_id)

  /// \brief Unit-test case: Construction.
  BOOST_AUTO_TEST_CASE(construction)
  {
    // default construction
    sheratan::process_impl::posix::process_id default_constructed;
    BOOST_CHECK_LE(default_constructed.get_value(), 0);

    // construction with PID argument
    sheratan::process_impl::posix::test::accessor::process_id_ptr pid = sheratan::process_impl::posix::test::accessor::process_id__process_id(42);
    BOOST_CHECK_EQUAL(pid->get_value(), 42);
  }

  /// \brief Unit-test case: Copy construction.
  BOOST_AUTO_TEST_CASE(copy_construction)
  {
    // create original and its copy via copy construction
    sheratan::process_impl::posix::test::accessor::process_id_ptr orig = sheratan::process_impl::posix::test::accessor::process_id__process_id(42);
    sheratan::process_impl::posix::process_id copy(*orig);

    // test that they are equal
    BOOST_CHECK_EQUAL(copy.get_value(), orig->get_value());
  }

  /// \brief Unit-test case: Non-throwing swap.
  BOOST_AUTO_TEST_CASE(swap)
  {
    // create two different process IDs
    sheratan::process_impl::posix::test::accessor::process_id_ptr pid1 = sheratan::process_impl::posix::test::accessor::process_id__process_id(42);
    sheratan::process_impl::posix::test::accessor::process_id_ptr pid2 = sheratan::process_impl::posix::test::accessor::process_id__process_id(23);

    // swap two instances
    using std::swap;
    BOOST_CHECK_NO_THROW(swap(*pid1, *pid2));

    // check that two instances are swapped
    BOOST_CHECK_EQUAL(pid1->get_value(), 23);
    BOOST_CHECK_EQUAL(pid2->get_value(), 42);
  }

  /// \brief Unit-test case: Equality comparison operator.
  BOOST_AUTO_TEST_CASE(equals_operator)
  {
    // create two IDs with different values
    sheratan::process_impl::posix::test::accessor::process_id_ptr lesser = sheratan::process_impl::posix::test::accessor::process_id__process_id(1);
    sheratan::process_impl::posix::test::accessor::process_id_ptr same_as_lesser = sheratan::process_impl::posix::test::accessor::process_id__process_id(1);
    sheratan::process_impl::posix::test::accessor::process_id_ptr greater = sheratan::process_impl::posix::test::accessor::process_id__process_id(2);

    // test that they compare correctly
    BOOST_CHECK(*lesser == *lesser);
    BOOST_CHECK(*lesser == *same_as_lesser);
    BOOST_CHECK(!(*lesser == *greater));
    BOOST_CHECK(!(*greater == *lesser));
    BOOST_CHECK(!(*greater == *same_as_lesser));
    BOOST_CHECK(*greater == *greater);
  }

  /// \brief Unit-test case: Inquality comparison operator.
  BOOST_AUTO_TEST_CASE(not_equals_operator)
  {
    // create two IDs with different values
    sheratan::process_impl::posix::test::accessor::process_id_ptr lesser = sheratan::process_impl::posix::test::accessor::process_id__process_id(1);
    sheratan::process_impl::posix::test::accessor::process_id_ptr same_as_lesser = sheratan::process_impl::posix::test::accessor::process_id__process_id(1);
    sheratan::process_impl::posix::test::accessor::process_id_ptr greater = sheratan::process_impl::posix::test::accessor::process_id__process_id(2);

    // test that they compare correctly
    BOOST_CHECK(!(*lesser != *lesser));
    BOOST_CHECK(!(*lesser != *same_as_lesser));
    BOOST_CHECK(*lesser != *greater);
    BOOST_CHECK(*greater != *lesser);
    BOOST_CHECK(*greater != *same_as_lesser);
    BOOST_CHECK(!(*greater != *greater));
  }

  /// \brief Unit-test case: Less-than comparison operator.
  BOOST_AUTO_TEST_CASE(less_operator)
  {
    // create two PIDs with different values
    sheratan::process_impl::posix::test::accessor::process_id_ptr lesser = sheratan::process_impl::posix::test::accessor::process_id__process_id(1);
    sheratan::process_impl::posix::test::accessor::process_id_ptr greater = sheratan::process_impl::posix::test::accessor::process_id__process_id(2);

    // test that they compare correctly
    BOOST_CHECK(!(*lesser < *lesser));
    BOOST_CHECK(*lesser < *greater);
    BOOST_CHECK(!(*greater < *lesser));
    BOOST_CHECK(!(*greater < *greater));
  }

  /// \brief Unit-test case: Less-than or equals comparison operator.
  BOOST_AUTO_TEST_CASE(less_equals_operator)
  {
    // create two PIDs with different values
    sheratan::process_impl::posix::test::accessor::process_id_ptr lesser = sheratan::process_impl::posix::test::accessor::process_id__process_id(1);
    sheratan::process_impl::posix::test::accessor::process_id_ptr same_as_lesser = sheratan::process_impl::posix::test::accessor::process_id__process_id(1);
    sheratan::process_impl::posix::test::accessor::process_id_ptr greater = sheratan::process_impl::posix::test::accessor::process_id__process_id(2);

    // test that they compare correctly
    BOOST_CHECK(*lesser <= *lesser);
    BOOST_CHECK(*lesser <= *same_as_lesser);
    BOOST_CHECK(*lesser <= *greater);
    BOOST_CHECK(!(*greater <= *lesser));
    BOOST_CHECK(!(*greater <= *same_as_lesser));
    BOOST_CHECK(*greater <= *greater);
  }

  /// \brief Unit-test case: Greater-than comparison operator.
  BOOST_AUTO_TEST_CASE(greater_operator)
  {
    // create two PIDs with different values
    sheratan::process_impl::posix::test::accessor::process_id_ptr lesser = sheratan::process_impl::posix::test::accessor::process_id__process_id(1);
    sheratan::process_impl::posix::test::accessor::process_id_ptr same_as_lesser = sheratan::process_impl::posix::test::accessor::process_id__process_id(1);
    sheratan::process_impl::posix::test::accessor::process_id_ptr greater = sheratan::process_impl::posix::test::accessor::process_id__process_id(2);

    // test that they compare correctly
    BOOST_CHECK(!(*lesser > *lesser));
    BOOST_CHECK(!(*lesser > *greater));
    BOOST_CHECK(*greater > *lesser);
    BOOST_CHECK(!(*greater > *greater));
  }

  /// \brief Unit-test case: Greater-than or equals comparison operator.
  BOOST_AUTO_TEST_CASE(greater_equals_operator)
  {
    // create two PIDs with different values
    sheratan::process_impl::posix::test::accessor::process_id_ptr lesser = sheratan::process_impl::posix::test::accessor::process_id__process_id(1);
    sheratan::process_impl::posix::test::accessor::process_id_ptr greater = sheratan::process_impl::posix::test::accessor::process_id__process_id(2);
    sheratan::process_impl::posix::test::accessor::process_id_ptr same_as_greater = sheratan::process_impl::posix::test::accessor::process_id__process_id(2);

    // test that they compare correctly
    BOOST_CHECK(*lesser >= *lesser);
    BOOST_CHECK(!(*lesser >= *greater));
    BOOST_CHECK(!(*lesser >= *same_as_greater));
    BOOST_CHECK(*greater >= *lesser);
    BOOST_CHECK(*greater >= *greater);
    BOOST_CHECK(*greater >= *same_as_greater);
  }

  /// \brief Unit-test case: Output operator.
  BOOST_AUTO_TEST_CASE(output_operator)
  {
    // create PID
    sheratan::process_impl::posix::test::accessor::process_id_ptr pid = sheratan::process_impl::posix::test::accessor::process_id__process_id(42);

    // output ID
    std::ostringstream os;
    os << *pid;

    // check output
    BOOST_CHECK_EQUAL(os.str(), "42");
  }

BOOST_AUTO_TEST_SUITE_END() // process_id


} // anonymous namespace


// vim: set ts=2 sw=2 et:


