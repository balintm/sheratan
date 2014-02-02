/// \file process/sub/posix/src/forker.cpp
/// \brief POSIX forker implementation.
/// \ingroup sheratan_process_posix
/// \author Marek Balint \c (mareq[A]balint[D]eu)


// fork(2): http://pubs.opengroup.org/onlinepubs/009695399/functions/fork.html


#include <cerrno>

#include <unistd.h>

#include "sheratan/errhdl/assert.hpp"
#include "sheratan/errhdl/throw.hpp"
#include "sheratan/process/posix/error_category.hpp"
#include "sheratan/process/posix/forker.hpp"
#include "sheratan/process/posix/process.hpp"


namespace sheratan {

namespace process_impl {

namespace posix {


forker::forker()
: fork_ctl_()
{
}

forker::forker(const fork_ctl &fc)
: fork_ctl_(fc.clone())
{
}

const fork_ctl & forker::get_fork_ctl() const
{
  SHERATAN_CHECK(this->fork_ctl_.get() != NULL);

  return *this->fork_ctl_;
}

fork_ctl & forker::get_fork_ctl()
{
  SHERATAN_CHECK(this->fork_ctl_.get() != NULL);

  return *this->fork_ctl_;
}

void forker::fork(process &child_process)
{
  SHERATAN_CHECK(this->fork_ctl_.get() != NULL);

  this->fork_ctl_->prefork();

  pid_t rc_fork = ::fork();
  if(rc_fork == -1) {  // error
    int saved_errno = errno;
    sheratan::errhdl::runtime_error ex_to_throw;
    ex_to_throw << error_category::error_info::posix_errnum(saved_errno);
    SHERATAN_THROW_EXCEPTION(ex_to_throw, sheratan::errhdl::error_code(errnum::POSIX_SYSTEM, get_error_category()));
  }
  else if(rc_fork == 0) { // child
    exit(this->fork_ctl_->child());
  }
  else if(rc_fork > 0) { // parent
    child_process.set_pid(process_id(static_cast<process_id::value_type>(rc_fork)));
    this->fork_ctl_->postfork(child_process);
    return;
  }

  // this point should never be reached
  SHERATAN_REQUIRE(false);
}


} // namespace posix

} // namespace process_impl

} // namespace sheratan


// vim: set ts=2 sw=2 et:


