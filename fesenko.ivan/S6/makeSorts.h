#ifndef MAKESORTS_H
#define MAKESORTS_H
#include <deque>
#include <list>
#include <dictionary/forward-list/forwardList.h>
#include "selectionSort.h"
#include "oddEvenSort.h"
#include "shellSort.h"
#include "fillRandom.h"
#include "print.h"

namespace fesenko
{
  template< typename T, typename Parameter >
  void makeSorts(size_t number, std::ostream &out)
  {
    std::deque< T > deque = fillRandom< std::deque< T > >(number);
    ForwardList< T > forwardList;
    std::list< T > list;
    for (auto it: deque) {
      list.push_front(it);
      forwardList.push_front(it);
    }
    Parameter parameter;
    selectionSort(forwardList.begin(), forwardList.end(), parameter);
    print(forwardList.begin(), forwardList.end(), out) << "\n";

    std::list< T > list1 = list;
    selectionSort(list1.begin(), list1.end(), parameter);
    print(list1.begin(), list1.end(), out) << "\n";
    list1 = list;
    oddEvenSort(list1.begin(), list1.end(), parameter);
    print(list1.begin(), list1.end(), out) << "\n";
    list1 = list;
    shellSort(list1.begin(), list1.end(), parameter);
    print(list1.begin(), list1.end(), out) << "\n";

    std::deque< T > deque1 = deque;
    selectionSort(deque1.begin(), deque1.end(), parameter);
    print(deque1.begin(), deque1.end(), out) << "\n";
    deque1 = deque;
    oddEvenSort(deque1.begin(), deque1.end(), parameter);
    print(deque1.begin(), deque1.end(), out) << "\n";
    deque1 = deque;
    shellSort(deque1.begin(), deque1.end(), parameter);
    print(deque1.begin(), deque1.end(), out) << "\n";
  }
}
#endif
