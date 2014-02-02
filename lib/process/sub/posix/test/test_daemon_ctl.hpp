/// \file process/sub/posix/test/test_daemon_ctl.hpp
/// \brief Test daemon controller interface.
/// \ingroup sheratan_process_posix_test
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#ifndef HG_SHERATAN_PROCESS_POSIX_TEST_TEST_DAEMON_CTL_HPP
#define HG_SHERATAN_PROCESS_POSIX_TEST_TEST_DAEMON_CTL_HPP


#include <cstdio>

#include "sheratan/process/posix/daemon_ctl.hpp"


namespace sheratan {

namespace process_impl {

namespace posix {

namespace test {


/// \brief Test daemon controller.
/// \ingroup sheratan_process_posix_test
/// \nosubgrouping
class test_daemon_ctl : public sheratan::process_impl::posix::daemon_ctl
{
  public:

    virtual daemon_ctl * clone() const;

  public:

    virtual void predaemonize();

    virtual void postdaemonize(daemon &);

    virtual exit_status::value_type daemonized_child();
};


} // namespace test

} // namespace posix

} // namespace process_impl

} // namespace sheratan


#endif // HG_SHERATAN_PROCESS_POSIX_TEST_TEST_DAEMON_CTL_HPP


// vim: set ts=2 sw=2 et:


