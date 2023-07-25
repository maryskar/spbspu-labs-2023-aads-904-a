#include "sortFunctions.h"
#include <iostream>
#include <cstddef>
#include <forwardList.h>
#include <deque>
#include <list>
#include <cstdlib>
#include "mergeSort.h"
#include "OddEvenSort.h"
#include "quickSort.h"

namespace mashkin
{
  template< class InputIt >
  std::ostream& print(std::ostream& out, InputIt first, InputIt last)
  {
    while (first != last)
    {
      out << *first;
      first++;
      if (first != last)
      {
        out << " ";
      }
    }
    return out;
  }

  void ascendInt(std::ostream& out, size_t numOfElem)
  {
    ForwardList< int > forwardList;

    for (size_t i = 0; i < numOfElem; i++)
    {
      forwardList.push_front(std::rand());
    }

    std::deque< int > queueForMerge(forwardList.begin(), forwardList.end());
    std::list< int > listForMerge(forwardList.begin(), forwardList.end());
    std::deque< int > queueForOddEven(forwardList.begin(), forwardList.end());
    std::list< int > listForOddEven(forwardList.begin(), forwardList.end());
    std::deque< int > queueForQSort(forwardList.begin(), forwardList.end());

    print(out, forwardList.begin(), forwardList.end()) << "\n";

    mergeSort(forwardList, 0, numOfElem - 1, std::less< int >());
    mergeSort(queueForMerge, 0, numOfElem - 1, std::less< int >());
    mergeSort(listForMerge, 0, numOfElem - 1, std::less< int >());
    oddEvenSort(listForOddEven, std::less< int >());
    oddEvenSort(queueForOddEven, std::less< int >());
    quickSort(queueForQSort, 0, numOfElem - 1);

    print(out, forwardList.begin(), forwardList.end()) << "\n";
    print(out, queueForMerge.begin(), queueForMerge.end()) << "\n";
    print(out, listForMerge.begin(), listForMerge.end()) << "\n";
    print(out, listForOddEven.begin(), listForOddEven.end()) << "\n";
    print(out, queueForOddEven.begin(), queueForOddEven.end()) << "\n";
    print(out, queueForQSort.begin(), queueForQSort.end()) << "\n";
  }
}
