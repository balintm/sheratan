/// \file errhdl/src/error_category.cpp
/// \brief Error category implementation.
/// \ingroup sheratan_errhdl
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#include <functional>

#include "sheratan/errhdl/error_category.hpp"
#include "sheratan/errhdl/error_category_template.hpp"


namespace sheratan {

namespace errhdl {


error_category::~error_category()
{
}

bool error_category::operator==(const error_category &other) const
{
  return this == &other;
}

bool error_category::operator!=(const error_category &other) const
{
  return !(*this == other);
}

bool error_category::operator<(const error_category &other) const
{
  return std::less<const error_category*>()(this, &other);
}


} // namespace errhdl

} // namespace sheratan


// vim: set ts=2 sw=2 et:


