/// \file sheratan/process/posix/fwd.hpp
/// \brief Process library POSIX implementation forward declarations.
/// \ingroup sheratan_process_posix
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#ifndef HG_SHERATAN_PROCESS_POSIX_FWD_HPP
#define HG_SHERATAN_PROCESS_POSIX_FWD_HPP


namespace sheratan {

namespace process_impl {

namespace posix {


class process_id;
class exit_status;
class fork_ctl;
class process;
template<typename Tag> class process_template;
class forker;
class daemon;
template<typename Tag> class daemon_template;
class daemonizer;
class self;


} // namespace posix

} // namespace process_impl

} // namespace sheratan



#endif // HG_SHERATAN_PROCESS_POSIX_FWD_HPP


// vim: set ts=2 sw=2 et:


