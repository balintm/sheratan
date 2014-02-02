/// \file sheratan/process/posix/exit_status.hpp
/// \brief Process exit status POSIX implementation interface.
/// \ingroup sheratan_process_posix
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#ifndef HG_SHERATAN_PROCESS_POSIX_EXIT_STATUS_HPP
#define HG_SHERATAN_PROCESS_POSIX_EXIT_STATUS_HPP


#include <algorithm>
#include <iosfwd>

#include "sheratan/process/posix/types.hpp"


namespace sheratan {

namespace process_impl {

namespace posix {


namespace test {


class accessor;


}


/// \brief POSIX process exit status.
/// \ingroup sheratan_process_posix
/// \nosubgrouping
class exit_status
{
  friend class test::accessor;

  public:

    /// \brief Value type definition.
    typedef int value_type;

    /// \brief Successful exit status.
    static const value_type SUCCESS;

    /// \brief Unsuccessful exit status.
    static const value_type FAILURE;

  public:

    /// \brief Default constructor.
    /// \par Abrahams exception guarantee:
    /// no-throw
    /// \post <code>after->valid() == false</code>
    exit_status();

  private:

    /// \brief Constructor
    /// \param value Exit status value.
    /// \par Abrahams exception guarantee:
    /// no-throw
    /// \post <code>after->valid() == true</code>
    /// \post <code>after->get_value() == value</code>
    /// \note Only \c process has access to this constructor.
    explicit exit_status(exit_status::value_type value);

    friend class process;

  public:

    /// \brief Non-throwing swap.
    /// \param other Other instance to swap with.
    /// \par Abrahams exception guarantee:
    /// no-throw
    void swap(exit_status &other);

  public:

    /// \brief Determine whether the exit status is valid.
    /// \retval true Valid exit status.
    /// \retval false Invalid exit status.
    /// \par Abrahams exception guarantee:
    /// no-throw
    bool valid() const;

    /// \brief Determine whether the process terminated normally.
    /// \par Abrahams exception guarantee:
    /// no-throw
    /// \retval true Process terminated normally.
    /// \retval false Process did not terminate normally.
    /// \pre <code>before->valid() == true</code>
    /// \note The term "terminated normally" refers to process termination due to calling
    ///       either \c exit or \c _exit function, or returning from \c main.
    bool exited() const;

    /// \brief Get termination status.
    /// \return Process termination status.
    /// \par Abrahams exception guarantee:
    /// no-throw
    /// \pre <code>before->valid() == true</code>
    /// \pre <code>before->exited() == true</code>
    /// \note The function returns "termination status", which is the lower 8 bits of the value
    ///       passed to the \c exit or \c exit_ function or returned from \c main.
    exit_status::value_type get_status() const;

    /// \brief Determine whether the process terminated because of unhandled signal.
    /// \retval true Process was terminated by signal.
    /// \retval false Process was not terminated by signal.
    /// \par Abrahams exception guarantee:
    /// no-throw
    bool signaled() const;

    /// \brief Get termination signal number.
    /// \return Signal number.
    /// \par Abrahams exception guarantee:
    /// no-throw
    /// \pre <code>before->valid() == true</code>
    /// \pre <code>before->signaled() == true</code>
    int get_term_signal() const;

    /// \brief Determine whether the process was stopped by delivery of signal.
    /// \retval true Process was stopped by delivery of signal.
    /// \retval false Process was not stopped by delivery of signal.
    /// \par Abrahams exception guarantee:
    /// no-throw
    /// \pre <code>before->valid() == true</code>
    bool stopped() const;

    /// \brief Get stop signal number.
    /// \return Signal number.
    /// \par Abrahams exception guarantee:
    /// no-throw
    /// \pre <code>before->valid() == true</code>
    /// \pre <code>before->stopped() == true</code>
    int get_stop_signal() const;

    /// \brief Determine whether the process has continued from a job control stop.
    /// \retval true Process has continued.
    /// \retval false Process has not continued.
    /// \par Abrahams exception guarantee:
    /// no-throw
    /// \pre <code>before->valid() == true</code>
    bool continued() const;

    /// \brief Determine whether the process created core-dump.
    /// \retval true Core dumped.
    /// \retval false No core-dump created.
    /// \par Abrahams exception guarantee:
    /// no-throw
    /// \pre <code>before->valid() == true</code>
    bool dumped_core() const;

    /// \brief Get value.
    /// \return Implementation dependent exit status.
    /// \par Abrahams exception guarantee:
    /// strong
    /// \pre <code>before->valid() == true</code>
    exit_status::value_type get_value() const;

  private:

    /// \brief Exit status validity flag.
    bool valid_;

    /// \brief Process exit status value.
    exit_status::value_type value_;
};


/// \brief Non-throwing swap (for Koening lookup).
/// \param es1 First instance to be swapped.
/// \param es2 Second instance to be swapped.
/// \par Abrahams exception guarantee:
/// no-throw
void swap(exit_status &es1, exit_status &es2);

/// \brief Output operator for process exit status.
/// \param os Output stream.
/// \param value Process exit status.
/// \return Output stream.
/// \par Abrahams exception guarantee:
/// weak
template<typename CharT, typename CharTraits>
std::basic_ostream<CharT, CharTraits> & operator<<(std::basic_ostream<CharT, CharTraits> &os, const exit_status &value);


} // namespace posix

} // namespace process_impl

} // namespace sheratan


namespace std {


/// \brief Non-throwing swap (for explicit std::swap calls).
/// \param es1 First instance to be swapped.
/// \param es2 Second instance to be swapped.
/// \par Abrahams exception guarantee:
/// no-throw
template<>
void swap(sheratan::process_impl::posix::exit_status &es1, sheratan::process_impl::posix::exit_status &es2);


} // namespace std


#include "sheratan/process/posix/exit_status.ci"


#endif // HG_SHERATAN_PROCESS_POSIX_EXIT_STATUS_HPP


// vim: set ts=2 sw=2 et:


