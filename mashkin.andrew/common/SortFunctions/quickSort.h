#ifndef MASHKIN_ANDREW_QUICKSORT_H
#define MASHKIN_ANDREW_QUICKSORT_H
#include <cstddef>
#include <utility>

namespace mashkin
{
  template <typename Iter, typename Comp>
  Iter partition(Iter first, Iter last, Comp comp)
  {
    auto pivot = last - 1;
    auto i = first;
    for (auto j = first; j != pivot; ++j){
      if (comp(*j, *pivot)){
        std::swap(*i++, *j);
      }
    }
    std::swap(*i, *pivot);
    return i;
  }

  template <typename Iter, typename Comp >
  void quickSort(Iter first, Iter last, Comp comp)
  {
    if (std::distance(first, last)>1){
      Iter bound = partition(first, last, comp);
      quickSort(first, bound, comp);
      quickSort(bound+1, last, comp);
    }
  }
}
#endif
