#ifndef ODDEVENSORT_H
#define ODDEVENSORT_H
#include <cstddef>
#include <algorithm>
namespace romanovich
{
  template< typename BidirectionalIterator, typename Compare >
  void oddEvenSort(BidirectionalIterator begin, size_t size, Compare comp)
  {
    bool sorted = false;
    while (!sorted)
    {
      sorted = true;
      for (size_t i = 1; i < size - 1; i += 2)
      {
        auto current = std::next(begin, i);
        auto next = std::next(current);
        if (comp(*next, *current))
        {
          std::swap(*current, *next);
          sorted = false;
        }
      }
      for (size_t i = 0; i < size - 1; i += 2)
      {
        auto current = std::next(begin, i);
        auto next = std::next(current);
        if (comp(*next, *current))
        {
          std::swap(*current, *next);
          sorted = false;
        }
      }
    }
  }
}
#endif
