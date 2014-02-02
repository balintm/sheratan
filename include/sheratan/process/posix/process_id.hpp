/// \file sheratan/process/posix/process_id.hpp
/// \brief Process ID POSIX implementation interface.
/// \ingroup sheratan_process_posix
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#ifndef HG_SHERATAN_PROCESS_POSIX_PROCESS_ID_HPP
#define HG_SHERATAN_PROCESS_POSIX_PROCESS_ID_HPP


#include <algorithm>
#include <iosfwd>

#include <sys/types.h>

#include "sheratan/process/posix/fwd.hpp"


namespace sheratan {

namespace process_impl {

namespace posix {

namespace test {


class accessor;


}


/// \brief POSIX process ID.
/// \ingroup sheratan_process_posix
/// \nosubgrouping
class process_id
{
  friend class test::accessor;

  public:

    /// \brief Value type definition.
    typedef ::pid_t value_type;

  public:

    /// \brief Default constructor.
    /// \par Abrahams exception guarantee:
    /// no-throw
    /// \post <code>after->get_value() == `NotAProcess`</code>
    process_id();

  private:

    /// \brief Constructor
    /// \param id Process ID.
    /// \par Abrahams exception guarantee:
    /// no-throw
    /// \post <code>after->get_value() == id</code>
    /// \note Only \c self, \c forker and \c daemonizer have access to this constructor.
    explicit process_id(process_id::value_type id);

    friend class self;
    friend class forker;
    friend class daemonizer;

  public:

    /// \brief Non-throwing swap.
    /// \param other Other instance to swap with.
    /// \par Abrahams exception guarantee:
    /// no-throw
    void swap(process_id &other);

  public:

    /// \brief Get value.
    /// \return Implementation dependent process ID.
    /// \par Abrahams exception guarantee:
    /// strong
    process_id::value_type get_value() const;

  private:

    /// \brief Process ID value.
    process_id::value_type value_;
};


/// \brief Non-throwing swap (for Koening lookup).
/// \param pid1 First instance to be swapped.
/// \param pid2 Second instance to be swapped.
/// \par Abrahams exception guarantee:
/// no-throw
void swap(process_id &pid1, process_id &pid2);

/// \brief Equality comparison operator for process IDs.
/// \param lhs Left-hand side parameter.
/// \param rhs Right-hand side parameter.
/// \retval true Left-hand side parameter and right-hand side parameter are equal.
/// \retval false Left-hand side parameter and right-hand side parameter are not equal.
/// \par Abrahams exception guarantee:
/// no-throw
bool operator==(const process_id &lhs, const process_id &rhs);

/// \brief Inequality comparison operator for process IDs.
/// \param lhs Left-hand side parameter.
/// \param rhs Right-hand side parameter.
/// \retval true Left-hand side parameter and right-hand side parameter are not equal.
/// \retval false Left-hand side parameter and right-hand side parameter are equal.
/// \par Abrahams exception guarantee:
/// no-throw
bool operator!=(const process_id &lhs, const process_id &rhs);

/// \brief Less-than comparison operator for process IDs.
/// \param lhs Left-hand side parameter.
/// \param rhs Right-hand side parameter.
/// \retval true Left-hand side parameter is less than right-hand side parameter.
/// \retval false Left-hand side parameter is not less than right-hand side parameter.
/// \par Abrahams exception guarantee:
/// no-throw
bool operator<(const process_id &lhs, const process_id &rhs);

/// \brief Less-than or equal comparison operator for process IDs.
/// \param lhs Left-hand side parameter.
/// \param rhs Right-hand side parameter.
/// \retval true Left-hand side parameter is less than or equal to right-hand side parameter.
/// \retval false Left-hand side parameter is not less than nor equal to right-hand side parameter.
/// \par Abrahams exception guarantee:
/// no-throw
bool operator<=(const process_id &lhs, const process_id &rhs);

/// \brief Greater-than comparison operator for process IDs.
/// \param lhs Left-hand side parameter.
/// \param rhs Right-hand side parameter.
/// \retval true Left-hand side parameter is greater than right-hand side parameter.
/// \retval false Left-hand side parameter is not greater than right-hand side parameter.
/// \par Abrahams exception guarantee:
/// no-throw
bool operator>(const process_id &lhs, const process_id &rhs);

/// \brief Greater-than or equal comparison operator for process IDs.
/// \param lhs Left-hand side parameter.
/// \param rhs Right-hand side parameter.
/// \retval true Left-hand side parameter is greater than or equal to right-hand side parameter.
/// \retval false Left-hand side parameter is not greater than nor equal to right-hand side parameter.
/// \par Abrahams exception guarantee:
/// no-throw
bool operator>=(const process_id &lhs, const process_id &rhs);

/// \brief Output operator for process ID.
/// \param os Output stream.
/// \param value Process ID.
/// \return Output stream.
/// \par Abrahams exception guarantee:
/// weak
template<typename CharT, typename CharTraits>
std::basic_ostream<CharT, CharTraits> & operator<<(std::basic_ostream<CharT, CharTraits> &os, const process_id &value);


} // namespace posix

} // namespace process_impl

} // namespace sheratan


namespace std {


/// \brief Non-throwing swap (for explicit std::swap calls).
/// \param pid1 First instance to be swapped.
/// \param pid2 Second instance to be swapped.
/// \par Abrahams exception guarantee:
/// no-throw
template<>
void swap(sheratan::process_impl::posix::process_id &pid1, sheratan::process_impl::posix::process_id &pid2);


} // namespace std


#include "sheratan/process/posix/process_id.ci"


#endif // HG_SHERATAN_PROCESS_POSIX_PROCESS_ID_HPP


// vim: set ts=2 sw=2 et:


