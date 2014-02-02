/// \file utility/test/test_id.hpp
/// \brief Test ID interface.
/// \ingroup sheratan_utility_test
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#ifndef HG_SHERATAN_UTILITY_TEST_TEST_ID_HPP
#define HG_SHERATAN_UTILITY_TEST_TEST_ID_HPP


#include <iosfwd>

#include "sheratan/utility/id.hpp"


namespace sheratan {

namespace utility {

namespace test {


/// \brief Test ID type definition.
typedef sheratan::utility::id<struct test_id_tag> test_id_type;


/// \brief Test ID traits.
/// \ingroup sheratan_utility_test
/// \nosubgrouping
struct test_id_traits
{
  /// \brief Value type definition.
  typedef int value_type;

  /// \brief Base tag.
  typedef test_id_type::tag base_tag;

  /// \brief Value tag.
  /// \ingroup sheratan_utility_test
  /// \nosubgrouping
  struct tag
  {
    /// \brief Value tag values.
    typedef enum
    {
      TEST_ID  ///< Test ID.
    } value_type;
  };

  /// \brief Default value.
  /// \return Default value.
  /// \par Abrahams exception guarantee:
  /// strong
  static test_id_traits::value_type default_value();

  /// \brief Less-than comparison.
  /// \param lhs Left-hand side parameter.
  /// \param rhs Right-hand side parameter.
  /// \retval true Left-hand side parameter is less than right-hand side parameter.
  /// \retval false Left-hand side parameter is not less than right-hand side parameter.
  /// \par Abrahams exception guarantee:
  /// strong
  static bool less(const test_id_traits::value_type &lhs, const test_id_traits::value_type &rhs);

  /// \brief Output.
  /// \param os Output stream.
  /// \param value Value to output.
  /// \return Output stream.
  /// \par Abrahams exception guarantee:
  /// weak
  static std::ostream & output(std::ostream &os, const test_id_traits::value_type &value);

  /// \brief Clone ID.
  /// \param id ID to be cloned.
  /// \return Pointer to cloned object.
  /// \throw std::bad_alloc Allocation of cloned object failed.
  /// \par Abrahams exception guarantee:
  /// strong
  /// \note Cloned object is allocated on heap and caller must assume
  /// its ownership. It should be used for direct initialization
  /// of some type of smart pointer. In addition, function \c destroy
  /// must be used to destroy cloned object in order to overcome shared
  /// library boundaries problem.
  static sheratan::utility::id_impl<test_id_traits, test_id_traits::tag::TEST_ID> * clone(const sheratan::utility::id_impl<test_id_traits, test_id_traits::tag::TEST_ID> &id);

  /// \brief Destroy previously allocated ID.
  /// \param id ID to be destroyed.
  /// \par Abrahams exception guarantee:
  /// no-throw
  /// \see \c clone
  static void destroy(sheratan::utility::id_impl_base<test_id_traits::base_tag> *id);
};


/// \brief Test implementation specific ID type definition.
typedef sheratan::utility::id_impl<test_id_traits, test_id_traits::tag::TEST_ID> test_id_impl_type;


} // namespace test

} // namespace utility

} // namespace sheratan


#endif // HG_SHERATAN_UTILITY_TEST_TEST_ID_HPP


// vim: set ts=2 sw=2 et:


