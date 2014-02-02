/// \file errhdl/src/error_code.cpp
/// \brief Error code implementation.
/// \ingroup sheratan_errhdl
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#include "sheratan/errhdl/error_code.hpp"
#include "sheratan/errhdl/default_category.hpp"


namespace sheratan {

namespace errhdl {


error_code::error_code()
: errnum_(get_default_category().get_default_errnum())
, category_(&get_default_category())
{
}

error_category::errnum_type error_code::get_errnum() const
{
  return this->errnum_;
}

const error_category & error_code::get_category() const
{
  return *this->category_;
}

bool operator==(const error_code &lhs, const error_code &rhs)
{
  return (lhs.errnum_ == rhs.errnum_) && (lhs.category_ == rhs.category_);
}

bool operator!=(const error_code &lhs, const error_code &rhs)
{
  return !(lhs == rhs);
}


} // namespace errhdl

} // namespace sheratan


// vim: set ts=2 sw=2 et:


