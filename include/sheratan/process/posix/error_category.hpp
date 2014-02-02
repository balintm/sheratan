/// \file sheratan/process/posix/error_category.hpp
/// \brief Process management library POSIX implementation error category interface.
/// \ingroup sheratan_process_posix
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#ifndef HG_SHERATAN_PROCESS_POSIX_ERROR_CATEGORY_HPP
#define HG_SHERATAN_PROCESS_POSIX_ERROR_CATEGORY_HPP


#include <boost/system/error_code.hpp>

#include "sheratan/errhdl/error_category_template.hpp"
#include "sheratan/errhdl/error_info.hpp"


namespace sheratan {

namespace process_impl {

namespace posix {


/// \brief Process management library POSIX implementation error category errnum.
/// \ingroup sheratan_process_posix
/// \nosubgrouping
struct errnum
{
  /// \brief Process managemet library POSIX implementation error category errnum values.
  typedef enum
  {
    UNKNOWN        = 0,  ///< Unknown error.
    POSIX_SYSTEM   = 1,  ///< POSIX/ANSI C system error. Error information item \c posix_errnum is set.
    BOOST_SYSTEM   = 2,  ///< Boost system error. Error information item \c boost_errnum is set.
    DAEMON_ERROR   = 3,  ///< Error in daemon process.
    PIDFILE_LOCKED = 4   ///< Daemon PID file (a.k.a. lock file) already locked.
  } value_type;
};


/// \brief Process management library POSIX implementation error category traits.
/// \ingroup sheratan_process_posix
/// \nosubgrouping
struct error_category_traits
{
  /// \brief Custom error information.
  struct error_info
  {
    /// \brief POSIX error number (errno) type definition.
    typedef int posix_errnum_type;

    /// \brief Data item errnum definition.
    typedef boost::error_info<struct error_category_posix_errnum_tag, error_info::posix_errnum_type> posix_errnum;

    /// \brief Boost system error number (errno) type definition.
    typedef boost::system::error_code boost_errnum_type;

    /// \brief Data item errnum definition.
    typedef boost::error_info<struct error_category_boost_errnum_tag, error_info::boost_errnum_type> boost_errnum;
  };

  /// \brief Error number type definition.
  typedef sheratan::process_impl::posix::errnum::value_type errnum_type;

  /// \brief Default error number.
  static const error_category_traits::errnum_type default_errnum = process_impl::posix::errnum::UNKNOWN;

  /// \brief Get category name.
  /// \return C-string containing category name.
  /// \par Abrahams exception guarantee:
  /// no-throw
  static const char * name();
};


/// \brief Process management library POSIX implementation error category.
/// \ingroup sheratan_process_posix
/// \nosubgrouping
typedef sheratan::errhdl::error_category_template<error_category_traits> error_category;

/// \brief Get process management library POSIX implementation error category.
/// \return Process management library POSIX implementation error category.
/// \par Abrahams exception guarantee:
/// no-throw
const error_category & get_error_category();

/// \brief Get POSIX error number (errno).
/// \param ex Exception to extract POSIX error number (errno) from.
/// \return POSIX error number (errno) stored in %exception if any,
/// zero otherwise.
/// \par Abrahams exception guarantee:
/// no-throw
error_category::error_info::posix_errnum_type get_posix_errnum(const sheratan::errhdl::exception &ex);

/// \brief Get Boost system error number.
/// \param ex Exception to extract Boost system error number from.
/// \return Boost system error number stored in %exception if any,
/// default-constructed \c boost::system::error_code otherwise.
/// \par Abrahams exception guarantee:
/// no-throw
error_category::error_info::boost_errnum_type get_boost_errnum(const sheratan::errhdl::exception &ex);


} // namespace posix

} // namespace process_impl

} // namespace sheratan


#endif // HG_SHERATAN_PROCESS_POSIX_ERROR_CATEGORY_HPP


// vim: set ts=2 sw=2 et:


