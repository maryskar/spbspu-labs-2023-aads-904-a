#ifndef S6_TIMSORT_HPP
#define S6_TIMSORT_HPP
#include <cstddef>

namespace chemodurov
{
  namespace detail
  {
    size_t getMinRun(size_t size)
    {
      size_t r = 0;
      while (size >= 64) {
        r |= size & 1;
        size >>= 1;
      }
      return size + r;
    }
  }

}
#endif
