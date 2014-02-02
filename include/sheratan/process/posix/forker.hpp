/// \file sheratan/process/posix/forker.hpp
/// \brief POSIX forker interface.
/// \ingroup sheratan_process_posix
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#ifndef HG_SHERATAN_PROCESS_POSIX_FORKER_HPP
#define HG_SHERATAN_PROCESS_POSIX_FORKER_HPP


#include <memory>

#include <boost/noncopyable.hpp>

#include "sheratan/process/posix/process_id.hpp"
#include "sheratan/process/posix/fork_ctl.hpp"


namespace sheratan {

namespace process_impl {

namespace posix {


/// \brief Forker POSIX implementation.
/// \ingroup sheratan_process_posix
/// \nosubgrouping
class forker : private boost::noncopyable
{
  public:

    /// \brief Default constructor.
    /// \par Abrahams exception guarantee:
    /// strong
    forker();

    /// \brief Constructor.
    /// \param fc Fork controller.
    /// \par Abrahams exception guarantee:
    /// strong
    explicit forker(const fork_ctl &fc);

  public:

    /// \brief Get fork controller.
    /// \return Fork controller.
    /// \par Abrahams exception guarantee:
    /// no-throw
    /// \pre Object must not be created by default constructor.
    const fork_ctl & get_fork_ctl() const;

    /// \brief Get fork controller.
    /// \return fork controller.
    /// \par Abrahams exception guarantee:
    /// no-throw
    /// \pre Object must not be created by default constructor.
    fork_ctl & get_fork_ctl();

  public:

    /// \brief Fork.
    /// \param child_process Child process object.
    /// \par Abrahams exception guarantee:
    /// strong
    /// \pre Object must not be created by default constructor.
    /// \note Call to this method will spawn a new process and return
    /// in its calling process. However, it will never return in child
    /// process.
    void fork(process &child_process);

  private:

    /// \brief Fork controller.
    std::auto_ptr<fork_ctl> fork_ctl_;
};


} // namespace posix

} // namespace process_impl

} // namespace sheratan


#endif // HG_SHERATAN_PROCESS_POSIX_FORKER_HPP


// vim: set ts=2 sw=2 et:


