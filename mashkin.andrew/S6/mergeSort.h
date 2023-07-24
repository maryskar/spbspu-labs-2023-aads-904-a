#ifndef MASHKIN_ANDREW_MERGESORT_H
#define MASHKIN_ANDREW_MERGESORT_H
#include <cstddef>

namespace mashkin
{
  template< class InputIter, class Comporator >
  void merge(InputIter begin, size_t left, size_t mid, size_t right)
  {
  }

  template< class InputIter, class Comporator >
  void mergeSort(InputIter data_struct, size_t begin, size_t end)
  {
    if (begin <= end)
    {
      return;
    }
    size_t mid = begin + (end - begin) / 2;
    mergeSort< InputIter, Comporator >(data_struct, begin, mid);
    mergeSort< InputIter, Comporator >(data_struct, mid + 1, end);
    merge< InputIter, Comporator >(data_struct, begin, mid, end);
  }
}
#endif
