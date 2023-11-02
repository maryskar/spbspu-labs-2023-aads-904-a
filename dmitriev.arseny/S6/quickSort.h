#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <algorithm>
#include <iterator>

namespace dmitriev
{
  template < typename ForwardIterator, typename Compare >
  void quickSort(ForwardIterator first, ForwardIterator last, Compare cmp = Compare())
  {
    if (first == last || std::next(first) == last)
    {
      return;
    }

    ForwardIterator pivot = std::next(first, std::distance(first, last) - 1);
    ForwardIterator wall = first;

    for (ForwardIterator current = first; current != pivot; ++current)
    {
      if (cmp(*current, *pivot))
      {
        std::iter_swap(current, wall++);
      }
    }

    std::iter_swap(wall, pivot);

    quickSort(first, wall, cmp);
    quickSort(++wall, last, cmp);
  }

}

#endif
