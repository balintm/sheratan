/// \file sheratan/errhdl/exception.hpp
/// \brief Base %exception interface.
/// \ingroup sheratan_errhdl
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#ifndef HG_SHERATAN_ERRHDL_EXCEPTION_HPP
#define HG_SHERATAN_ERRHDL_EXCEPTION_HPP


#include <stdexcept>

#include <boost/exception/exception.hpp>

#include "sheratan/errhdl/error_info.hpp"
#include "sheratan/errhdl/trace_iterator.hpp"


namespace sheratan {

namespace errhdl {


/// \brief Base %exception.
/// \ingroup sheratan_errhdl
/// \nosubgrouping
class exception : public boost::exception
{
  public:

    /// \brief Trace iterator type definition.
    typedef trace_iterator iterator;

    /// \brief Constant trace iterator type definition.
    typedef const_trace_iterator const_iterator;

  public:

    /// \brief Clone exception.
    /// \return Pointer to cloned object.
    /// \throw std::bad_alloc Allocation of cloned object failed.
    /// \par Abrahams exception guarantee:
    /// strong
    /// \note Cloned object is allocated on heap and caller must assume
    /// its ownership. It should be used for direct initialization
    /// of some type of smart pointer. In addition, \c destroy method
    /// must be used to destroy cloned object in order to overcome shared
    /// library boundaries problem.
    virtual exception * clone() const = 0;

    /// \brief Destroy previously allocated exception.
    /// \param ex Exception to be destroyed.
    /// \par Abrahams exception guarantee:
    /// no-throw
    /// \see \c clone
    static void destroy(exception *ex);

  public:

    /// \brief Get constant iterator referring to the first element in trace data.
    /// \return Iterator referring to the first element in trace data.
    /// \par Abrahams exception guarantee:
    /// no-throw
    exception::const_iterator begin() const;

    /// \brief Get constant iterator referring past-the-end of trace data.
    /// \return Iterator referring past-the-end of trace data.
    /// \par Abrahams exception guarantee:
    /// no-throw
    exception::const_iterator end() const;

    /// \brief Get iterator referring to the first element in trace data.
    /// \return Iterator referring to the first element in trace data.
    /// \par Abrahams exception guarantee:
    /// no-throw
    exception::iterator begin();

    /// \brief Get iterator referring past-the-end of trace data.
    /// \return Iterator referring past-the-end of trace data.
    /// \par Abrahams exception guarantee:
    /// no-throw
    exception::iterator end();
};


/// \brief Exception for errors presumably detectable only when the program executes.
/// \ingroup sheratan_errhdl
/// \nosubgrouping
class runtime_error : public exception, public std::runtime_error
{
  public:

    /// \brief Default constructor.
    /// \par Abrahams exception guarantee:
    /// no-throw
    runtime_error();

  public:

    virtual sheratan::errhdl::exception * clone() const;
};


/// \brief Exception for errors presumably detectable before the program executes, such as violations of logical preconditions or class invariants.
/// \ingroup sheratan_errhdl
/// \nosubgrouping
class logic_error : public exception, public std::logic_error
{
  public:

    /// \brief Default constructor.
    /// \par Abrahams exception guarantee:
    /// no-throw
    logic_error();

  public:

    virtual sheratan::errhdl::exception * clone() const;
};


} // namespace errhdl

} // namespace sheratan


#endif // HG_SHERATAN_ERRHDL_EXCEPTION_HPP


// vim: set ts=2 sw=2 et:


