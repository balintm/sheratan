/// \file process/sub/posix/src/process.cpp
/// \brief POSIX process implementation.
/// \ingroup sheratan_process_posix
/// \author Marek Balint \c (mareq[A]balint[D]eu)


// waitpid(2): http://pubs.opengroup.org/onlinepubs/009695399/functions/wait.html
// kill(2): http://pubs.opengroup.org/onlinepubs/009604599/functions/kill.html


#include <cerrno>

#include <sys/wait.h>
#include <signal.h>

#include "sheratan/errhdl/assert.hpp"
#include "sheratan/errhdl/throw.hpp"
#include "sheratan/process/posix/error_category.hpp"
#include "sheratan/process/posix/process.hpp"


namespace sheratan {

namespace process_impl {

namespace posix {


process::~process()
{
  // this may throw an exception, which means undefined behavior,
  // however allowing execution of this destructor, in case this condition
  // is not met, itself results undefined behavior and it is probably
  // the best thing to cry out as loud and as soon as possible - thus let
  // the exception be potentially thrown even from destructor
  SHERATAN_CHECK(!this->valid());
}

void process::set_pid(process_id pid)
{
  this->pid_ = process_id(pid);
}

process_id process::get_pid() const
{
  return this->pid_;
}

bool process::valid() const
{
  if(this->pid_ == process_id()) {
    return false;
  }
  return true;
}

void process::detach()
{
  this->pid_ = process_id();
}

exit_status process::join(bool nonblocking, bool stopped, bool continued)
{
  SHERATAN_CHECK(this->valid());

  int status;
  pid_t rc_waitpid = ::waitpid(this->pid_.get_value(), &status, 0 | (nonblocking ? WNOHANG : 0) | (stopped ? WUNTRACED : 0) | (continued ? WCONTINUED : 0));
  if(nonblocking && (rc_waitpid == 0)) {
    // return invalid (defalut constructed exit status is invalid by definition) exit status
    // in case it was non-blocking call to waitpid and child has not changed its status
    return exit_status();
  }
  if(rc_waitpid != this->pid_.get_value()) {
    int saved_errnum = errno;
    sheratan::errhdl::runtime_error ex_to_throw;
    ex_to_throw << error_category::error_info::posix_errnum(saved_errnum);
    SHERATAN_THROW_EXCEPTION(ex_to_throw, sheratan::errhdl::error_code(errnum::POSIX_SYSTEM, get_error_category()));
  }

  exit_status ret(status);

  // set invalid process state only in case when waitpid returned
  // for already finished (i.e. zombie) process - it is not the case,
  // if the process just stopped or continued after job control stop
  if((!ret.stopped()) && (!ret.continued())) {
    this->pid_ = process_id();
  }

  return exit_status(status);
}

#if 0 // NOT IMPLEMENTED
exit_status process::timed_join(const system_time_type &time)
{
  SHERATAN_CHECK(this->valid());

  /// \todo Implement this method.
  return exit_status();
}
#endif // NOT IMPLEMENTED

void process::kill(signal_number_type signal)
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


