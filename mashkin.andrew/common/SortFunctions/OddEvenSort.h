#ifndef MASHKIN_ANDREW_ODDEVENSORT_H
#define MASHKIN_ANDREW_ODDEVENSORT_H
#include <cstddef>
#include <iterator>
#include <iostream>
#include "DetailsOfSortFunction.h"

namespace mashkin
{
  template< class Iter >
  void swapValOfIter(Iter& first, Iter& second)
  {
    auto var = *first;
    *first = *second;
    *second = var;
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

      detail::oddEvenSortImpl(first, second, beforeEnd, last, isSorted, comp);

      first = begin;
      second = begin;
      ++first;
      ++++second;

      detail::oddEvenSortImpl(first, second, beforeEnd, last, isSorted, comp);
    }
  }

  template< class DataStruct, class Comporator >
  void oddEvenSort(DataStruct& dataStruct, Comporator comp)
  {
    bool isSorted = false;

    while (!isSorted)
    {
      isSorted = true;

      auto first = dataStruct.begin();
      auto second = ++dataStruct.begin();
      auto beforeEnd = --dataStruct.end();

      for (;first != beforeEnd && first != dataStruct.end(); std::advance(first, 2), std::advance(second, 2))
      {
        if (!comp(*first, *second))
        {
          std::swap(*first, *second);
          isSorted = false;
        }
      }

      first = ++dataStruct.begin();
      second = ++++dataStruct.begin();

      for (;first != beforeEnd && first != dataStruct.end(); std::advance(first, 2), std::advance(second, 2))
      {
        if (!comp(*first, *second))
        {
          swapValOfIter(first, second);
          isSorted = false;
        }
      }
    }
  }
}
#endif
