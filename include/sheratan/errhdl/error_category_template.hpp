/// \file sheratan/errhdl/error_category_template.hpp
/// \brief Error category template interface.
/// \ingroup sheratan_errhdl
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#ifndef HG_SHERATAN_ERRHDL_ERROR_CATEGORY_TEMPLATE_HPP
#define HG_SHERATAN_ERRHDL_ERROR_CATEGORY_TEMPLATE_HPP


#include "sheratan/errhdl/error_category.hpp"


namespace sheratan {

namespace errhdl {


/// \brief Error category template.
/// \ingroup sheratan_errhdl
/// \nosubgrouping
template<typename ErrorCategoryTraits>
class error_category_template : public error_category
{
  public:

    /// \brief Custom error information.
    typedef typename ErrorCategoryTraits::error_info error_info;

    /// \brief Error number type definition.
    typedef typename ErrorCategoryTraits::errnum_type errnum_type;

  private:

    /// \brief Restricted constructor.
    /// \note Only \c get_error_category friend function is allowed to create
    /// instance of this class.
    error_category_template();

    template<typename ErrorCategoryTraitsT>
    friend const error_category_template<ErrorCategoryTraitsT> & get_error_category();

  public:

    virtual const char * get_name() const;
    virtual error_category::errnum_type get_default_errnum() const;
};


/// \brief Get error category.
/// \return Error category specified by \c ErrorCategoryTraits template parameter.
/// \par Abrahams exception guarantee:
/// no-throw
template<typename ErrorCategoryTraitsT>
const error_category_template<ErrorCategoryTraitsT> & get_error_category();


} // namespace errhdl

} // namespace sheratan



#include "sheratan/errhdl/error_category_template.ci"


#endif // HG_SHERATAN_ERRHDL_ERROR_CATEGORY_TEMPLATE_HPP


// vim: set ts=2 sw=2 et:


