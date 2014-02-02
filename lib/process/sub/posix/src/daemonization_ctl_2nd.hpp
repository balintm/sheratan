/// \file process/sub/posix/src/daemonization_ctl_2nd.hpp
/// \brief POSIX daemonization 2nd fork controller interface.
/// \ingroup sheratan_process_posix
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#ifndef HGI_SHERATAN_PROCESS_POSIX_DAEMONIZATION_CTL_2ND_HPP
#define HGI_SHERATAN_PROCESS_POSIX_DAEMONIZATION_CTL_2ND_HPP


#include "sheratan/process/posix/fwd.hpp"
#include "sheratan/process/posix/fork_ctl.hpp"
#include "sheratan/process/posix/parent_child_sync.hpp"
#include "daemonization_fwd.hpp"


namespace sheratan {

namespace process_impl {

namespace posix {


/// \brief POSIX 2nd daemonization fork controller.
/// \ingroup sheratan_process_posix
/// \nosubgrouping
class daemonization_ctl_2nd : public fork_ctl
{
  public:

    /// \brief Constructor.
    /// \param resources Daemonization resources.
    /// \par Abrahams exception guarantee:
    /// strong
    daemonization_ctl_2nd(daemonization_resources &resources);

    /// \brief Copy constructor.
    /// \param that Other instance to copy from.
    /// \par Abrahams exception guarantee:
    /// strong
    daemonization_ctl_2nd(const daemonization_ctl_2nd &that);

    /// \brief Destructor.
    /// \par Abrahams exception guarantee:
    /// no-throw
    ~daemonization_ctl_2nd();

  public:

    virtual fork_ctl * clone() const;

  public:

    virtual void prefork();

    virtual void postfork(process &child_process);

    virtual exit_status::value_type child();

  private:

    /// \brief Create synchronization pipe.
    /// \par Abrahams exception guarantee:
    /// strong
    void create_sync_pipe();

    /// \brief Close synchronization pipe.
    /// \par Abrahams exception guarantee:
    /// no-throw
    void close_sync_pipe();

    /// \brief Wait on synchronization pipe.
    /// \par Abrahams exception guarantee:
    /// strong
    void wait_sync_pipe();

    /// \brief Unblock synchronization pipe.
    /// \par Abrahams exception guarantee:
    /// strong
    void unblock_sync_pipe();

    /// \brief Set up SIGCHLD handler.
    /// \par Abrahams exception guarantee:
    /// strong
    void setup_sigchld();

    /// \brief SIGCHLD handler.
    /// \par Abrahams exception guarantee:
    /// strong
    static void sigchld_handler(int);

  private:

    /// \brief Daemonization resources.
    daemonization_resources &resources_;

    /// \brief Synchronization pipe read-end.
    std::FILE *sync_pipe_r_;

    /// \brief Synchronization pipe write-end.
    std::FILE *sync_pipe_w_;
};


} // namespace posix

} // namespace process_impl

} // namespace sheratan


#endif // HGI_SHERATAN_PROCESS_POSIX_DAEMONIZATION_RESOURCES_2ND_HPP


// vim: set ts=2 sw=2 et:


