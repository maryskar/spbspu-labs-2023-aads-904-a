#ifndef PRINTSORTDATA_H
#define PRINTSORTDATA_H

#include <iostream>
#include <deque>
#include <list>
#include "fillDequeData.h"
#include "insertionSort.h"
#include "quickSort.h"
#include "timSort.h"

namespace dmitriev
{
  namespace details
  {
    template< typename Iterator >
    void print(Iterator first, Iterator last, std::ostream& out)
    {
      if (first == last)
      {
        return;
      }

      out << *first;
      for (++first; first != last; first++)
      {
        out << ' ' << *first;
      }
    }
  }

  template< typename Value, typename Compare >
  void printSortData(size_t number, std::ostream& out, Compare cmp)
  {
    std::deque< Value > deque1 = dmitriev::fiillDequeRandom< Value >(number);
    std::deque< Value > deque2;
    std::deque< Value > deque3;

    std::list< Value > list1;
    std::list< Value > list2;

    ForwardList< Value > forwardList;

    for (auto val : deque1)
    {
      deque2.push_front(val);
      deque3.push_front(val);

      list1.push_front(val);
      list2.push_front(val);

      forwardList.pushFront(val);
    }

    quickSort< typename std::deque< Value >::iterator, Compare >(deque1.begin(), deque1.end(), cmp);
    details::print(deque1.begin(), deque1.end(), out);
    out << '\n';
    insertionSort< typename std::deque< Value >::iterator, Compare >(deque2.begin(), deque2.end(), cmp);
    details::print(deque2.begin(), deque2.end(), out);
    out << '\n';
    timSort< typename std::deque< Value >::iterator, Compare >(deque3.begin(), deque3.end(), cmp);
    details::print(deque3.begin(), deque3.end(), out);
    out << '\n';

    quickSort< typename std::list< Value >::iterator, Compare >(list1.begin(), list1.end(), cmp);
    details::print(list1.begin(), list1.end(), out);
    out << '\n';
    insertionSort< typename std::list< Value >::iterator, Compare >(list2.begin(), list2.end(), cmp);
    details::print(list2.begin(), list2.end(), out);
    out << '\n';

    quickSort< typename ForwardList< Value >::iterator, Compare >(forwardList.begin(), forwardList.end(), cmp);
    details::print(forwardList.begin(), forwardList.end(), out);
    //out << '\n';
  }

}

#endif
