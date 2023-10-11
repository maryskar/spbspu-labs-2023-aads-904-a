#ifndef MASHKIN_ANDREW_ODDEVENSORT_H
#define MASHKIN_ANDREW_ODDEVENSORT_H
#include <cstddef>
#include <iterator>
#include <iostream>

namespace mashkin
{
  namespace detail
  {
    template< class Iter, class Comp >
    void oddEvenSortImpl(Iter first, Iter second, Iter beforeEnd, Iter last, bool& isSorted, Comp comp)
    {
      for (; first != beforeEnd && first != last; std::advance(first, 2), std::advance(second, 2))
      {
        if (comp(*second, *first))
        {
          std::swap(*first, *second);
          isSorted = false;
        }
      }
    }
  }

  template< class Iter, class Comp >
  void oddEvenSort(Iter first, Iter last, Comp comp)
  {
    bool isSorted = false;
    while (!isSorted)
    {
      isSorted = true;
      auto begin = first;
      auto second = first;
      ++second;
      auto beforeEnd = last;
      --beforeEnd;
      detail::oddEvenSortImpl(begin, second, beforeEnd, last, isSorted, comp);
      first = begin;
      second = begin;
      ++begin;
      ++++second;
      detail::oddEvenSortImpl(begin, second, beforeEnd, last, isSorted, comp);
    }
  }
}
#endif
