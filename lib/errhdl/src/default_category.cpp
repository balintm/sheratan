/// \file errhdl/src/default_category.cpp
/// \brief Default error category implementation.
/// \ingroup sheratan_errhdl
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#include "sheratan/errhdl/default_category.hpp"


namespace sheratan {

namespace errhdl {


const char * default_category_traits::name()
{
  return "unknown error";
}

const default_category & get_default_category()
{
  return get_error_category<default_category_traits>();
}


} // namespace errhdl

} // namespace sheratan


// vim: set ts=2 sw=2 et:


