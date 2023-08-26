#ifndef SHAKER_HPP
#define SHAKER_HPP

#include <functional>

namespace hrushchev
{
  template< typename RandomIt, typename Compare = std::less< > >
  void shakerSort(RandomIt begin, RandomIt end, Compare comp = Compare{})
  {
    auto left = begin;
    auto right = std::prev(end);
    while (left < right)
    {
      for (auto it = left; it != right; ++it)
      {
        if (comp(*(std::next(it)), *it))
        {
          std::swap(*it, *(std::next(it)));
        }
      }
      --right;
      for (auto it = right; it != left; --it)
      {
        if (comp(*it, *(std::prev(it))))
        {
          std::swap(*it, *(std::prev(it)));
        }
      }
      ++left;
    }
  }
}
#endif
