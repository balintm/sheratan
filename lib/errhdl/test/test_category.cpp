/// \file errhdl/test/test_category.cpp
/// \brief Test error category implementation.
/// \ingroup sheratan_errhdl_test
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#include "sheratan/errhdl/exception.hpp"
#include "test_category.hpp"


namespace sheratan {

namespace errhdl {

namespace test {


const char * test_category_traits::name()
{
  return "test";
}

const test_category & get_test_category()
{
  return get_error_category<test_category_traits>();
}

test_category::error_info::testing_data_type get_testing_data(const sheratan::errhdl::exception &ex)
{
  if(const test_category::error_info::testing_data_type *test_data = sheratan::errhdl::get_error_info<test_category::error_info::testing_data>(ex)) {
    return *test_data;
  }
  else {
    return 0;
  }
}


} // namespace test

} // namespace errhdl

} // namespace sheratan


// vim: set ts=2 sw=2 et:


