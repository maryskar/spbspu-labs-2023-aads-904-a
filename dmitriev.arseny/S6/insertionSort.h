#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#include <functional>

namespace dmitriev
{
  template < typename BidirectionalIterator, typename Compare >
  void insertionSort(BidirectionalIterator first, BidirectionalIterator last, Compare cmp = Compare())
  {
    if (first == last)
    {
      return;
    }

    for (auto it = std::next(first); it != last; ++it)
    {
      auto value = *it;
      auto hole = it;

      while (hole != first && cmp(value, *std::prev(hole)))
      {
        std::iter_swap(hole, std::prev(hole));
        --hole;
      }

      *hole = value;
    }
  }
}

#endif
