/// \file errhdl/src/throw.cpp
/// \brief Exception throwing implementation.
/// \ingroup sheratan_errhdl
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#include "sheratan/errhdl/throw.hpp"


namespace sheratan {

namespace errhdl {


void throw_exception(const logic_error &ex)
{
  throw ex;
}

void throw_exception(const runtime_error &ex)
{
  throw ex;
}


} // namespace errhdl

} // namespace sheratan


// vim: set ts=2 sw=2 et:


