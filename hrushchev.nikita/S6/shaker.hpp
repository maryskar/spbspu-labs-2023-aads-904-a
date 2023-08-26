#ifndef SHAKER_HPP
#define SHAKER_HPP

#include <functional>

template<typename BidirectionalIt, typename Compare = std::less<>>
void shakerSort(BidirectionalIt begin, BidirectionalIt end, Compare comp = Compare{})
{
  auto left = begin;
  auto right = end - 1;
  while (left < right)
  {
    for (auto it = left; it < right; ++it)
    {
      if (comp(*(it + 1), *it))
      {
        std::swap(*it, *(it + 1));
      }
    }
    --right;
    for (auto it = right; it > left; --it)
    {
      if (comp(*it, *(it - 1)))
      {
        std::swap(*it, *(it - 1));
      }
    }
    ++left;
  }
}

#endif
