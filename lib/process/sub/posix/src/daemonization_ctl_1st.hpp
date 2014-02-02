/// \file process/sub/posix/src/daemonization_ctl_1st.hpp
/// \brief POSIX daemonization 1st fork controller interface.
/// \ingroup sheratan_process_posix
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#ifndef HGI_SHERATAN_PROCESS_POSIX_DAEMONIZATION_CTL_1ST_HPP
#define HGI_SHERATAN_PROCESS_POSIX_DAEMONIZATION_CTL_1ST_HPP


#include "sheratan/process/posix/fork_ctl.hpp"
#include "sheratan/process/posix/fwd.hpp"
#include "daemonization_fwd.hpp"


namespace sheratan {

namespace process_impl {

namespace posix {


/// \brief POSIX 1st daemonization fork controller.
/// \ingroup sheratan_process_posix
/// \nosubgrouping
class daemonization_ctl_1st : public fork_ctl
{
  public:

    /// \brief Constructor.
    /// \param resources Daemonization resources.
    /// \par Abrahams exception guarantee:
    /// strong
    daemonization_ctl_1st(daemonization_resources &resources);

    /// \brief Copy constructor.
    /// \param that Other instance to copy from.
    /// \par Abrahams exception guarantee:
    /// strong
    daemonization_ctl_1st(const daemonization_ctl_1st &that);

  public:

    virtual fork_ctl * clone() const;

  public:

    virtual void prefork();

    virtual void postfork(process &child_process);

    virtual exit_status::value_type child();

  private:

    /// \brief Daemonization resources.
    daemonization_resources &resources_;
};


} // namespace posix

} // namespace process_impl

} // namespace sheratan


#endif // HGI_SHERATAN_PROCESS_POSIX_DAEMONIZATION_RESOURCES_1ST_HPP


// vim: set ts=2 sw=2 et:


