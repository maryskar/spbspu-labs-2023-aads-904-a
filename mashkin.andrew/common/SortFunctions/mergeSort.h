#ifndef MASHKIN_ANDREW_MERGESORT_H
#define MASHKIN_ANDREW_MERGESORT_H
#include <cstddef>
#include <iterator>
#include "ForwardList/forwardList.h"

namespace mashkin
{
  namespace detail
  {
    template< class Iter, class Comp >
    void merge(Iter first, Iter mid, Iter last, Comp comp)
    {
      mashkin::ForwardList< std::remove_reference_t< decltype(*first) > > temp(first, last);
      Iter leftIt = first;
      Iter rightIt = mid;
      auto tempIt = temp.begin();
      while (leftIt != mid && rightIt != last)
      {
        if (comp(*leftIt, *rightIt))
        {
          *tempIt++ = *leftIt++;
        }
        else
        {
          *tempIt++ = *rightIt++;
        }
      }
      while (leftIt != mid)
      {
        *tempIt++ = *leftIt++;
      }
      while (rightIt != last)
      {
        *tempIt++ = *rightIt++;
      }
      tempIt = temp.begin();
      for (Iter it = first; it != last; ++it)
      {
        *it = *tempIt++;
      }
    }
  }

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
