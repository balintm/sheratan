/// \file sheratan/process/lib_info.hpp
/// \brief Process management library information declarations.
/// \ingroup sheratan_process
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#ifndef HG_SHERATAN_PROCESS_LIB_INFO_HPP
#define HG_SHERATAN_PROCESS_LIB_INFO_HPP


#ifdef SHERATAN_TARGET_OS_LINUX
#  include "sheratan/process/posix/lib_info.hpp"
#  include "sheratan/process/posix/namespace.hpp"
#else
#  error FATAL: Target OS not supported!
#endif


#endif // HG_SHERATAN_PROCESS_LIB_INFO_HPP


// vim: set ts=2 sw=2 et:


