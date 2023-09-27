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
}
#endif
