/// \file process/sub/posix/src/daemonization_ctl_1st.cpp
/// \brief POSIX daemonization 1st fork controller implementation.
/// \ingroup sheratan_process_posix
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#include "sheratan/errhdl/exception.hpp"
#include "sheratan/errhdl/assert.hpp"
#include "sheratan/errhdl/throw.hpp"
#include "sheratan/process/posix/error_category.hpp"
#include "sheratan/process/posix/process_template.hpp"
#include "daemonization_ctl_1st.hpp"
#include "daemonization_ctl_2nd.hpp"
#include "daemonization_resources.hpp"


namespace sheratan {

namespace process_impl {

namespace posix {


/// \brief Second child process type definition.
typedef process_template<struct second_child_tag> second_child_process;


daemonization_ctl_1st::daemonization_ctl_1st(daemonization_resources &resources)
: resources_(resources)
{
}

daemonization_ctl_1st::daemonization_ctl_1st(const daemonization_ctl_1st &that)
: resources_(that.resources_)
{
}

fork_ctl * daemonization_ctl_1st::clone() const
{
  return new daemonization_ctl_1st(*this);
}

void daemonization_ctl_1st::prefork()
{
  // create child pipe
  this->resources_.create_rc_pipe(daemonization_resources::pipe_id::CHILD);

  // create daemon pipe
  this->resources_.create_rc_pipe(daemonization_resources::pipe_id::DAEMON);
}

void daemonization_ctl_1st::postfork(process &child_process)
{
  // close write end of child pipe
  this->resources_.close_rc_pipe(daemonization_resources::pipe_id::CHILD, daemonization_resources::pipe_end::WRITE);

  // close write end of daemon pipe
  this->resources_.close_rc_pipe(daemonization_resources::pipe_id::DAEMON, daemonization_resources::pipe_end::WRITE);

  // join child (always exists and exit status contains information about both child and daemon)
  exit_status status = child_process.join();

  // handle errors
  SHERATAN_CHECK(status.valid());
  if(status.get_status() != exit_status::SUCCESS) {
    // retrieve child exception
    sheratan::errhdl::exception *child_ex_to_throw = NULL;
    sheratan::errhdl::logic_error child_logic_ex_to_throw;
    sheratan::errhdl::runtime_error child_runtime_ex_to_throw;
    child_ex_to_throw = this->resources_.retrieve_ex(daemonization_resources::pipe_id::CHILD, child_logic_ex_to_throw, child_runtime_ex_to_throw);
    // check error code
    sheratan::errhdl::error_code ec = get_code(*child_ex_to_throw);
    if((ec.get_category() == sheratan::process_impl::posix::get_error_category()) && (ec.get_errnum() == errnum::DAEMON_ERROR)) {
      // retrieve daemon exceptionin case of daemon failure
      sheratan::errhdl::exception *daemon_ex_to_throw = NULL;
      sheratan::errhdl::logic_error daemon_logic_ex_to_throw;
      sheratan::errhdl::runtime_error daemon_runtime_ex_to_throw;
      daemon_ex_to_throw = this->resources_.retrieve_ex(daemonization_resources::pipe_id::DAEMON, daemon_logic_ex_to_throw, daemon_runtime_ex_to_throw);
      // add it into child exception as a cause
      *child_ex_to_throw << sheratan::errhdl::error_info::cause(sheratan::errhdl::error_info::cause_type(daemon_ex_to_throw->clone(), sheratan::errhdl::exception::destroy));
    }
    // throw exception
    sheratan::errhdl::runtime_error *runtime_error_to_throw = dynamic_cast<sheratan::errhdl::runtime_error *>(child_ex_to_throw);
    if(runtime_error_to_throw) {
      throw *runtime_error_to_throw;
    }
    sheratan::errhdl::logic_error *logic_error_to_throw = dynamic_cast<sheratan::errhdl::logic_error *>(child_ex_to_throw);
    if(logic_error_to_throw) {
      throw *logic_error_to_throw;
    }
    SHERATAN_CHECK(false);
  }

  // retrieve and store daemon's PID
  this->resources_.retrieve_daemon_pid(daemonization_resources::pipe_id::DAEMON);
}

exit_status::value_type daemonization_ctl_1st::child()
{
  try {
    // execute common daemon initialization procedure
    this->resources_.daemon_init_child();

    // start daemon process (a.k.a. 2nd child)
    second_child_process second_child(daemonization_ctl_2nd(this->resources_));

    // no need to join process, it was already taken care of in daemonization_ctl_2nd's postfork routine,
    // not speaking about that it exits only in case of an error (it is a daemon, remember?) and thus
    // there must be little more sophisticated handling in place (see daemonization_ctl_2nd's postfork
    // routine for details)
    //exit_status status = second_child.join();

    // finalize daemonization resources
    this->resources_.finalize();

    // detach daemon process (a.k.a. 2nd child)
    second_child.detach();

    // successful return
    return exit_status::SUCCESS;
  }
  catch(sheratan::errhdl::runtime_error &ex) {
    // report failure
    this->resources_.report_ex(daemonization_resources::pipe_id::CHILD, ex);

    // finalize daemonization resources
    this->resources_.finalize();

    // unsuccessful return
    return exit_status::FAILURE;
  }
  catch(sheratan::errhdl::logic_error &ex) {
    // report failure
    this->resources_.report_ex(daemonization_resources::pipe_id::CHILD, ex);

    // finalize daemonization resources
    this->resources_.finalize();

    // unsuccessful return
    return exit_status::FAILURE;
  }
  catch(...) {
    // report failure
    this->resources_.report_unknown_ex(daemonization_resources::pipe_id::CHILD);

    // finalize daemonization resources
    this->resources_.finalize();

    // unsuccessful return
    return exit_status::FAILURE;
  }
}


} // namespace posix

} // namespace process_impl

} // namespace sheratan


// vim: set ts=2 sw=2 et:


