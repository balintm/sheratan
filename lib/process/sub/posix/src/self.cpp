/// \file process/sub/posix/src/self.cpp
/// \brief POSIX self process implementation.
/// \ingroup sheratan_process_posix
/// \author Marek Balint \c (mareq[A]balint[D]eu)


// getpid(2): http://pubs.opengroup.org/onlinepubs/009695399/functions/getpid.html
// getppid(2): http://pubs.opengroup.org/onlinepubs/009695399/functions/getppid.html


#include <sys/types.h>
#include <unistd.h>

#include "sheratan/process/posix/self.hpp"


namespace sheratan {

namespace process_impl {

namespace posix {


process_id self::get_pid()
{
  return process_id(::getpid());
}

process_id self::get_parent_pid()
{
  return process_id(::getppid());
}


} // namespace posix

} // namespace process_impl

} // namespace sheratan


// vim: set ts=2 sw=2 et:


