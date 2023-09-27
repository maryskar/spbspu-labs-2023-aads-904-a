#ifndef MASHKIN_ANDREW_DETAILSOFSORTFUNCTION_H
#define MASHKIN_ANDREW_DETAILSOFSORTFUNCTION_H
#include <ForwardList/forwardList.h>


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

  template< class Iter, class Comp >
  void oddEvenSortImpl(Iter first, Iter second, Iter beforeEnd, Iter last, bool& isSorted, Comp comp)
  {
    for (; second != beforeEnd && second != last; std::advance(first, 2), std::advance(second, 2))
    {
      if (!comp(*first, *second))
      {
        std::swap(*first, *second);
        isSorted = false;
      }
    }
  }
}
#endif
