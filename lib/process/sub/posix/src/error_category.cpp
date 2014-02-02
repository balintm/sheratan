/// \file process/sub/posix/src/error_category.cpp
/// \brief Process management library POSIX implementation error category implementation.
/// \ingroup sheratan_process_posix
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#include "sheratan/errhdl/exception.hpp"
#include "sheratan/process/posix/error_category.hpp"


namespace sheratan {

namespace process_impl {

namespace posix {


const char * error_category_traits::name()
{
  return "process_posix error";
}

const error_category & get_error_category()
{
  return sheratan::errhdl::get_error_category<sheratan::process_impl::posix::error_category_traits>();
}

error_category::error_info::posix_errnum_type get_posix_errnum(const sheratan::errhdl::exception &ex)
{
  if(const error_category::error_info::posix_errnum_type *posix_errnum = sheratan::errhdl::get_error_info<error_category::error_info::posix_errnum>(ex)) {
    return *posix_errnum;
  }
  else {
    return 0;
  }
}

error_category::error_info::boost_errnum_type get_boost_errnum(const sheratan::errhdl::exception &ex)
{
  if(const error_category::error_info::boost_errnum_type *boost_errnum = sheratan::errhdl::get_error_info<error_category::error_info::boost_errnum>(ex)) {
    return *boost_errnum;
  }
  else {
    return boost::system::error_code();
  }
}


} // namespace posix

} // namespace process_impl

} // namespace sheratan


// vim: set ts=2 sw=2 et:


