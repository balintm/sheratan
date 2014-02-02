/// \file sheratan/errhdl/assert_category.hpp
/// \brief Failed assertion error category interface.
/// \ingroup sheratan_errhdl
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#ifndef HG_SHERATAN_ERRHDL_ASSERT_CATEGORY_HPP
#define HG_SHERATAN_ERRHDL_ASSERT_CATEGORY_HPP


#include "sheratan/errhdl/error_category_template.hpp"
#include "sheratan/errhdl/error_info.hpp"


namespace sheratan {

namespace errhdl {


/// \brief Failed assertion error category errnum.
/// \ingroup sheratan_errhdl
/// \nosubgrouping
struct assert_errnum
{
  public:

    /// \brief Test error category errnum values.
    typedef enum
    {
      UNKNOWN = 0,  ///< Unknown error.
      WARNING,      ///< Warning.
      ERROR,        ///< Error.
      FATAL         ///< Fatal error.
    } value_type;
};


/// \brief Failed assertion error category traits.
/// \ingroup sheratan_errhdl
/// \nosubgrouping
struct assert_category_traits
{
  /// \brief Custom error information.
  struct error_info
  {
    /// \brief Failed assertion type definition.
    typedef const char *failed_assertion_type;

    /// \brief Data item failed assertion type definition.
    typedef boost::error_info<struct assert_category_failed_assertion_tag, error_info::failed_assertion_type> failed_assertion;
  };

  /// \brief Error number type definition.
  typedef assert_errnum::value_type errnum_type;

  /// \brief Default error number.
  static const assert_category_traits::errnum_type default_errnum = assert_errnum::UNKNOWN;

  /// \brief Get category name.
  /// \return C-string containing category name.
  /// \par Abrahams exception guarantee:
  /// no-throw
  static const char * name();
};


/// \brief Failed assertion error category.
/// \ingroup sheratan_errhdl
/// \nosubgrouping
typedef error_category_template<assert_category_traits> assert_category;


/// \brief Get failed assertion error category.
/// \return Failed assertion error category.
/// \par Abrahams exception guarantee:
/// no-throw
const assert_category & get_assert_category();

/// \brief Get failed assertion.
/// \param ex Exception to extract failed assertion from.
/// \return Failed assertion stored in %exception if any,
/// empty string otherwise.
/// \par Abrahams exception guarantee:
/// no-throw
assert_category::error_info::failed_assertion_type get_failed_assertion(const exception &ex);


} // namespace errhdl

} // namespace sheratan


#endif // HG_SHERATAN_ERRHDL_ASSERT_CATEGORY_HPP


// vim: set ts=2 sw=2 et:


