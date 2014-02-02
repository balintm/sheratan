/// \file sheratan/errhdl/assert.hpp
/// \brief Assertion macros.
/// \ingroup sheratan_errhdl
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#ifndef HG_SHERATAN_ERRHDL_ASSERT_HPP
#define HG_SHERATAN_ERRHDL_ASSERT_HPP


/// \brief Action taken by assertion macros: Do nothing.
#define SHERATAN_ASSERT_ACTION_OFF    0

/// \brief Action taken by assertion macros: Throw exception.
#define SHERATAN_ASSERT_ACTION_THROW  1

/// \brief Action taken by assertion macros: Abort immediately.
#define SHERATAN_ASSERT_ACTION_ABORT  2


#ifndef SHERATAN_ASSERT_WARN
  /// \brief Action taken by SHERATAN_WARN assertion macro.
  /// \note Default action can be overriden by defining
  /// \c SHERATAN_ASSERT_WARN macro prior to inclusion of file
  /// \c errhdl/assert.hpp.
# define SHERATAN_ASSERT_WARN SHERATAN_ASSERT_ACTION_THROW
#endif

#ifndef SHERATAN_ASSERT_CHECK
  /// \brief Action taken by SHERATAN_CHECK assertion macro.
  /// \note Default action can be overriden by defining
  /// \c SHERATAN_ASSERT_CHECK macro prior to inclusion
  /// of file \c errhdl/assert.hpp.
# define SHERATAN_ASSERT_CHECK SHERATAN_ASSERT_ACTION_THROW
#endif

#ifndef SHERATAN_ASSERT_REQUIRE
  /// \brief Action taken by SHERATAN_REQUIRE assertion macro.
  /// \note Default action can be overriden by defining
  /// \c SHERATAN_ASSERT_REQUIRE macro prior to inclusion
  /// of file \c errhdl/assert.hpp.
# define SHERATAN_ASSERT_REQUIRE SHERATAN_ASSERT_ACTION_THROW
#endif


// include files necessary for exception throwing if needed
#if((SHERATAN_ASSERT_WARN == SHERATAN_ASSERT_ACTION_THROW) || (SHERATAN_ASSERT_CHECK == SHERATAN_ASSERT_ACTION_THROW) || (SHERATAN_ASSERT_REQUIRE == SHERATAN_ASSERT_ACTION_THROW))
# include "sheratan/errhdl/throw.hpp"
# include "sheratan/errhdl/assert_category.hpp"
#endif

// include files necessary for aborting if needed
#if((SHERATAN_ASSERT_WARN == SHERATAN_ASSERT_ACTION_ABORT) || (SHERATAN_ASSERT_CHECK == SHERATAN_ASSERT_ACTION_ABORT) || (SHERATAN_ASSERT_REQUIRE == SHERATAN_ASSERT_ACTION_ABORT))
# include <iostream>
# include <cstdlib>
# include "sheratan/errhdl/assert_category.hpp"
#endif


/// \internal
/// \brief Helper macro for throwing assertions.
/// \param assertion Expression to be checked.
/// \param errnum Error number to be inserted into thrown exception.
/// \pre Expression passed in \c assertion argument must be convertible
/// to \c bool.
/// \post In case when asserted expression is not satisfied, exception
/// \c logic_error, with \c assert_category category and error code
/// \c errnum, containing \c error_info::failed_assertion in addition
/// to all data inserted by \c SHERATAN_THROW_EXCEPTION, is thrown.
/// Nothing is done otherwise.
/// \note This macro holds actual implementation of throwing assertions.
#define SHERATAN_ASSERT_HELPER_THROW(assertion, errnum)                                   \
  if(!(assertion)) {                                                                      \
    SHERATAN_THROW_EXCEPTION(                                                             \
      ::sheratan::errhdl::logic_error()                                                   \
        << ::sheratan::errhdl::assert_category::error_info::failed_assertion(#assertion)  \
      ,                                                                                   \
      ::sheratan::errhdl::error_code(                                                     \
        (errnum),                                                                         \
        ::sheratan::errhdl::get_assert_category()                                         \
      )                                                                                   \
    );                                                                                    \
  }

/// \internal
/// \brief Helper macro for aborting assertions.
/// \param assertion Expression to be checked.
/// \param message Message to be printed before aborting.
/// \pre Expression passed in \c assertion argument must be convertible
/// to \c bool.
/// \post In case when asserted expression is not satisfied, \c message
/// is printed to standard error output and program execution
/// is immediately aborted. Nothing is done otherwise.
/// \note This macro holds actual implementation of aborting assertions.
#define SHERATAN_ASSERT_HELPER_ABORT(assertion, message)           \
  if(!(assertion)) {                                               \
    std::cerr                                                      \
      << (message) << ": " << __FILE__ << "(" << __LINE__ << "): " \
      << get_assert_category().get_name()                          \
      << ": "                                                      \
      << #assertion                                                \
      << std::endl                                                 \
    ;                                                              \
    abort();                                                       \
  }


#if SHERATAN_ASSERT_WARN == SHERATAN_ASSERT_ACTION_OFF
# define SHERATAN_WARN(assertion)
#elif SHERATAN_ASSERT_WARN == SHERATAN_ASSERT_ACTION_THROW
  /// \brief Assert (error level: warning).
  /// \param assertion Expression to be checked.
  /// \pre Expression passed in \c assertion argument must be convertible
  /// to \c bool.
  /// \post <code>SHERATAN_ASSERT_WARN == SHERATAN_ASSERT_ACTION_OFF</code>:
  /// No code is generated.
  /// \post <code>SHERATAN_ASSERT_WARN == SHERATAN_ASSERT_ACTION_THROW</code>:
  /// In case when asserted expression is not satisfied, exception
  /// \c logic_error, with \c assert_category category and error code
  /// \c assert_errnum::WARNING, containing \c error_info::failed_assertion
  /// in addition to all data inserted by \c SHERATAN_THROW_EXCEPTION,
  /// is thrown. Nothing is done otherwise.
  /// \post <code>SHERATAN_ASSERT_WARN == SHERATAN_ASSERT_ACTION_ABORT</code>:
  /// In case when asserted expression is not satisfied, warning message
  /// is printed to standard error output and program execution
  /// is immediately aborted. Nothing is done otherwise.
# define SHERATAN_WARN(assertion) SHERATAN_ASSERT_HELPER_THROW(assertion, ::sheratan::errhdl::assert_errnum::WARNING)
#elif SHERATAN_ASSERT_WARN == SHERATAN_ASSERT_ACTION_ABORT
# define SHERATAN_WARN(assertion) SHERATAN_ASSERT_HELPER_ABORT(assertion, "warning")
#endif


#if SHERATAN_ASSERT_CHECK == SHERATAN_ASSERT_ACTION_OFF
# define SHERATAN_CHECK(assertion)
#elif SHERATAN_ASSERT_CHECK == SHERATAN_ASSERT_ACTION_THROW
  /// \brief Assert (error level: error).
  /// \param assertion Expression to be checked.
  /// \pre Expression passed in \c assertion argument must be convertible
  /// to \c bool.
  /// \post <code>SHERATAN_ASSERT_CHECK == SHERATAN_ASSERT_ACTION_OFF</code>:
  /// No code is generated.
  /// \post <code>SHERATAN_ASSERT_CHECK == SHERATAN_ASSERT_ACTION_THROW</code>:
  /// In case when asserted expression is not satisfied, exception
  /// \c logic_error, with \c assert_category category and error code
  /// \c assert_errnum::ERROR, containing \c error_info::failed_assertion
  /// in addition to all data inserted by \c SHERATAN_THROW_EXCEPTION,
  /// is thrown. Nothing is done otherwise.
  /// \post <code>SHERATAN_ASSERT_CHECK == SHERATAN_ASSERT_ACTION_ABORT</code>:
  /// In case when asserted expression is not satisfied, error message
  /// is printed to standard error output and program execution
  /// is immediately aborted. Nothing is done otherwise.
# define SHERATAN_CHECK(assertion) SHERATAN_ASSERT_HELPER_THROW(assertion, ::sheratan::errhdl::assert_errnum::ERROR)
#elif SHERATAN_ASSERT_CHECK == SHERATAN_ASSERT_ACTION_ABORT
# define SHERATAN_CHECK(assertion) SHERATAN_ASSERT_HELPER_ABORT(assertion, "error")
#endif


#if SHERATAN_ASSERT_REQUIRE == SHERATAN_ASSERT_ACTION_OFF
# define SHERATAN_REQUIRE(assertion)
#elif SHERATAN_ASSERT_REQUIRE == SHERATAN_ASSERT_ACTION_THROW
  /// \brief Assert (error level: fatal error).
  /// \param assertion Expression to be checked.
  /// \pre Expression passed in \c assertion argument must be convertible
  /// to \c bool.
  /// \post <code>SHERATAN_ASSERT_REQUIRE == SHERATAN_ASSERT_ACTION_OFF</code>:
  /// No code is generated.
  /// \post <code>SHERATAN_ASSERT_REQUIRE == SHERATAN_ASSERT_ACTION_THROW</code>:
  /// In case when asserted expression is not satisfied, exception
  /// \c logic_error, with \c assert_category category and error code
  /// \c assert_errnum::FATAL, containing \c error_info::failed_assertion
  /// in addition to all data inserted by \c SHERATAN_THROW_EXCEPTION,
  /// is thrown. Nothing is done otherwise.
  /// \post <code>SHERATAN_ASSERT_REQUIRE == SHERATAN_ASSERT_ACTION_ABORT</code>:
  /// In case when asserted expression is not satisfied, fatal error
  /// message is printed to standard error output and program execution
  /// is immediately aborted. Nothing is done otherwise.
# define SHERATAN_REQUIRE(assertion) SHERATAN_ASSERT_HELPER_THROW(assertion, ::sheratan::errhdl::assert_errnum::FATAL)
#elif SHERATAN_ASSERT_REQUIRE == SHERATAN_ASSERT_ACTION_ABORT
# define SHERATAN_REQUIRE(assertion) SHERATAN_ASSERT_HELPER_ABORT(assertion, "FATAL")
#endif


// undefine these macros - they are needed only inside this header file
#undef SHERATAN_ASSERT_ACTION_OFF
#undef SHERATAN_ASSERT_ACTION_THROW
#undef SHERATAN_ASSERT_ACTION_ABORT


#endif // HG_SHERATAN_ERRHDL_ASSERT_HPP


// vim: set ts=2 sw=2 et:


