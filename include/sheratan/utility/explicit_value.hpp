/// \file sheratan/utility/explicit_value.hpp
/// \brief Explicit value interface.
/// \ingroup sheratan_utility
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#ifndef HG_SHERATAN_UTILITY_EXPLICIT_VALUE_HPP
#define HG_SHERATAN_UTILITY_EXPLICIT_VALUE_HPP


namespace sheratan {

namespace utility {


/// \brief Explicit value.
/// \ingroup sheratan_utility
/// \nosubgrouping
template<typename ValueTraits, typename ValueTraits::tag::value_type Tag>
class explicit_value
{
  public:

    /// \brief Value type.
    typedef typename ValueTraits::value_type value_type;

  public:

    /// \brief Default constructor.
    /// \par Abrahams exception guarantee:
    /// strong
    /// \post <code>after->get_value == ValueTraits::default_value()</code>
    explicit_value();

    /// \brief Constructor.
    /// \param value Value.
    /// \par Abrahams exception guarantee:
    /// strong
    /// \post <code>after->get_value() == value</code>
    explicit explicit_value(const explicit_value<ValueTraits, Tag>::value_type &value);

  public:

    /// \brief Conversion operator to ValueType.
    /// \par Abrahams exception guarantee:
    /// strong
    operator typename explicit_value<ValueTraits, Tag>::value_type() const;

  public:

    /// \brief Get value.
    /// \return Value.
    /// \par Abrahams exception guarantee:
    /// strong
    typename explicit_value<ValueTraits, Tag>::value_type get_value() const;

    /// \brief Set value.
    /// \param value Value to be set.
    /// \par Abrahams exception guarantee:
    /// strong
    /// \post <code>after->get_value() == value</code>
    void set_value(const explicit_value<ValueTraits, Tag>::value_type &value);

  private:

    /// \brief Value.
    typename explicit_value<ValueTraits, Tag>::value_type value_;
};


} // namespace utility

} // namespace sheratan


#include "sheratan/utility/explicit_value.ci"


#endif // HG_SHERATAN_UTILITY_EXPLICIT_VALUE_HPP


// vim: set ts=2 sw=2 et:


