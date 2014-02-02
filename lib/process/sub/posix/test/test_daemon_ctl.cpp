/// \file process/sub/posix/test/test_daemon_ctl.cpp
/// \brief Test daemon controller implementation.
/// \ingroup sheratan_process_posix_test
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#include "test_daemon_ctl.hpp"


namespace sheratan {

namespace process_impl {

namespace posix {

namespace test {


daemon_ctl * test_daemon_ctl::clone() const
{
  return new test_daemon_ctl(*this);
}

void test_daemon_ctl::predaemonize()
{
  // nop
}

void test_daemon_ctl::postdaemonize(daemon &daemon_process)
{
  // nop
}

exit_status::value_type test_daemon_ctl::daemonized_child()
{
  return exit_status::SUCCESS;
}


} // namespace test

} // namespace posix

} // namespace process_impl

} // namespace sheratan


// vim: set ts=2 sw=2 et:


