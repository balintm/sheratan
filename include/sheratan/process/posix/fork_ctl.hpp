/// \file sheratan/process/posix/fork_ctl.hpp
/// \brief POSIX fork controller interface.
/// \ingroup sheratan_process_posix
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#ifndef HG_SHERATAN_PROCESS_POSIX_FORK_CTL_TEMPLATE_HPP
#define HG_SHERATAN_PROCESS_POSIX_FORK_CTL_TEMPLATE_HPP


#include "sheratan/process/posix/fwd.hpp"
#include "sheratan/process/posix/exit_status.hpp"


namespace sheratan {

namespace process_impl {

namespace posix {


/// \brief POSIX fork controller.
/// \ingroup sheratan_process_posix
/// \nosubgrouping
class fork_ctl
{
  public:

    /// \brief Virtual destructor.
    /// \par Abrahams exception guarantee:
    /// no-throw
    virtual ~fork_ctl() = 0;

  public:

    /// \brief Clone.
    /// \return Pointer to newly created instance.
    /// \par Abrahams exception guarantee:
    /// strong
    virtual fork_ctl * clone() const = 0;

  public:

    /// \brief Prefork (parent) routine.
    /// \par Abrahams exception guarantee:
    /// strong
    virtual void prefork() = 0;

    /// \brief Postfork (parent) routine.
    /// \param child_process Child process object.
    /// \par Abrahams exception guarantee:
    /// strong
    virtual void postfork(process &child_process) = 0;

    /// \brief Child process routine.
    /// \return Return value of child process.
    /// \par Abrahams exception guarantee:
    /// strong
    virtual exit_status::value_type child() = 0;
};


} // namespace posix

} // namespace process_impl

} // namespace sheratan


#endif // HG_SHERATAN_PROCESS_POSIX_FORK_CTL_TEMPLATE_HPP


// vim: set ts=2 sw=2 et:


