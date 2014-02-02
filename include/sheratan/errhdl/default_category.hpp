/// \file sheratan/errhdl/default_category.hpp
/// \brief Default error category interface.
/// \ingroup sheratan_errhdl
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#ifndef HG_SHERATAN_ERRHDL_DEFAULT_CATEGORY_HPP
#define HG_SHERATAN_ERRHDL_DEFAULT_CATEGORY_HPP


#include "sheratan/errhdl/error_category_template.hpp"


namespace sheratan {

namespace errhdl {


/// \brief Default error category errnum.
/// \ingroup sheratan_errhdl
/// \nosubgrouping
struct default_errnum
{
  /// \brief Test error category errnum values.
  typedef enum
  {
    UNKNOWN = 0  ///< Unknown error.
  } value_type;
};


/// \brief Default error category traits.
/// \ingroup sheratan_errhdl
/// \nosubgrouping
struct default_category_traits
{
  /// \brief Custom error information.
  struct error_info
  {
  };

  /// \brief Error number type definition.
  typedef errhdl::default_errnum::value_type errnum_type;

  /// \brief Default error number.
  static const default_category_traits::errnum_type default_errnum = errhdl::default_errnum::UNKNOWN;

  /// \brief Get category name.
  /// \return C-string containing category name.
  /// \par Abrahams exception guarantee:
  /// no-throw
  static const char * name();
};


/// \brief Default error category.
/// \ingroup sheratan_errhdl
/// \nosubgrouping
typedef error_category_template<default_category_traits> default_category;


/// \brief Get default error category.
/// \return Default error category.
/// \par Abrahams exception guarantee:
/// no-throw
const default_category & get_default_category();


} // namespace errhdl

} // namespace sheratan


#endif // HG_SHERATAN_ERRHDL_DEFAULT_CATEGORY_HPP


// vim: set ts=2 sw=2 et:


