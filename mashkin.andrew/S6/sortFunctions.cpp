#include "sortFunctions.h"
#include <deque>
#include <iomanip>
#include <iostream>
#include <list>
#include <random>
#include <ForwardList/forwardList.h>
#include "SortFunctions/OddEvenSort.h"
#include "SortFunctions/mergeSort.h"
#include "SortFunctions/quickSort.h"

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

  template< class Type, class Comporator >
  void sortAndPrint(std::ostream& out, size_t numOfElem, ForwardList< Type > forwardList, Comporator comp)
  {
    print(out, forwardList.begin(), forwardList.end()) << "\n";

    std::deque< Type > queueForMerge(forwardList.begin(), forwardList.end());
    std::list< Type > listForMerge(forwardList.begin(), forwardList.end());
    std::deque< Type > queueForOddEven(forwardList.begin(), forwardList.end());
    std::list< Type > listForOddEven(forwardList.begin(), forwardList.end());
    std::deque< Type > queueForQSort(forwardList.begin(), forwardList.end());

    mergeSort(forwardList.begin(), std::distance(forwardList.begin(), forwardList.end()), comp);
    mergeSort(queueForMerge.begin(), queueForMerge.size(), comp);
    mergeSort(listForMerge.begin(), listForMerge.size(), comp);
    oddEvenSort(listForOddEven.begin(), listForOddEven.end(), comp);
    oddEvenSort(queueForOddEven.begin(), queueForOddEven.end(), comp);
    quickSort(queueForQSort.begin(), queueForQSort.end(), comp);

    print(out, forwardList.begin(), forwardList.end()) << "\n";
    print(out, queueForMerge.begin(), queueForMerge.end()) << "\n";
    print(out, listForMerge.begin(), listForMerge.end()) << "\n";
    print(out, listForOddEven.begin(), listForOddEven.end()) << "\n";
    print(out, queueForOddEven.begin(), queueForOddEven.end()) << "\n";
    print(out, queueForQSort.begin(), queueForQSort.end()) << "\n";
  }

  template< class Type >
  void getRandVelueForForwardList(ForwardList< Type >& forwardList, size_t numOfElem)
  {
    std::default_random_engine generator;
    std::uniform_int_distribution< > distribution;
    for (size_t i = 0; i < numOfElem; i++)
    {
      forwardList.push_front(distribution(generator));
    }
  }

  void ascendInt(std::ostream& out, size_t numOfElem)
  {
    ForwardList< int > forwardList;
    getRandVelueForForwardList(forwardList, numOfElem);
    sortAndPrint< int, decltype(std::less< int >()) >(out, numOfElem, forwardList, std::less< int >());
  }

  void ascendFloat(std::ostream& out, size_t numOfElem)
  {
    ForwardList< double > forwardList;
    getRandVelueForForwardList(forwardList, numOfElem);
    out << std::fixed << std::setprecision(1);
    sortAndPrint< double, decltype(std::less< double >()) >(out, numOfElem, forwardList, std::less< double >());
  }

  void descendInt(std::ostream& out, size_t numOfElem)
  {
    ForwardList< int > forwardList;
    getRandVelueForForwardList(forwardList, numOfElem);
    sortAndPrint< int, decltype(std::greater< int >()) >(out, numOfElem, forwardList, std::greater< int >());
  }

  void descendFloat(std::ostream& out, size_t numOfElem)
  {
    ForwardList< double > forwardList;
    getRandVelueForForwardList(forwardList, numOfElem);
    out << std::fixed << std::setprecision(1);
    sortAndPrint< double, decltype(std::greater< double >()) >(out, numOfElem, forwardList, std::greater< double >());
  }
}
