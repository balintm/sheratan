/// \file sheratan/errhdl/throw.hpp
/// \brief Exception throwing interface.
/// \ingroup sheratan_errhdl
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#ifndef HG_SHERATAN_ERRHDL_THROW_HPP
#define HG_SHERATAN_ERRHDL_THROW_HPP


#include "sheratan/errhdl/exception.hpp"


namespace sheratan {

namespace errhdl {


/// \brief Throw exception.
/// \param ex Exception instance to be thrown.
/// \post Exception instance passed in \c ex parameter is thrown.
/// Caller can safely assume that call to this function will never
/// return.
void throw_exception(const logic_error &ex);

/// \brief Throw exception.
/// \param ex Exception instance to be thrown.
/// \post Exception instance passed in \c ex parameter is thrown.
/// Caller can safely assume that call to this function will never
/// return.
void throw_exception(const runtime_error &ex);


} // namespace errhdl

} // namespace sheratan


/// \brief Throw exception.
/// \param ex Exception instance to be thrown.
/// \param errcode Error code.
/// \pre Exception instance passed in \c ex parameter must be
/// \c sheratan::errhdl::logic_error (or some of its descendants)
/// or \c sheratan::errhdl::runtime_error (or some of its
/// descendants).
/// \post Exception instance passed in \c ex parameter is initialized
/// with data and thrown. Caller can safely assume that call to this
/// macro will never return.
#define SHERATAN_THROW_EXCEPTION(ex, errcode)            \
  ::sheratan::errhdl::throw_exception(                   \
    (ex)                                                 \
      << ::sheratan::errhdl::error_info::code(errcode)   \
      << ::sheratan::errhdl::error_info::file(__FILE__)  \
      << ::sheratan::errhdl::error_info::line(__LINE__)  \
  )


/// \brief Translate exception.
/// \param ex Exception instance to be thrown.
/// \param errcode Error code.
/// \param errcause Original exception to be translated.
/// \pre Exception instance passed in \c ex parameter must be
/// \c sheratan::errhdl::logic_error (or some of its descendants)
/// or \c sheratan::errhdl::runtime_error (or some of its
/// descendants).
/// \post Exception instance passed in \c ex parameter is initialized
/// with data and thrown. Caller can safely assume that call to this
/// macro will never return.
#define SHERATAN_TRANSLATE_EXCEPTION(ex, errcode, errcause)  \
  ::sheratan::errhdl::throw_exception(                       \
    (ex)                                                     \
      << ::sheratan::errhdl::error_info::code(errcode)       \
      << ::sheratan::errhdl::error_info::file(__FILE__)      \
      << ::sheratan::errhdl::error_info::line(__LINE__)      \
      << ::sheratan::errhdl::error_info::cause(              \
           ::sheratan::errhdl::error_info::cause_type(       \
             (errcause).clone(),                             \
             ::sheratan::errhdl::exception::destroy          \
           )                                                 \
         )                                                   \
  )


#endif // HG_SHERATAN_ERRHDL_THROW_HPP


// vim: set ts=2 sw=2 et:


