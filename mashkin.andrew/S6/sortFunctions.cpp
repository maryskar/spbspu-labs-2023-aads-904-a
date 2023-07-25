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
  void ascendInt(std::ostream& out, size_t numOfElem)
  {
    ForwardList< int > forwardList;
    for (size_t i = 0; i < numOfElem; i++)
    {
      forwardList.push_front(i);
      //forwardList.push_front(std::rand());
    }
    std::deque< int > queue(forwardList.begin(), forwardList.end());
    std::list< int > list(forwardList.begin(), forwardList.end());

    for (auto i = forwardList.begin(); i != forwardList.end(); i++)
    {
      std::cout << *i << " ";
    }
    out << "\n";
    mergeSort(forwardList, 0, numOfElem - 1, std::less< int >());
    mergeSort(queue, 0, numOfElem - 1, std::less< int >());
    mergeSort(list, 0, numOfElem - 1, std::less< int >());
    for (auto i = forwardList.begin(); i != forwardList.end(); i++)
    {
      std::cout << *i << " ";
    }
  }
}
