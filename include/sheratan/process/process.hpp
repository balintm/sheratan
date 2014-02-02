/// \file sheratan/process/process.hpp
/// \brief Process interface.
/// \ingroup sheratan_process
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#ifndef HG_SHERATAN_PROCESS_PROCESS_HPP
#define HG_SHERATAN_PROCESS_PROCESS_HPP


#ifdef SHERATAN_TARGET_OS_LINUX
#  include "sheratan/process/posix/process.hpp"
#  include "sheratan/process/posix/namespace.hpp"
#else
#  error FATAL: Target OS not supported!
#endif


#endif // HG_SHERATAN_PROCESS_PROCESS_HPP


// vim: set ts=2 sw=2 et:


