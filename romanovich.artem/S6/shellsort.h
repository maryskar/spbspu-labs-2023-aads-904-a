#ifndef SHELLSORT_H
#define SHELLSORT_H
#include <cstddef>
#include <algorithm>
template< typename RandomAccessIterator, typename Compare >
void shellSort(RandomAccessIterator begin, size_t size, Compare comp)
{
  for (size_t gap = size / 2; gap > 0; gap /= 2)
  {
    for (size_t i = gap; i < size; ++i)
    {
      auto temp = *(begin + i);
      size_t j = i;
      while (j >= gap && comp(temp, *(begin + j - gap)))
      {
        *(begin + j) = *(begin + j - gap);
        j -= gap;
      }
      *(begin + j) = temp;
    }
  }
}
#endif
