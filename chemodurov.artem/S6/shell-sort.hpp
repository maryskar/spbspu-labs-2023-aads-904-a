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
    BidirectionalIt end = std::next(begin, size);
    for (size_t d = size / 2, cnt = d; d != 0; d /= 2, cnt = d)
    {
      Map< size_t, BidirectionalIt > temp = iters;
      for (auto i = iters.begin(); i != iters.end(); ++i)
      {
        temp.insert({i->first + d, std::next(i->second, d)});
      }
      iters = temp;
      for (auto i = iters.at(d); cnt != size; ++i, ++cnt)
      {
        for (size_t j = cnt; j >= d; j -= d)
        {
          BidirectionalIt b1 = (--(temp.upper_bound(j)))->second;
          BidirectionalIt b2 = (--(temp.upper_bound(j - d)))->second;
          if (comp(*b1, *b2))
          {
            std::swap(*b1, *b2);
          }
        }
        for (auto j = temp.begin(); j != temp.end(); ++j)
        {
          if (std::next(j->second) != end)
          {
            ++(j->second);
          }
        }
      }
    }
  }
}

#endif
