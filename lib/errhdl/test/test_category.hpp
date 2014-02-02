/// \file errhdl/test/test_category.hpp
/// \brief Test error category interface.
/// \ingroup sheratan_errhdl_test
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#ifndef HG_SHERATAN_ERRHDL_TEST_TEST_CATEGORY_HPP
#define HG_SHERATAN_ERRHDL_TEST_TEST_CATEGORY_HPP


#include "sheratan/errhdl/error_category_template.hpp"
#include "sheratan/errhdl/error_info.hpp"


namespace sheratan {

namespace errhdl {

namespace test {


/// \brief Test error category errnum.
/// \ingroup sheratan_errhdl_test
/// \nosubgrouping
struct test_errnum
{
  /// \brief Test error category errnum values.
  typedef enum
  {
    UNKNOWN = 0,  ///< Unknown error.
    ERROR_1 = 1,  ///< Error #1.
    ERROR_2 = 2   ///< Error #2.
  } value_type;
};


/// \brief Test error category traits.
/// \ingroup sheratan_errhdl_test
/// \nosubgrouping
struct test_category_traits
{
  /// \brief Custom error information.
  struct error_info
  {
    /// \brief Testing data type definition.
    typedef int testing_data_type;

    /// \brief Data item testing data type definition.
    typedef boost::error_info<struct test_category_testing_data_tag, error_info::testing_data_type> testing_data;
  };

  /// \brief Error number type definition.
  typedef test_errnum::value_type errnum_type;

  /// \brief Default error number.
  static const test_category_traits::errnum_type default_errnum = test_errnum::UNKNOWN;

  /// \brief Get category name.
  /// \return C-string containing category name.
  /// \par Abrahams exception guarantee:
  /// no-throw
  static const char * name();
};


/// \brief Test error category.
/// \ingroup sheratan_errhdl_test
/// \nosubgrouping
typedef sheratan::errhdl::error_category_template<test_category_traits> test_category;


/// \brief Get test error category.
/// \return Test error category.
/// \par Abrahams exception guarantee:
/// no-throw
const test_category & get_test_category();

/// \brief Get testing data.
/// \param ex Exception to extract testing data from.
/// \return Testing data stored in %exception if any,
/// zero string otherwise.
/// \par Abrahams exception guarantee:
/// no-throw
test_category::error_info::testing_data_type get_testing_data(const sheratan::errhdl::exception &ex);


} // namespace test

} // namespace errhdl

} // namespace sheratan


#endif // HG_SHERATAN_ERRHDL_TEST_TEST_CATEGORY_HPP


// vim: set ts=2 sw=2 et:


