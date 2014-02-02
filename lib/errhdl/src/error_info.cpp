/// \file errhdl/src/error_info.cpp
/// \brief Exception information implementation.
/// \ingroup sheratan_errhdl
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#include "sheratan/errhdl/error_info.hpp"
#include "sheratan/errhdl/exception.hpp"


namespace sheratan {

namespace errhdl {


error_info::code_type get_code(const exception &ex)
{
  if(const error_info::code_type *code = get_error_info<error_info::code>(ex)) {
    return *code;
  }
  else {
    return error_code();
  }
}

error_info::file_type get_file(const exception &ex)
{
  if(const error_info::file_type *file = get_error_info<error_info::file>(ex)) {
    return *file;
  }
  else {
    return "";
  }
}

error_info::line_type get_line(const exception &ex)
{
  if(const error_info::line_type *line = get_error_info<error_info::line>(ex)) {
    return *line;
  }
  else {
    return 0;
  }
}

error_info::seconds_type get_seconds(const exception &ex)
{
  if(const error_info::seconds_type *seconds = get_error_info<error_info::seconds>(ex)) {
    return *seconds;
  }
  else {
    return 0;
  }
}

error_info::useconds_type get_useconds(const exception &ex)
{
  if(const error_info::useconds_type *useconds = get_error_info<error_info::useconds>(ex)) {
    return *useconds;
  }
  else {
    return 0;
  }
}


} // namespace errhdl

} // namespace sheratan


// vim: set ts=2 sw=2 et:


