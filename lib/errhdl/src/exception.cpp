/// \file errhdl/src/exception.cpp
/// \brief Base %exception implementation.
/// \ingroup sheratan_errhdl
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#include "sheratan/errhdl/exception.hpp"


namespace sheratan {

namespace errhdl {


void exception::destroy(exception *ex)
{
  delete ex;
}

exception::const_iterator exception::begin() const
{
  return exception::const_iterator(*this);
}

exception::const_iterator exception::end() const
{
  return exception::const_iterator();
}

exception::iterator exception::begin()
{
  return exception::iterator(*this);
}

exception::iterator exception::end()
{
  return exception::iterator();
}

runtime_error::runtime_error()
: sheratan::errhdl::exception()
, std::runtime_error("")
{
}

exception * runtime_error::clone() const
{
  return new runtime_error(*this);
}

logic_error::logic_error()
: sheratan::errhdl::exception()
, std::logic_error("")
{
}

exception * logic_error::clone() const
{
  return new logic_error(*this);
}


} // namespace errhdl

} // namespace sheratan


// vim: set ts=2 sw=2 et:


