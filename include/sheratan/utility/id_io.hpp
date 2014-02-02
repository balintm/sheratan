/// \file sheratan/utility/id_io.hpp
/// \brief ID I/O interface.
/// \ingroup sheratan_utility
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#ifndef HG_SHERATAN_UTILITY_ID_IO_HPP
#define HG_SHERATAN_UTILITY_ID_IO_HPP


#include <iosfwd>

#include "sheratan/utility/id.hpp"


namespace sheratan {

namespace utility {


/// \brief Output operator for implementation specific ID.
/// \param os Output stream.
/// \param value ID.
/// \return Output stream.
/// \par Abrahams exception guarantee:
/// weak
template<typename Tag>
std::ostream & operator<<(std::ostream &os, const id_impl_base<Tag> &value);

/// \brief Output operator for ID.
/// \param os Output stream.
/// \param value ID.
/// \return Output stream.
/// \par Abrahams exception guarantee:
/// weak
template<typename Tag, template <typename> class SmartPtrT>
std::ostream & operator<<(std::ostream &os, const id<Tag, SmartPtrT> &value);


} // namespace utility

} // namespace sheratan


#include "sheratan/utility/id_io.ci"


#endif // HG_SHERATAN_UTILITY_ID_IO_HPP


// vim: set ts=2 sw=2 et:


