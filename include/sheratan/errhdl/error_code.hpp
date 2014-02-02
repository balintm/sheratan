/// \file sheratan/errhdl/error_code.hpp
/// \brief Error code interface.
/// \ingroup sheratan_errhdl
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#ifndef HG_SHERATAN_ERRHDL_ERROR_CODE_HPP
#define HG_SHERATAN_ERRHDL_ERROR_CODE_HPP


#include "sheratan/errhdl/error_category.hpp"


namespace sheratan {

namespace errhdl {


/// \brief Error code.
/// \ingroup sheratan_errhdl
/// \nosubgrouping
class error_code
{
  public:

    /// \brief Default constructor.
    /// \par Abrahams exception guarantee:
    /// no-throw
    /// \post <code>after->get_errnum() == get_default_category().get_default_errnum()</code>
    /// \post <code>after->get_category() == get_default_category()</code>
    error_code();

    /// \brief Constructor.
    /// \param errnum Error number.
    /// \param category Error category.
    /// \par Abrahams exception guarantee:
    /// no-throw
    /// \post <code>after->get_errnum() == errnum</code>
    /// \post <code>after->get_category() == category</code>
    template<typename ErrorCategory>
    error_code(typename ErrorCategory::errnum_type errnum, const ErrorCategory &category);

  public:

    friend bool operator==(const error_code &lhs, const error_code &rhs);

  public:

    /// \brief Get error number.
    /// \return Error number.
    /// \par Abrahams exception guarantee:
    /// no-throw
    error_category::errnum_type get_errnum() const;

    /// \brief Get error category.
    /// \return Error category.
    /// \par Abrahams exception guarantee:
    /// no-throw
    const error_category & get_category() const;

  public:

    /// \brief Set error number and category.
    /// \param errnum Error number to be set.
    /// \param category Error category to be set.
    /// \par Abrahams exception guarantee:
    /// no-throw
    /// \post <code>after->get_errnum() == errnum</code>
    /// \post <code>after->get_category() == category</code>
    template<typename ErrorCategory>
    void set_error_code(typename ErrorCategory::errnum_type errnum, const ErrorCategory &category);

  private:

    /// \brief Error number.
    error_category::errnum_type errnum_;

    /// \brief Error category.
    const error_category *category_;
};


/// \brief Equality comparison operator.
/// \param lhs Left-hand side parameter.
/// \param rhs Right-hand side parameter.
/// \retval true Left-hand side parameter and right-hand side parameter are equal.
/// \retval false Left-hand side parameter and right-hand side parameter are not equal.
/// \par Abrahams exception guarantee:
/// no-throw
bool operator==(const error_code &lhs, const error_code &rhs);

/// \brief Inequality comparison operator.
/// \param lhs Left-hand side parameter.
/// \param rhs Right-hand side parameter.
/// \retval true Left-hand side parameter and right-hand side parameter are not equal.
/// \retval false Left-hand side parameter and right-hand side parameter are equal.
/// \par Abrahams exception guarantee:
/// no-throw
bool operator!=(const error_code &lhs, const error_code &rhs);


} // namespace errhdl

} // namespace sheratan


#include "sheratan/errhdl/error_code.ci"


#endif // HG_SHERATAN_ERRHDL_ERROR_CODE_HPP


// vim: set ts=2 sw=2 et:


