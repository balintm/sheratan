/// \file process/sub/posix/src/exit_status.cpp
/// \brief POSIX process exit status implementation.
/// \ingroup sheratan_process_posix
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#include <cstdlib>

#include <sys/wait.h>

#include "sheratan/errhdl/assert.hpp"
#include "sheratan/process/posix/exit_status.hpp"


namespace sheratan {

namespace process_impl {

namespace posix {


const exit_status::value_type exit_status::SUCCESS = EXIT_SUCCESS;

const exit_status::value_type exit_status::FAILURE = EXIT_FAILURE;


exit_status::exit_status()
: valid_(false)
, value_(0)
{
}

exit_status::exit_status(exit_status::value_type value)
: valid_(true)
, value_(value)
{
}

void exit_status::swap(exit_status &other)
{
  using std::swap;

  swap(this->valid_, other.valid_);
  swap(this->value_, other.value_);
}

bool exit_status::valid() const
{
  return this->valid_;
}

bool exit_status::exited() const
{
  SHERATAN_CHECK(this->valid() == true);

  return WIFEXITED(this->value_);
}

exit_status::value_type exit_status::get_status() const
{
  SHERATAN_CHECK(this->valid() == true);

  return WEXITSTATUS(this->value_);
}

bool exit_status::signaled() const
{
  SHERATAN_CHECK(this->valid() == true);

  return WIFSIGNALED(this->value_);
}

int exit_status::get_term_signal() const
{
  SHERATAN_CHECK(this->valid() == true);
  SHERATAN_CHECK(this->signaled());

  return WTERMSIG(this->value_);
}

bool exit_status::stopped() const
{
  SHERATAN_CHECK(this->valid() == true);

  return WIFSTOPPED(this->value_);
}

int exit_status::get_stop_signal() const
{
  SHERATAN_CHECK(this->valid() == true);
  SHERATAN_CHECK(this->stopped() == true);

  return WSTOPSIG(this->value_);
}

bool exit_status::continued() const
{
  SHERATAN_CHECK(this->valid() == true);

  // WIFCONTINUED is XSI extension
# ifdef WIFCONTINUED
    return WIFCONTINUED(this->value_);
# else
    return false;
# endif
}

bool exit_status::dumped_core() const
{
  SHERATAN_CHECK(this->valid() == true);

  // WCOREDUMP is not specified by POSIX
# ifdef WCOREDUMP
    return WCOREDUMP(this->value_);
# else
    return false;
# endif
}

exit_status::value_type exit_status::get_value() const
{
  SHERATAN_CHECK(this->valid() == true);

  return this->value_;
}

void swap(exit_status &es1, exit_status &es2)
{
  es1.swap(es2);
}


} // namespace posix

} // namespace process_impl

} // namespace sheratan


namespace std {


template<>
void swap(sheratan::process_impl::posix::exit_status &es1, sheratan::process_impl::posix::exit_status &es2)
{
  es1.swap(es2);
}


} // namespace std


// vim: set ts=2 sw=2 et:


