/// \file sheratan/process/posix/process_template.hpp
/// \brief POSIX process template interface.
/// \ingroup sheratan_process_posix
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#ifndef HG_SHERATAN_PROCESS_POSIX_PROCESS_TEMPLATE_HPP
#define HG_SHERATAN_PROCESS_POSIX_PROCESS_TEMPLATE_HPP


#include "sheratan/process/posix/process.hpp"
#include "sheratan/process/posix/forker.hpp"


namespace sheratan {

namespace process_impl {

namespace posix {


/// \brief Process template POSIX implementation.
/// \ingroup sheratan_process_posix
/// \nosubgrouping
template<typename Tag>
class process_template : public process
{
  public:

    /// \brief Default constructor.
    /// \par Abrahams exception guarantee:
    /// no-throw
    /// \post <code>this->valid() == false</code>
    /// \post <code>this->get_id() == process_id()</code>.
    process_template();

    /// \brief Constructor.
    /// \param fc Fork controller.
    /// \par Abrahams exception guarantee:
    /// strong
    /// \post <code>this->valid() == true</code>
    /// \post <code>this->get_id() != process_id()</code>.
    explicit process_template(const fork_ctl &fc);

  public:

    /// \brief Get fork controller.
    /// \return Fork controller.
    /// \par Abrahams exception guarantee:
    /// no-throw
    /// \pre Object must not be created by default constructor.
    const fork_ctl & get_fork_ctl() const;

    /// \brief Get fork controller.
    /// \return Fork controller.
    /// \par Abrahams exception guarantee:
    /// no-throw
    /// \pre Object must not be created by default constructor.
    fork_ctl & get_fork_ctl();

  private:

    /// \brief Forker.
    forker forker_;
};


} // namespace posix

} // namespace process_impl

} // namespace sheratan


#include "sheratan/process/posix/process_template.ci"


#endif // HG_SHERATAN_PROCESS_POSIX_PROCESS_TEMPLATE_HPP


// vim: set ts=2 sw=2 et:


