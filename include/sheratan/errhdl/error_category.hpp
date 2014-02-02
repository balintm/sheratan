/// \file sheratan/errhdl/error_category.hpp
/// \brief Error category interface.
/// \ingroup sheratan_errhdl
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#ifndef HG_SHERATAN_ERRHDL_ERROR_CATEGORY_HPP
#define HG_SHERATAN_ERRHDL_ERROR_CATEGORY_HPP


#include <boost/noncopyable.hpp>


namespace sheratan {

namespace errhdl {


/// \brief Abstract base class for error categories.
/// \ingroup sheratan_errhdl
/// \nosubgrouping
class error_category : private boost::noncopyable
{
  public:

    /// \brief Error number type definition.
    typedef int errnum_type;

  public:

    /// \brief Virtual destructor.
    /// \par Abrahams exception guarantee:
    /// no-throw
    virtual ~error_category();

  public:

    /// \brief Equality comparison operator.
    /// \param other Other instance of error category to compare with.
    /// \retval true Error categories are equal.
    /// \retval false Error categories are not equal.
    /// \par Abrahams exception guarantee:
    /// no-throw
    bool operator==(const error_category &other) const;

    /// \brief Inequality comparison operator.
    /// \param other Other instance of error category to compare with.
    /// \retval true Error categories are not equal.
    /// \retval false Error categories are equal.
    /// \par Abrahams exception guarantee:
    /// no-throw
    bool operator!=(const error_category &other) const;

    /// \brief Less-than comparison operator.
    /// \param other Other instance of error category to compare with.
    /// \retval true This instance of error category is less than \c other.
    /// \retval false This instance of error category is not less than \c other.
    /// \par Abrahams exception guarantee:
    /// no-throw
    bool operator<(const error_category &other) const;

  public:

    /// \brief Get category name.
    /// \return C-string containing category name.
    /// \par Abrahams exception guarantee:
    /// no-throw
    virtual const char * get_name() const = 0;

    /// \brief Get category name.
    /// \return C-string containing category name.
    /// \par Abrahams exception guarantee:
    /// no-throw
    virtual error_category::errnum_type get_default_errnum() const = 0;
};


} // namespace errhdl

} // namespace sheratan



#endif // HG_SHERATAN_ERRHDL_ERROR_CATEGORY_HPP


// vim: set ts=2 sw=2 et:


