#ifndef MASHKIN_ANDREW_MERGESORT_H
#define MASHKIN_ANDREW_MERGESORT_H
#include <cstddef>
#include <iterator>
#include "DetailsOfSortFunction.h"
#include "ForwardList/forwardList.h"

namespace mashkin
{
  template< class Iter, class Comp >
  void mergeSort(Iter first, size_t size, Comp comp)
  {
    if (size <= 1)
    {
      return;
    }
    Iter mid = first;
    Iter last = first;
    std::advance(mid, size / 2);
    std::advance(last, size);
    mergeSort(first, size / 2, comp);
    mergeSort(mid, size - size / 2, comp);
    detail::merge(first, mid, last, comp);
  }
}
#endif
