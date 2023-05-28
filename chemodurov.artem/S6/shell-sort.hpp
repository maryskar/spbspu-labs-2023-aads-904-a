#ifndef S6_SHELL_SORT_HPP
#define S6_SHELL_SORT_HPP
#include <functional>
#include <map.hpp>

namespace chemodurov
{
  template< typename BidirectionalIt, typename Compare = std::less< > >
  void shellSort(BidirectionalIt begin, size_t size, Compare comp = Compare{})
  {
    Map< size_t, BidirectionalIt > iters;
    iters.insert({0, begin});
    for (size_t d = size / 2, cnt = d; d != 0; d /= 2, cnt = d)
    {
      for (auto i = iters.begin(); i != iters.end(); ++i)
      {
        iters.insert({i->first + d, std::next(i->second, d)});
      }
      for (auto i = iters.at(d); cnt != size; ++i, ++cnt)
      {
        for (size_t j = cnt; j >= d; j -= d)
        {
          BidirectionalIt b1 = (--iters.upper_bound(j))->second;
          BidirectionalIt b2 = (--iters.upper_bound(j - d))->second;
          if (comp(*b1, *b2))
          {
            std::swap(*b1, *b2);
          }
        }
      }
    }
  }
}

#endif
