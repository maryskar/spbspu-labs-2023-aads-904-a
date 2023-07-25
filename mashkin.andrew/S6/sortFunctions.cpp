#include "sortFunctions.h"
#include <iostream>
#include <cstddef>
#include <forwardList.h>
#include <deque>
#include <list>
#include <cstdlib>
#include "mergeSort.h"

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
    std::deque< int > queue(forwardList.begin(), forwardList.end());
    std::list< int > list(forwardList.begin(), forwardList.end());

    print(out, forwardList.begin(), forwardList.end()) << "\n";

    mergeSort(forwardList, 0, numOfElem - 1, std::less< int >());
    mergeSort(queue, 0, numOfElem - 1, std::less< int >());
    mergeSort(list, 0, numOfElem - 1, std::less< int >());

    print(out, forwardList.begin(), forwardList.end()) << "\n";
    print(out, queue.begin(), queue.end()) << "\n";
    print(out, list.begin(), list.end()) << "\n";
  }
}
