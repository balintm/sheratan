/// \file sheratan/meta/if_then_else.hpp
/// \brief If-then-else template.
/// \ingroup sheratan_meta
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#ifndef HG_SHERATAN_META_IF_THEN_ELSE_HPP
#define HG_SHERATAN_META_IF_THEN_ELSE_HPP


namespace sheratan {

namespace meta {


/// \brief If-then-else template.
/// \ingroup sheratan_meta
/// \nosubgrouping
template<bool Condition, typename ResultTrue, typename ResultFalse>
struct if_then_else;


/// \brief If-then-else template (partial specialization for true).
/// \ingroup sheratan_meta
/// \nosubgrouping
template<typename ResultTrue, typename ResultFalse>
struct if_then_else<true, ResultTrue, ResultFalse>
{
  /// \brief True yields second template argument.
  typedef ResultTrue result;
};


/// \brief If-then-else template (partial specialization for false).
/// \ingroup sheratan_meta
/// \nosubgrouping
template<typename ResultTrue, typename ResultFalse>
struct if_then_else<false, ResultTrue, ResultFalse>
{
  /// \brief False yields third template argument.
  typedef ResultFalse result;
};


} // namespace meta

} // namespace sheratan


#endif // HG_SHERATAN_META_IF_THEN_ELSE_HPP


// vim: set ts=2 sw=2 et:


