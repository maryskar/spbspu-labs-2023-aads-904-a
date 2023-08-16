#ifndef ODDEVENSORT_H
#define ODDEVENSORT_H
#include <cstddef>
#include <algorithm>
template< typename RandomAccessIterator, typename Compare >
void oddEvenSort(RandomAccessIterator begin, size_t size, Compare comp)
{
  bool sorted = false;
  while (!sorted)
  {
    sorted = true;
    for (size_t i = 1; i < size - 1; i += 2)
    {
      if (comp(*(begin + i + 1), *(begin + i)))
      {
        std::swap(*(begin + i), *(begin + i + 1));
        sorted = false;
      }
    }
    for (size_t i = 0; i < size - 1; i += 2)
    {
      if (comp(*(begin + i + 1), *(begin + i)))
      {
        std::swap(*(begin + i), *(begin + i + 1));
        sorted = false;
      }
    }
  }
}
#endif
