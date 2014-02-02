/// \file process/sub/posix/test/boost_test_sigchld_suppressor.cpp
/// \brief SIGCHLD suppressor implementation.
/// \ingroup sheratan_process_posix_test
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#include <boost/test/unit_test.hpp>

#include "boost_test_sigchld_suppressor.hpp"


namespace sheratan {

namespace process_impl {

namespace posix {

namespace test {


boost_test_sigchld_suppressor::boost_test_sigchld_suppressor()
{
  // ignore SIGCHLD
  struct sigaction signal_sigaction;
  signal_sigaction.sa_handler = SIG_DFL;
  signal_sigaction.sa_sigaction = NULL;
  BOOST_REQUIRE_EQUAL(sigemptyset(&signal_sigaction.sa_mask), 0);
  signal_sigaction.sa_flags = 0;
  BOOST_REQUIRE_EQUAL(sigaction(SIGCHLD, &signal_sigaction, &this->orig_signal_sigaction_), 0);
}

boost_test_sigchld_suppressor::~boost_test_sigchld_suppressor()
{
  // restore original SIGCHLD disposition
  BOOST_REQUIRE_EQUAL(sigaction(SIGCHLD, &this->orig_signal_sigaction_, NULL), 0);
}

void boost_test_sigchld_suppressor::no_op() const
{
  // nothing here
}


} // namespace test

} // namespace posix

} // namespace process_impl

} // namespace sheratan


// vim: set ts=2 sw=2 et:


