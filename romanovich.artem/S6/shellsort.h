#ifndef SHELLSORT_H
#define SHELLSORT_H
#include <cstddef>
#include <algorithm>
namespace romanovich
{
  template< typename BidirectionalIterator, typename Compare >
  void shellSort(BidirectionalIterator begin, size_t size, Compare comp)
  {
    for (size_t gap = size / 2; gap > 0; gap /= 2)
    {
      for (size_t i = gap; i < size; ++i)
      {
        auto temp = *std::next(begin, i);
        size_t j = i;
        while (j >= gap && comp(temp, *std::next(begin, j - gap)))
        {
          *std::next(begin, j) = *std::next(begin, j - gap);
          j -= gap;
        }
        *std::next(begin, j) = temp;
      }
    }
  }
}
#endif
