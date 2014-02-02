/// \file utility/test/test_id_counters.hpp
/// \brief Test ID counters declaration.
/// \ingroup sheratan_utility_test
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#ifndef HG_SHERATAN_UTILITY_TEST_TEST_ID_COUNTERS_HPP
#define HG_SHERATAN_UTILITY_TEST_TEST_ID_COUNTERS_HPP


#include <stddef.h>

#include "sheratan/utility/id.hpp"


namespace sheratan {

namespace utility {

namespace test {


/// \brief Number of cloned ID objects.
extern ssize_t id_impl_counter;


} // namespace test

} // namespace utility

} // namespace sheratan


#endif // HG_SHERATAN_UTILITY_TEST_TEST_ID_COUNTERS_HPP


// vim: set ts=2 sw=2 et:


