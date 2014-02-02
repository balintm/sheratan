/// \file tools/boost_test.hpp
/// \brief Conditional inclusion of Boost.Test library.
/// \ingroup tools
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#ifndef HG_SHERATAN_TOOLS_BOOST_TEST_HPP
#define HG_SHERATAN_TOOLS_BOOST_TEST_HPP


#if defined(SHERATAN_TEST_LINK_STATIC)
# include <boost/test/unit_test.hpp>
#elif defined(SHERATAN_TEST_LINK_DYNAMIC)
# define BOOST_TEST_DYN_LINK
# include <boost/test/unit_test.hpp>
#elif defined(SHERATAN_TEST_LINK_NO)
# include <boost/test/included/unit_test.hpp>
#endif


#endif // HG_SHERATAN_TOOLS_BOOST_TEST_HPP


// vim: set ts=2 sw=2 et:


