/// \file sheratan/utility/id.hpp
/// \brief ID interface.
/// \ingroup sheratan_utility
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#ifndef HG_SHERATAN_UTILITY_ID_HPP
#define HG_SHERATAN_UTILITY_ID_HPP


#include <iosfwd>

#include <boost/shared_ptr.hpp>


namespace sheratan {

namespace utility {


template<typename Tag, template <typename> class SmartPtrT>
class id;


/// \brief Implementation specific ID base.
/// \ingroup sheratan_utility
/// \nosubgrouping
template<typename Tag>
class id_impl_base
{
  public:

    /// \brief Tag definition.
    typedef Tag tag;

    /// \brief Destruct function type definition.
    typedef void (*destroy_function)(id_impl_base *);

  public:

    /// \brief Virtual destructor
    /// \par Abrahams exception guarantee:
    /// no-throw
    virtual ~id_impl_base() = 0;

  public:

    /// \brief Less-than comparison.
    /// \param rhs Other instance to compare with.
    /// \retval true Other instance is less than this instance.
    /// \retval false Other instance is not less than this instance.
    /// \par Abrahams exception guarantee:
    /// strong
    virtual bool less(const id_impl_base<Tag> &rhs) const = 0;

    /// \brief Output.
    /// \param os Output stream.
    /// \return Output stream.
    /// \par Abrahams exception guarantee:
    /// weak
    virtual std::ostream & output(std::ostream &os) const = 0;

    /// \brief Clone ID.
    /// \return Pointer to cloned object.
    /// \throw std::bad_alloc Allocation of cloned object failed.
    /// \par Abrahams exception guarantee:
    /// strong
    /// \note Cloned object is allocated on heap and caller must assume
    /// its ownership. It should be used for direct initialization
    /// of some type of smart pointer. In addition, function returned
    /// by \c get_destroy_function must be used to destroy cloned object
    /// in order to overcome shared library boundaries problem.
    virtual id_impl_base<Tag> * clone() const = 0;

    /// \brief Get destroy function.
    /// \return Pointer to destroy function.
    /// \par Abrahams exception guarantee:
    /// no-throw
    /// \see \c clone
    virtual destroy_function get_destroy_function() const = 0;
};


/// \brief Equality comparison operator for implementation specific IDs.
/// \param lhs Left-hand side parameter.
/// \param rhs Right-hand side parameter.
/// \retval true Left-hand side parameter and right-hand side parameter are equal.
/// \retval false Left-hand side parameter and right-hand side parameter are not equal.
/// \par Abrahams exception guarantee:
/// strong
template<typename Tag>
bool operator==(const id_impl_base<Tag> &lhs, const id_impl_base<Tag> &rhs);

/// \brief Inequality comparison operator for implementation specific IDs.
/// \param lhs Left-hand side parameter.
/// \param rhs Right-hand side parameter.
/// \retval true Left-hand side parameter and right-hand side parameter are not equal.
/// \retval false Left-hand side parameter and right-hand side parameter are equal.
/// \par Abrahams exception guarantee:
/// strong
template<typename Tag>
bool operator!=(const id_impl_base<Tag> &lhs, const id_impl_base<Tag> &rhs);

/// \brief Less-than comparison operator for implementation specific IDs.
/// \param lhs Left-hand side parameter.
/// \param rhs Right-hand side parameter.
/// \retval true Left-hand side parameter is less than right-hand side parameter.
/// \retval false Left-hand side parameter is not less than right-hand side parameter.
/// \par Abrahams exception guarantee:
/// strong
template<typename Tag>
bool operator<(const id_impl_base<Tag> &lhs, const id_impl_base<Tag> &rhs);

/// \brief Less-than or equal comparison operator for implementation specific IDs.
/// \param lhs Left-hand side parameter.
/// \param rhs Right-hand side parameter.
/// \retval true Left-hand side parameter is less than or equal to right-hand side parameter.
/// \retval false Left-hand side parameter is not less than nor equal to right-hand side parameter.
/// \par Abrahams exception guarantee:
/// strong
template<typename Tag>
bool operator<=(const id_impl_base<Tag> &lhs, const id_impl_base<Tag> &rhs);

/// \brief Greater-than comparison operator for implementation specific IDs.
/// \param lhs Left-hand side parameter.
/// \param rhs Right-hand side parameter.
/// \retval true Left-hand side parameter is greater than right-hand side parameter.
/// \retval false Left-hand side parameter is not greater than right-hand side parameter.
/// \par Abrahams exception guarantee:
/// strong
template<typename Tag>
bool operator>(const id_impl_base<Tag> &lhs, const id_impl_base<Tag> &rhs);

/// \brief Greater-than or equal comparison operator for implementation specific IDs.
/// \param lhs Left-hand side parameter.
/// \param rhs Right-hand side parameter.
/// \retval true Left-hand side parameter is greater than or equal to right-hand side parameter.
/// \retval false Left-hand side parameter is not greater than nor equal to right-hand side parameter.
/// \par Abrahams exception guarantee:
/// strong
template<typename Tag>
bool operator>=(const id_impl_base<Tag> &lhs, const id_impl_base<Tag> &rhs);


/// \brief Implementation specific ID.
/// \ingroup sheratan_utility
/// \nosubgrouping
template<typename ValueTraits, typename ValueTraits::tag::value_type Tag>
class id_impl : public id_impl_base<typename ValueTraits::base_tag>
{
  public:

    /// \brief Value type definition.
    typedef typename ValueTraits::value_type value_type;

  public:

    /// \brief Default constructor.
    /// \par Abrahams exception guarantee:
    /// strong
    /// \post <code>after->get_value() == ValueTraits::default_value()</code>
    id_impl();

    /// \brief Constructor.
    /// \param value Value.
    /// \par Abrahams exception guarantee:
    /// strong
    /// \post <code>after->get_value() == value</code>
    explicit id_impl(const id_impl<ValueTraits, Tag>::value_type &value);

  public:

    virtual bool less(const id_impl_base<typename ValueTraits::base_tag> &rhs) const;
    virtual std::ostream & output(std::ostream &os) const;
    virtual id_impl_base<typename ValueTraits::base_tag> * clone() const;
    virtual typename id_impl_base<typename ValueTraits::base_tag>::destroy_function get_destroy_function() const;

  public:

    /// \brief Less-than comparison.
    /// \param rhs Other instance to compare with.
    /// \retval true Other instance is less than this instance.
    /// \retval false Other instance is not less than this instance.
    /// \par Abrahams exception guarantee:
    /// strong
    bool less(const id_impl &rhs) const;

    /// \brief Get value.
    /// \return Value.
    /// \par Abrahams exception guarantee:
    /// strong
    typename id_impl<ValueTraits, Tag>::value_type get_value() const;

    /// \brief Set value.
    /// \param value Value to be set.
    /// \par Abrahams exception guarantee:
    /// strong
    /// \post <code>after->get_value() == value</code>
    void set_value(const id_impl<ValueTraits, Tag>::value_type &value);

  private:

    /// \brief Value.
    typename id_impl<ValueTraits, Tag>::value_type value_;
};


/// \brief ID.
/// \ingroup sheratan_utility
/// \nosubgrouping
template<typename Tag, template <typename> class SmartPtrT = boost::shared_ptr>
class id
{
  public:

    /// \brief Tag definition.
    typedef Tag tag;

    /// \brief Value type definition.
    typedef id_impl_base<Tag> value_type;

  public:

    /// \brief Constructor.
    /// \param value Value.
    /// \par Abrahams exception guarantee:
    /// strong
    /// \post <code>after->get_value() == value</code>
    explicit id(const id<Tag, SmartPtrT>::value_type &value);

  public:

    /// \brief Less-than comparison.
    /// \param rhs Other instance to compare with.
    /// \retval true Other instance is less than this instance.
    /// \retval false Other instance is not less than this instance.
    /// \par Abrahams exception guarantee:
    /// strong
    bool less(const id<Tag, SmartPtrT> &rhs) const;

    /// \brief Get value.
    /// \return Value.
    /// \par Abrahams exception guarantee:
    /// strong
    typename id<Tag, SmartPtrT>::value_type & get_value();

    /// \brief Get value.
    /// \return Value.
    /// \par Abrahams exception guarantee:
    /// strong
    const typename id<Tag, SmartPtrT>::value_type & get_value() const;

    /// \brief Set value.
    /// \param value Value to be set.
    /// \par Abrahams exception guarantee:
    /// strong
    /// \post <code>after->get_value() == value</code>
    void set_value(const id<Tag, SmartPtrT>::value_type &value);

  private:

    /// \brief Value.
    SmartPtrT<typename id<Tag, SmartPtrT>::value_type> value_;
};


/// \brief Equality comparison operator for IDs.
/// \param lhs Left-hand side parameter.
/// \param rhs Right-hand side parameter.
/// \retval true Left-hand side parameter and right-hand side parameter are equal.
/// \retval false Left-hand side parameter and right-hand side parameter are not equal.
/// \par Abrahams exception guarantee:
/// strong
template<typename Tag, template <typename> class SmartPtrT>
bool operator==(const id<Tag, SmartPtrT> &lhs, const id<Tag, SmartPtrT> &rhs);

/// \brief Inequality comparison operator for IDs.
/// \param lhs Left-hand side parameter.
/// \param rhs Right-hand side parameter.
/// \retval true Left-hand side parameter and right-hand side parameter are not equal.
/// \retval false Left-hand side parameter and right-hand side parameter are equal.
/// \par Abrahams exception guarantee:
/// strong
template<typename Tag, template <typename> class SmartPtrT>
bool operator!=(const id<Tag, SmartPtrT> &lhs, const id<Tag, SmartPtrT> &rhs);

/// \brief Less-than comparison operator for IDs.
/// \param lhs Left-hand side parameter.
/// \param rhs Right-hand side parameter.
/// \retval true Left-hand side parameter is less than right-hand side parameter.
/// \retval false Left-hand side parameter is not less than right-hand side parameter.
/// \par Abrahams exception guarantee:
/// strong
template<typename Tag, template <typename> class SmartPtrT>
bool operator<(const id<Tag, SmartPtrT> &lhs, const id<Tag, SmartPtrT> &rhs);

/// \brief Less-than or equal comparison operator for IDs.
/// \param lhs Left-hand side parameter.
/// \param rhs Right-hand side parameter.
/// \retval true Left-hand side parameter is less than or equal to right-hand side parameter.
/// \retval false Left-hand side parameter is not less than nor equal to right-hand side parameter.
/// \par Abrahams exception guarantee:
/// strong
template<typename Tag, template <typename> class SmartPtrT>
bool operator<=(const id<Tag, SmartPtrT> &lhs, const id<Tag, SmartPtrT> &rhs);

/// \brief Greater-than comparison operator for IDs.
/// \param lhs Left-hand side parameter.
/// \param rhs Right-hand side parameter.
/// \retval true Left-hand side parameter is greater than right-hand side parameter.
/// \retval false Left-hand side parameter is not greater than right-hand side parameter.
/// \par Abrahams exception guarantee:
/// strong
template<typename Tag, template <typename> class SmartPtrT>
bool operator>(const id<Tag, SmartPtrT> &lhs, const id<Tag, SmartPtrT> &rhs);

/// \brief Greater-than or equal comparison operator for IDs.
/// \param lhs Left-hand side parameter.
/// \param rhs Right-hand side parameter.
/// \retval true Left-hand side parameter is greater than or equal to right-hand side parameter.
/// \retval false Left-hand side parameter is not greater than nor equal to right-hand side parameter.
/// \par Abrahams exception guarantee:
/// strong
template<typename Tag, template <typename> class SmartPtrT>
bool operator>=(const id<Tag, SmartPtrT> &lhs, const id<Tag, SmartPtrT> &rhs);


} // namespace utility

} // namespace sheratan


#include "sheratan/utility/id.ci"


#endif // HG_SHERATAN_UTILITY_ID_HPP


// vim: set ts=2 sw=2 et:


