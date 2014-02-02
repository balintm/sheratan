/// \file sheratan/process/parent_child_sync.hpp
/// \brief Parent-child synchronizer interface.
/// \ingroup sheratan_process
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#ifndef HG_SHERATAN_PROCESS_PARENT_CHILD_SYNC_HPP
#define HG_SHERATAN_PROCESS_PARENT_CHILD_SYNC_HPP


#ifdef SHERATAN_TARGET_OS_LINUX
#  include "sheratan/process/posix/parent_child_sync.hpp"
#  include "sheratan/process/posix/namespace.hpp"
#else
#  error FATAL: Target OS not supported!
#endif


#endif // HG_SHERATAN_PROCESS_PARENT_CHILD_SYNC_HPP


// vim: set ts=2 sw=2 et:


