/// \file sheratan/errhdl/error_info.hpp
/// \brief Error information interface.
/// \ingroup sheratan_errhdl
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#ifndef HG_SHERATAN_ERRHDL_ERROR_INFO_HPP
#define HG_SHERATAN_ERRHDL_ERROR_INFO_HPP


#include <boost/exception/info.hpp>
#include <boost/exception/error_info.hpp>

#include "sheratan/errhdl/error_code.hpp"
#include "sheratan/errhdl/exception_fwd.hpp"


namespace sheratan {

namespace errhdl {


/// \brief Error information for all error categories.
/// \ingroup sheratan_errhdl
/// \nosubgrouping
struct error_info
{
  /// \brief Exception code type definition.
  typedef error_code code_type;

  /// \brief Exception data item code type definition.
  typedef boost::error_info<struct exception_code_tag, error_info::code_type> code;

  /// \brief Exception file type definition.
  typedef const char *file_type;

  /// \brief Exception data item file type definition.
  typedef boost::error_info<struct exception_file_tag, error_info::file_type> file;

  /// \brief Exception line type definition.
  typedef unsigned int line_type;

  /// \brief Exception data item line type definition.
  typedef boost::error_info<struct exception_line_tag, error_info::line_type> line;

  /// \brief Exception seconds portion of time type definition.
  typedef time_t seconds_type;

  /// \brief Exception data item seconds portion of time type definition.
  typedef boost::error_info<struct exception_seconds_tag, error_info::seconds_type> seconds;

  /// \brief Exception microseconds portion of time type definition.
  typedef suseconds_t useconds_type;

  /// \brief Exception data item microseconds portion of time type definition.
  typedef boost::error_info<struct exception_useconds_tag, error_info::useconds_type> useconds;

  /// \brief Exception cause type definition.
  typedef boost::shared_ptr<exception> cause_type;

  /// \brief Exception data item cause type definition.
  typedef boost::error_info<struct exception_cause_tag, error_info::cause_type> cause;
};


/// \brief Get error information.
/// \param ex Exception containing stored information.
/// \return Pointer to stored value identified by template parameter,
/// \c NULL in case denoted value is not present.
/// \par Abrahams exception guarantee:
/// no-throw
/// \note Pointer is valid until the exception passed in \c ex parameter
/// is not destroyed.
template <typename ErrorInfo>
const typename ErrorInfo::value_type * get_error_info(const exception &ex);

/// \brief Get error code.
/// \param ex Exception to extract error code from.
/// \return Error code stored in %exception if any,
/// default constructed \c exception::code_type otherwise.
/// \par Abrahams exception guarantee:
/// no-throw
error_info::code_type get_code(const exception &ex);

/// \brief Get file.
/// \param ex Exception to extract file from.
/// \return File stored in %exception if any, empty string otherwise.
/// \par Abrahams exception guarantee:
/// no-throw
error_info::file_type get_file(const exception &ex);

/// \brief Get line.
/// \param ex Exception to extract line from.
/// \return Line stored in %exception if any, zero otherwise.
/// \par Abrahams exception guarantee:
/// no-throw
error_info::line_type get_line(const exception &ex);

/// \brief Get seconds portion of time.
/// \param ex Exception to extract seconds portion of time from.
/// \return Seconds portion of time stored in %exception if any,
/// zero otherwise.
/// \par Abrahams exception guarantee:
/// no-throw
error_info::seconds_type get_seconds(const exception &ex);

/// \brief Get microseconds portion of time.
/// \param ex Exception to extract microseconds portion of time from.
/// \return Microseconds portion of time stored in %exception if any,
/// zero otherwise.
/// \par Abrahams exception guarantee:
/// no-throw
error_info::useconds_type get_useconds(const exception &ex);


} // namespace errhdl

} // namespace sheratan


#include "sheratan/errhdl/error_info.ci"


#endif // HG_SHERATAN_ERRHDL_ERROR_INFO_HPP


// vim: set ts=2 sw=2 et:


