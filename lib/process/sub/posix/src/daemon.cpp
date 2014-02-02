/// \file process/sub/posix/src/daemon.cpp
/// \brief POSIX daemon implementation.
/// \ingroup sheratan_process_posix
/// \author Marek Balint \c (mareq[A]balint[D]eu)


// waitpid(2): http://pubs.opengroup.org/onlinepubs/009695399/functions/wait.html
// kill(2): http://pubs.opengroup.org/onlinepubs/009604599/functions/kill.html


#include <cerrno>

#include <signal.h>

#include "sheratan/errhdl/assert.hpp"
#include "sheratan/errhdl/throw.hpp"
#include "sheratan/process/posix/error_category.hpp"
#include "sheratan/process/posix/daemon.hpp"


namespace sheratan {

namespace process_impl {

namespace posix {


daemon::~daemon()
{
}

void daemon::set_pid(process_id pid)
{
  this->pid_ = process_id(pid);
}

process_id daemon::get_pid() const
{
  return this->pid_;
}

bool daemon::valid() const
{
  if(this->pid_ == process_id()) {
    return false;
  }
  return true;
}

void daemon::kill(signal_number_type signal)
{
  SHERATAN_CHECK(this->valid());

  // this is *NOT* recursive call - syscall kill(2) is called
  int rc_kill = ::kill(this->pid_.get_value(), signal);
  if(rc_kill != 0) {
    int saved_errnum = errno;
    sheratan::errhdl::runtime_error ex_to_throw;
    ex_to_throw << error_category::error_info::posix_errnum(saved_errnum);
    SHERATAN_THROW_EXCEPTION(ex_to_throw, sheratan::errhdl::error_code(errnum::BOOST_SYSTEM, get_error_category()));
  }
}


} // namespace posix

} // namespace process_impl

} // namespace sheratan


// vim: set ts=2 sw=2 et:


