/// \file sheratan/process/posix/self.hpp
/// \brief Self process POSIX implementaton interface.
/// \ingroup sheratan_process_posix
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#ifndef HG_SHERATAN_PROCESS_POSIX_SELF_HPP
#define HG_SHERATAN_PROCESS_POSIX_SELF_HPP


#include <boost/noncopyable.hpp>

#include "sheratan/process/posix/process_id.hpp"


namespace sheratan {

namespace process_impl {

namespace posix {


/// \brief Self process POSIX implementation.
/// \ingroup sheratan_process_posix
/// \nosubgrouping
class self : private boost::noncopyable
{
  private:

    /// \brief Restricted default constructor.
    /// \par Abrahams exception guarantee:
    /// strong
    self();

  public:

    /// \brief Get process ID.
    /// \return Process ID.
    /// \par Abrahams exception guarantee:
    /// no-throw
    static process_id get_pid();

    /// \brief Get parent process ID.
    /// \return Parent process ID.
    /// \par Abrahams exception guarantee:
    /// no-throw
    static process_id get_parent_pid();
};


} // namespace posix

} // namespace process_impl

} // namespace sheratan


#endif // HG_SHERATAN_PROCESS_POSIX_SELF_HPP


// vim: set ts=2 sw=2 et:


