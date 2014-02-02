/// \file process/sub/posix/src/parent_child_sync.cpp
/// \brief POSIX parent-child synchronizer implementation.
/// \ingroup sheratan_process_posix
/// \author Marek Balint \c (mareq[A]balint[D]eu)


// pipe(2): http://pubs.opengroup.org/onlinepubs/009695399/functions/pipe.html


#include <cerrno>
#include <cstdlib>
#include <cstdio>

#include <unistd.h>

#include "sheratan/errhdl/assert.hpp"
#include "sheratan/errhdl/throw.hpp"
#include "sheratan/process/posix/error_category.hpp"
#include "sheratan/process/posix/parent_child_sync.hpp"


namespace sheratan {

namespace process_impl {

namespace posix {


parent_child_sync::parent_child_sync()
: sync_pipe_r_(NULL)
, sync_pipe_w_(NULL)
{
}

void parent_child_sync::prefork()
{
  // create parent-child synchronization pipe
  this->create_sync_pipe();
}

void parent_child_sync::postfork(process &)
{
  // nothing to do here
}

exit_status::value_type parent_child_sync::child()
{
  // nothing to do here

  return exit_status::SUCCESS;
}

void parent_child_sync::finalize()
{
  this->close_sync_pipe();
}

void parent_child_sync::wait_for_parent()
{
  this->wait_sync_pipe();
}

void parent_child_sync::unblock_child()
{
  this->unblock_sync_pipe();
}

void parent_child_sync::wait_for_child()
{
  this->wait_sync_pipe();
}

void parent_child_sync::unblock_parent()
{
  this->unblock_sync_pipe();
}

void parent_child_sync::create_sync_pipe()
{
  SHERATAN_CHECK(this->sync_pipe_r_ == NULL);
  SHERATAN_CHECK(this->sync_pipe_w_ == NULL);

  int saved_errnum = 0;
  int sync_pipe_fd[2] = {-1, -1};

  // create parent-child synchronization pipe
  if(::pipe(sync_pipe_fd) != 0) {
    saved_errnum = errno;
    goto error;
  }
  this->sync_pipe_r_ = ::fdopen(sync_pipe_fd[0], "r");
  if(this->sync_pipe_r_ == NULL) {
    saved_errnum = errno;
    goto error;
  }
  this->sync_pipe_w_ = ::fdopen(sync_pipe_fd[1], "w");
  if(this->sync_pipe_w_ == NULL) {
    saved_errnum = errno;
    goto error;
  }

  // successful return
  return;

  // ERROR HANDLING
  error:

  // free all possibly allocated resources
  if((this->sync_pipe_r_ == NULL) && (sync_pipe_fd[0] != -1)) {
    ::close(sync_pipe_fd[0]);
  }
  if((this->sync_pipe_w_ == NULL) && (sync_pipe_fd[1] != -1)) {
    ::close(sync_pipe_fd[1]);
  }
  this->close_sync_pipe();

  // throw exception
  sheratan::errhdl::runtime_error ex_to_throw;
  ex_to_throw << error_category::error_info::posix_errnum(saved_errnum);
  SHERATAN_THROW_EXCEPTION(ex_to_throw, sheratan::errhdl::error_code(errnum::POSIX_SYSTEM, get_error_category()));
}

void parent_child_sync::close_sync_pipe()
{
  if(this->sync_pipe_r_ != NULL) {
    std::fclose(this->sync_pipe_r_);
    this->sync_pipe_r_ = NULL;
  }
  if(this->sync_pipe_w_ != NULL) {
    std::fclose(this->sync_pipe_w_);
    this->sync_pipe_w_ = NULL;
  }
}


namespace {


/// \brief Data to be sent over parent-child synchronization pipe.
static const char sync_pipe_data = 42;


} // anonymous namespace


void parent_child_sync::wait_sync_pipe()
{
  errno = 0;
  int data;
  if((data = std::fgetc(this->sync_pipe_r_)) == EOF) {
    int saved_errnum = errno;
    sheratan::errhdl::runtime_error ex_to_throw;
    ex_to_throw << error_category::error_info::posix_errnum(saved_errnum);
    SHERATAN_THROW_EXCEPTION(ex_to_throw, sheratan::errhdl::error_code(errnum::POSIX_SYSTEM, get_error_category()));
  }

  SHERATAN_CHECK(data == sync_pipe_data);
}

void parent_child_sync::unblock_sync_pipe()
{
  errno = 0;
  if(std::fputc(sync_pipe_data, this->sync_pipe_w_) == EOF) {
    int saved_errnum = errno;
    sheratan::errhdl::runtime_error ex_to_throw;
    ex_to_throw << error_category::error_info::posix_errnum(saved_errnum);
    SHERATAN_THROW_EXCEPTION(ex_to_throw, sheratan::errhdl::error_code(errnum::POSIX_SYSTEM, get_error_category()));
  }
}


} // namespace posix

} // namespace process_impl

} // namespace sheratan


// vim: set ts=2 sw=2 et:


