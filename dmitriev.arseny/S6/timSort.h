#ifndef TIMSORT_H
#define TIMSORT_H

#include <forwardList.h>
#include "insertionSort.h"

namespace dmitriev
{
  namespace details
  {
    int minRunLength(int n)
    {
      int r = 0;
      while (n >= 64)
      {
        r |= n & 1;
        n >>= 1;
      }
      return n + r;
    }

    template< class Iterator, class Comp >
    void inplaceMerge(Iterator first, Iterator mid, Iterator last, Comp comp)
    {
      dmitriev::ForwardList< std::remove_reference_t< decltype(*first) > > temp;
      temp.insertAfter(temp.beforeBegin(), first, last);
      Iterator leftIt = first;
      Iterator rightIt = mid;
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
      for (Iterator it = first; it != last; ++it)
      {
        *it = *tempIt++;
      }
    }

    template < typename RandomIterator, typename Compare >
    void merge(RandomIterator first, RandomIterator last, Compare cmp, int minRun)
    {
      const int n = std::distance(first, last);
      if (n <= minRun)
      {
        return;
      }
      RandomIterator mid = first + n / 2;
      merge(first, mid, cmp, minRun);
      merge(mid, last, cmp, minRun);

      inplaceMerge(first, mid, last, cmp);
    }
  }

  template < typename RandomIterator, typename Compare >
  void timSort(RandomIterator first, RandomIterator last, Compare cmp = Compare())
  {
    int minMerge = 32;
    int n = std::distance(first, last);
    if (n < 2)
    {
      return;
    }
    if (n < minMerge)
    {
      insertionSort(first, last, cmp);
      return;
    }

    int minRun = details::minRunLength(n);
    RandomIterator cur = first;
    while (std::distance(cur, last) >= minRun)
    {
      RandomIterator end = std::min(cur + minRun, last);
      insertionSort(cur, end, cmp);
      cur = end;
    }
    details::merge(first, last, cmp, minRun);
  }
}

#endif
