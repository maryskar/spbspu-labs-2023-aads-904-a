#ifndef S6_SHELL_SORT_HPP
#define S6_SHELL_SORT_HPP
#include <functional>

namespace chemodurov
{
  template< typename BidirectionalIt, typename Compare = std::less< > >
  void shellSort(BidirectionalIt begin, size_t size, Compare comp = Compare{})
  {
    for (size_t d = size / 2, cnt = d; d != 0; d /= 2, cnt = d)
    {
      for (auto i = std::next(begin, d); cnt != size; ++i, ++cnt)
      {
        //
      }
    }
  }
}

#endif
