#ifndef FILLLIST_HPP
#define FILLLIST_HPP

#include <random>
#include <forwardlist.hpp>

namespace hrushchev
{
  void fillRandomFloats(ForwardList< float >& list, size_t size);
  void fillRandomInts(ForwardList< int >& list, size_t size);
}

#endif
