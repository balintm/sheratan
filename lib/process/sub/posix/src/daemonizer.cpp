/// \file process/sub/posix/src/daemonizer.cpp
/// \brief POSIX daemonizer implementation.
/// \ingroup sheratan_process_posix
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#include "sheratan/errhdl/assert.hpp"
#include "sheratan/process/posix/daemonizer.hpp"
#include "sheratan/process/posix/daemon.hpp"
#include "sheratan/process/posix/process_template.hpp"
#include "daemonization_resources.hpp"
#include "daemonization_ctl_1st.hpp"


namespace sheratan {

namespace process_impl {

namespace posix {


/// \brief First child process type definition.
typedef process_template<struct first_child_tag> first_child_process;


daemonizer::pid_file_value_traits::value_type daemonizer::pid_file_value_traits::default_value()
{
  return "";
}

daemonizer::pid_file_mode_value_traits::value_type daemonizer::pid_file_mode_value_traits::default_value()
{
  return file_permissions::USER_READ | file_permissions::USER_WRITE | file_permissions::GROUP_READ | file_permissions::OTHER_READ;
}

daemonizer::working_dir_value_traits::value_type daemonizer::working_dir_value_traits::default_value()
{
  return "/";
}

daemonizer::stdstreams_redirect_value_traits::value_type daemonizer::stdstreams_redirect_value_traits::default_value()
{
  return "/dev/null";
}

daemonizer::reset_signals_flag_value_traits::value_type daemonizer::reset_signals_flag_value_traits::default_value()
{
  return true;
}


daemonizer::daemonizer()
: resources_()
{
}

daemonizer::daemonizer(
  const daemon_ctl &dc,
  const daemonizer::pid_file_type &pid_file,
  const daemonizer::pid_file_mode_type &pid_file_mode,
  const daemonizer::working_dir_type &working_dir,
  const daemonizer::stdin_redirect_type &stdin_redirect,
  const daemonizer::stdout_redirect_type &stdout_redirect,
  const daemonizer::stderr_redirect_type &stderr_redirect,
  const daemonizer::reset_signals_flag_type &reset_signals_flag
)
: resources_(new daemonization_resources(dc, pid_file, pid_file_mode, working_dir, stdin_redirect, stdout_redirect, stderr_redirect, reset_signals_flag))
{
}

const daemon_ctl & daemonizer::get_daemon_ctl() const
{
  SHERATAN_CHECK(this->resources_.get() != NULL);

  return this->resources_->get_daemon_ctl();
}

daemon_ctl & daemonizer::get_daemon_ctl()
{
  SHERATAN_CHECK(this->resources_.get() != NULL);

  return this->resources_->get_daemon_ctl();
}

void daemonizer::daemonize(daemon &daemon_process)
{
  SHERATAN_CHECK(this->resources_.get() != NULL);

  // let user's daemon controller know that daemonization is about to be executed
  this->resources_->get_daemon_ctl().predaemonize();

  // execute common daemon initialization procedure
  this->resources_->daemon_init_parent();

  // start child process (a.k.a. 1st child)
  first_child_process first_child(daemonization_ctl_1st(*this->resources_));

  // no need to join process, it was already taken care of in daemonization_ctl_1st's postfork routine
  //exit_status status = first_child.join();

  // set daemon's process ID
  daemon_process.set_pid(process_id(this->resources_->get_daemon_pid()));

  // let user's daemon controller know that daemonization is done and this is a parent process
  this->resources_->get_daemon_ctl().postdaemonize(daemon_process);

  // finalize daemonization resources
  this->resources_->finalize();
}


} // namespace posix

} // namespace process_impl

} // namespace sheratan


// vim: set ts=2 sw=2 et:


