#ifndef S6_SHAKER_H
#define S6_SHAKER_H
#include <algorithm>

namespace tarasenko
{
  template< typename BidirectIt, typename Compare >
  void shakerSort(BidirectIt begin, BidirectIt last, Compare comp)
  {
    bool was_swapped = true;
    while (was_swapped)
    {
      was_swapped = false;
      for (auto i = begin; i != std::prev(last); i++)
      {
        auto next = std::next(i);
        if (comp(*next, *i))
        {
          std::swap(*i, *next);
          was_swapped = true;
        }
      }
      --last;
      if (!was_swapped)
      {
        break;
      }
      was_swapped = false;
      for (auto i = std::prev(last); i != begin; i--)
      {
        auto prev = std::prev(i);
        if (comp(*i, *prev))
        {
          std::swap(*i, *prev);
          was_swapped = true;
        }
      }
      ++begin;
    }
  }
}
#endif
