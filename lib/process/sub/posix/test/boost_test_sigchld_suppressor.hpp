/// \file process/sub/posix/test/boost_test_sigchld_suppressor.hpp
/// \brief SIGCHLD suppressor interface.
/// \ingroup sheratan_process_posix_test
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#ifndef HG_SHERATAN_PROCESS_POSIX_TEST_BOOST_TEST_SIGCHLD_SUPPRESSOR_HPP
#define HG_SHERATAN_PROCESS_POSIX_TEST_BOOST_TEST_SIGCHLD_SUPPRESSOR_HPP


#include <signal.h>


namespace sheratan {

namespace process_impl {

namespace posix {

namespace test {


/// \brief Helper class suppressing reception of SIGCHLD by Boost.Test.
/// \ingroup sheratan_process_posix_test
/// \note The same effect should be reached by defining macro
/// \c BOOST_TEST_IGNORE_NON_ZERO_CHILD_CODE before inclusion of
/// \c boost/test/unit_test.hpp. However, it simply does not work.
class boost_test_sigchld_suppressor
{
  public:

    /// \brief Default constructor.
    /// \par Abrahams exception guarantee:
    /// no-throw
    boost_test_sigchld_suppressor();

    /// \brief Destructor
    /// \par Abrahams exception guarantee:
    /// no-throw
    ~boost_test_sigchld_suppressor();

  public:

    /// \brief No-op.
    /// \par Abrahams exception guarantee:
    /// no-throw
    /// \note This method does nothing, but it is needed to make
    /// compiler shut up about unused variable.
    void no_op() const;

  private:

    /// \brief Original SIGCHLD disposition.
    struct sigaction orig_signal_sigaction_;
};


} // namespace test

} // namespace posix

} // namespace process_impl

} // namespace sheratan


#endif // HG_SHERATAN_PROCESS_POSIX_TEST_BOOST_TEST_SIGCHLD_SUPPRESSOR_HPP


// vim: set ts=2 sw=2 et:



