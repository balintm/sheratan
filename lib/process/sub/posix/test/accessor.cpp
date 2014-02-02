/// \file process/sub/posix/test/accessor.cpp
/// \brief Test helper accessor implementation.
/// \ingroup sheratan_process_posix_test
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#include "accessor.hpp"


namespace sheratan {

namespace process_impl {

namespace posix {

namespace test {


accessor::process_id_ptr accessor::process_id__process_id(sheratan::process_impl::posix::process_id::value_type id)
{
  return accessor::process_id_ptr(new sheratan::process_impl::posix::process_id(id));
}

accessor::exit_status_ptr accessor::exit_status__exit_status(sheratan::process_impl::posix::exit_status::value_type value)
{
  return accessor::exit_status_ptr(new sheratan::process_impl::posix::exit_status(value));
}


} // namespace test

} // namespace posix

} // namespace process_impl

} // namespace sheratan


// vim: set ts=2 sw=2 et:


