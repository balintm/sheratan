/// \file errhdl/src/assert_category.cpp
/// \brief Failed assertion error category implementation.
/// \ingroup sheratan_errhdl
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#include "sheratan/errhdl/assert_category.hpp"
#include "sheratan/errhdl/exception.hpp"


namespace sheratan {

namespace errhdl {


const char * assert_category_traits::name()
{
  return "failed assertion";
}

const assert_category & get_assert_category()
{
  return get_error_category<assert_category_traits>();
}

assert_category::error_info::failed_assertion_type get_failed_assertion(const exception &ex)
{
  if(const assert_category::error_info::failed_assertion_type *assertion = get_error_info<assert_category::error_info::failed_assertion>(ex)) {
    return *assertion;
  }
  else {
    return "";
  }
}


} // namespace errhdl

} // namespace sheratan


// vim: set ts=2 sw=2 et:


