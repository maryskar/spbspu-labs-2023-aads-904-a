#ifndef COMPARATOR_HPP
#define COMPARATOR_HPP

namespace turkin
{
  template< typename K, typename C >
  bool eq(const K & lhs, const K & rhs)
  {
    return !C{}(lhs, rhs) && !C{}(lhs, rhs);
  }

  template< typename K, typename C >
  bool neq(const K & lhs, const K & rhs)
  {
    return !eq(lhs, rhs);
  }
}

#endif
