#ifndef QUICKSORT_H
#define QUICKSORT_H
#include <cstddef>
#include <algorithm>
template< typename BidirectionalIterator, typename Compare >
void quickSort(BidirectionalIterator begin, size_t size, Compare comp)
{
  if (size < 2)
  {
    return;
  }
  auto pivot = begin + size - 1;
  auto i = begin;
  for (auto j = begin; j < pivot; ++j)
  {
    if (comp(*j, *pivot))
    {
      std::swap(*i, *j);
      ++i;
    }
  }
  std::swap(*i, *pivot);
  quickSort(begin, i - begin, comp);
  quickSort(i + 1, pivot - i, comp);
}
#endif
