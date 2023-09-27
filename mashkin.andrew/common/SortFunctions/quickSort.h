#ifndef MASHKIN_ANDREW_QUICKSORT_H
#define MASHKIN_ANDREW_QUICKSORT_H
#include <cstddef>
#include <utility>
#include "DetailsOfSortFunction.h"

namespace mashkin
{
  template <typename Iter, typename Comp >
  void quickSort(Iter first, Iter last, Comp comp)
  {
    if (std::distance(first, last)>1)
    {
      Iter bound = detail::partition(first, last, comp);
      quickSort(first, bound, comp);
      quickSort(bound+1, last, comp);
    }
  }
}
#endif
