/// \file utility/test/test_id.cpp
/// \brief Test ID implementation.
/// \ingroup sheratan_utility_test
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#include <iostream>

#include "test_id.hpp"
#include "test_id_counters.hpp"


namespace sheratan {

namespace utility {

namespace test {


test_id_traits::value_type test_id_traits::default_value()
{
  return 42;
}

bool test_id_traits::less(const test_id_traits::value_type &lhs, const test_id_traits::value_type &rhs)
{
  return lhs < rhs;
}

std::ostream & test_id_traits::output(std::ostream &os, const test_id_traits::value_type &value)
{
  return os << value;
}

sheratan::utility::id_impl<test_id_traits, test_id_traits::tag::TEST_ID> * test_id_traits::clone(const sheratan::utility::id_impl<test_id_traits, test_id_traits::tag::TEST_ID> &id)
{
  ++id_impl_counter;
  return new sheratan::utility::id_impl<test_id_traits, test_id_traits::tag::TEST_ID>(id);
}

void test_id_traits::destroy(sheratan::utility::id_impl_base<test_id_traits::base_tag> *id)
{
  --id_impl_counter;
  delete id;
}


} // namespace test

} // namespace utility

} // namespace sheratan


// vim: set ts=2 sw=2 et:


