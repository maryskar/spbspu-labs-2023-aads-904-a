#ifndef MASHKIN_ANDREW_ODDEVENSORT_H
#define MASHKIN_ANDREW_ODDEVENSORT_H
#include <cstddef>
#include <iterator>
#include <iostream>
#include "DetailsOfSortFunction.h"

namespace mashkin
{
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
