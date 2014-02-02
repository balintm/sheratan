/// \file process/sub/posix/test/accessor.hpp
/// \brief Test helper accessor interface.
/// \ingroup sheratan_process_posix_test
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#ifndef HG_SHERATAN_PROCESS_POSIX_TEST_ACCESSOR_HPP
#define HG_SHERATAN_PROCESS_POSIX_TEST_ACCESSOR_HPP


#include <boost/shared_ptr.hpp>

#include "sheratan/process/posix/process_id.hpp"
#include "sheratan/process/posix/exit_status.hpp"


namespace sheratan {

namespace process_impl {

namespace posix {

namespace test {


/// \brief Helper class enabling access to private parts of tested classes.
/// \ingroup sheratan_process_posix_test
class accessor
{
  public:

    /// \brief Managed pointer to process_id type definition.
    typedef boost::shared_ptr<sheratan::process_impl::posix::process_id> process_id_ptr;

    /// \brief Managed pointer to exit_status type definition.
    typedef boost::shared_ptr<sheratan::process_impl::posix::exit_status> exit_status_ptr;

  public:

    /// \brief Call private constructor of process_id.
    /// \param id Process ID value.
    /// \return Instance of process_id.
    /// \note See process_id class for more information.
    static accessor::process_id_ptr process_id__process_id(sheratan::process_impl::posix::process_id::value_type id);

    /// \brief Call private constructor of exit_status.
    /// \param value Exit status value.
    /// \return Instance of exit_status.
    /// \note See process_id class for more information.
    static accessor::exit_status_ptr exit_status__exit_status(sheratan::process_impl::posix::exit_status::value_type value);
};


} // namespace test

} // namespace posix

} // namespace process_impl

} // namespace sheratan


#endif // HG_SHERATAN_PROCESS_POSIX_TEST_ACCESSOR_HPP


// vim: set ts=2 sw=2 et:


