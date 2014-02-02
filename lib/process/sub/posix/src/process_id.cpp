/// \file process/sub/posix/src/process_id.cpp
/// \brief POSIX process ID implementation.
/// \ingroup sheratan_process_posix
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#include "sheratan/process/posix/process_id.hpp"


namespace sheratan {

namespace process_impl {

namespace posix {


namespace {


/// \brief Not-A-Process process ID.
/// \note Type \c pid_t is signed integral type, according to POSIX so \c -1 should work,
/// but \c 0 is safer and will work as well, since, in practice, there is no process
/// with such PID.
static const process_id::value_type not_a_process = 0;


} // anonymous namespace


process_id::process_id()
: value_(not_a_process)
{
}

process_id::process_id(process_id::value_type id)
: value_(id)
{
}

void process_id::swap(process_id &other)
{
  using std::swap;

  swap(this->value_, other.value_);
}

process_id::value_type process_id::get_value() const
{
  return this->value_;
}

void swap(process_id &pid1, process_id &pid2)
{
  pid1.swap(pid2);
}

bool operator==(const process_id &lhs, const process_id &rhs)
{
  return (!(lhs < rhs)) && (!(rhs < lhs));
}

bool operator!=(const process_id &lhs, const process_id &rhs)
{
  return !(lhs == rhs);
}

bool operator<(const process_id &lhs, const process_id &rhs)
{
  return lhs.get_value() < rhs.get_value();
}

bool operator<=(const process_id &lhs, const process_id &rhs)
{
  return !(rhs < lhs);
}

bool operator>(const process_id &lhs, const process_id &rhs)
{
  return rhs < lhs;
}

bool operator>=(const process_id &lhs, const process_id &rhs)
{
  return !(lhs < rhs);
}


} // namespace posix

} // namespace process_impl

} // namespace sheratan


namespace std {


template<>
void swap(sheratan::process_impl::posix::process_id &pid1, sheratan::process_impl::posix::process_id &pid2)
{
  pid1.swap(pid2);
}


} // namespace std


// vim: set ts=2 sw=2 et:


