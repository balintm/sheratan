/// \file sheratan/process/posix/types.hpp
/// \brief Common POSIX types definitions.
/// \ingroup sheratan_process_posix
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#ifndef HG_SHERATAN_PROCESS_POSIX_TYPES_HPP
#define HG_SHERATAN_PROCESS_POSIX_TYPES_HPP


#include <boost/date_time/posix_time/posix_time_types.hpp>


namespace sheratan {

namespace process_impl {

namespace posix {


/// \brief System time type definition.
typedef boost::posix_time::ptime system_time_type;

/// \brief Signal number type definition.
typedef int signal_number_type;

/// \brief File descriptor type definition.
typedef int file_descriptor_type;

/// \brief File mode.
/// \ingroup sheratan_process_posix
/// \nosubgrouping
struct file_permissions
{
  /// \brief File mode values.
  typedef enum
  {
    NO_PERM     = 0000,  ///< ---------
    USER_READ   = 0400,  ///< r--------
    USER_WRITE  = 0200,  ///< -w-------
    USER_EXEC   = 0100,  ///< --x------
    GROUP_READ  = 0040,  ///< ---r-----
    GROUP_WRITE = 0020,  ///< ----w----
    GROUP_EXEC  = 0010,  ///< -----x---
    OTHER_READ  = 0004,  ///< ------r--
    OTHER_WRITE = 0002,  ///< -------w-
    OTHER_EXEC  = 0001   ///< --------x
  } value_type;
};

/// \brief File mode type definition.
typedef int file_mode_type;


} // namespace posix

} // namespace process_impl

} // namespace sheratan


#endif // HG_SHERATAN_PROCESS_POSIX_TYPES_HPP


// vim: set ts=2 sw=2 et:


