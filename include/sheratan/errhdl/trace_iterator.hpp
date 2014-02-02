/// \file sheratan/errhdl/trace_iterator.hpp
/// \brief Exception trace iterator interface.
/// \ingroup sheratan_errhdl
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#ifndef HG_SHERATAN_ERRHDL_TRACE_ITERATOR_HPP
#define HG_SHERATAN_ERRHDL_TRACE_ITERATOR_HPP


#include <iterator>

#include "sheratan/errhdl/error_info.hpp"
#include "sheratan/meta/if_then_else.hpp"


namespace sheratan {

namespace errhdl {


/// \brief Exception trace iterator template.
/// \ingroup sheratan_errhdl
/// \nosubgrouping
template<bool IsConstant>
class trace_iterator_template
: public std::iterator<std::forward_iterator_tag, exception, std::ptrdiff_t, typename sheratan::meta::if_then_else<IsConstant, const exception *, exception *>::result, typename sheratan::meta::if_then_else<IsConstant, const exception &, exception &>::result>
{
  public:

    /// \brief Default constructor.
    /// \par Abrahams exception guarantee:
    /// no-throw
    /// \post Iterator is singular.
    trace_iterator_template();

  private:

    /// \brief Constructor.
    /// \param ex Exception being pointed to.
    /// \par Abrahams exception guarantee:
    /// no-throw
    /// \post Iterator is properly initialized and points to \c exception specified by \c ex parameter.
    /// \note Only \c exception has access to this constructor.
    explicit trace_iterator_template(typename trace_iterator_template<IsConstant>::reference ex);

    friend class exception;
    friend class trace_iterator_template<false>;

  public:

    /// \brief Conversion operator to constant iterator.
    /// \par Abrahams exception guarantee:
    /// strong
    operator trace_iterator_template<true>() const;

  public:

    /// \brief Dereference operator.
    /// \return Reference to element being pointed to.
    /// \par Abrahams exception guarantee:
    /// no-throw
    /// \pre Iterator is dereferencable.
    typename trace_iterator_template<IsConstant>::reference operator*() const;

    /// \brief Class dereference operator.
    /// \return Pointer to element being pointed to.
    /// \par Abrahams exception guarantee:
    /// no-throw
    /// \pre Iterator is dereferencable.
    typename trace_iterator_template<IsConstant>::pointer operator->() const;

    /// \brief Pre-increment operator.
    /// \return Reference to incremented iterator.
    /// \par Abrahams exception guarantee:
    /// no-throw
    /// \pre Iterator is dereferencable.
    /// \post Iterator points to the next element.
    trace_iterator_template<IsConstant> & operator++();

    /// \brief Post-increment operator.
    /// \return Copy of the iterator prior to incrementation.
    /// \par Abrahams exception guarantee:
    /// no-throw
    /// \pre Iterator is dereferencable.
    /// \post Iterator points to the next element.
    trace_iterator_template<IsConstant> operator++(int);

    template<bool IsLHSConstant, bool IsRHSConstant>
    friend bool operator==(const trace_iterator_template<IsLHSConstant> &lhs, const trace_iterator_template<IsRHSConstant> &rhs);

  private:

    /// \brief Exception pointer type definition.
    typedef typename sheratan::meta::if_then_else<IsConstant, const exception *, exception *>::result exception_ptr_type;

  private:

    /// \brief Exception being pointed to.
    typename trace_iterator_template<IsConstant>::exception_ptr_type exception_;
};

/// \brief Equality comparison operator.
/// \param lhs Left-hand side parameter.
/// \param rhs Right-hand side parameter.
/// \retval true Left-hand side and right-hand side parameters are equal.
/// \retval false Left-hand side and right-hand side parameters are not equal.
/// \par Abrahams exception guarantee:
/// no-throw
template<bool IsLHSConstant, bool IsRHSConstant>
bool operator==(const trace_iterator_template<IsLHSConstant> &lhs, const trace_iterator_template<IsRHSConstant> &rhs);

/// \brief Inequality comparison operator.
/// \param lhs Left-hand side parameter.
/// \param rhs Right-hand side parameter.
/// \retval true Left-hand side and right-hand side parameters are not equal.
/// \retval false Left-hand side and right-hand side parameters are equal.
/// \par Abrahams exception guarantee:
/// no-throw
template<bool IsLHSConstant, bool IsRHSConstant>
bool operator!=(const trace_iterator_template<IsLHSConstant> &lhs, const trace_iterator_template<IsRHSConstant> &rhs);


/// \brief Exception trace iterator.
/// \ingroup sheratan_errhdl
/// \nosubgrouping
typedef trace_iterator_template<false> trace_iterator;


/// \brief Exception trace constant iterator.
/// \ingroup sheratan_errhdl
/// \nosubgrouping
typedef trace_iterator_template<true> const_trace_iterator;


} // namespace errhdl

} // namespace sheratan


#include "sheratan/errhdl/trace_iterator.ci"


#endif // HG_SHERATAN_ERRHDL_TRACE_ITERATOR_HPP


// vim: set ts=2 sw=2 et:


