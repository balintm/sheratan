/// \file sheratan/process/error_category.hpp
/// \brief Process management library error category interface.
/// \ingroup sheratan_process
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#ifndef HG_SHERATAN_PROCESS_ERROR_CATEGORY_HPP
#define HG_SHERATAN_PROCESS_ERROR_CATEGORY_HPP


#ifdef SHERATAN_TARGET_OS_LINUX
#  include "sheratan/process/posix/error_category.hpp"
#  include "sheratan/process/posix/namespace.hpp"
#else
#  error FATAL: Target OS not supported!
#endif


#endif // HG_SHERATAN_PROCESS_ERROR_CATEGORY_HPP


// vim: set ts=2 sw=2 et:


