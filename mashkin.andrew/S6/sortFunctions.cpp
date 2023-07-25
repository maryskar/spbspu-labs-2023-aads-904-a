#include "sortFunctions.h"
#include <iostream>
#include <forwardList.h>
#include <deque>
#include <list>
#include <random>
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

  template< class Type, class Comporator >
  void sortAndPrint(std::ostream& out, size_t numOfElem, ForwardList< Type > forwardList, Comporator comp)
  {
    print(out, forwardList.begin(), forwardList.end()) << "\n";

    std::deque< Type > queueForMerge(forwardList.begin(), forwardList.end());
    std::list< Type > listForMerge(forwardList.begin(), forwardList.end());
    std::deque< Type > queueForOddEven(forwardList.begin(), forwardList.end());
    std::list< Type > listForOddEven(forwardList.begin(), forwardList.end());
    std::deque< Type > queueForQSort(forwardList.begin(), forwardList.end());

    mergeSort(forwardList, 0, numOfElem - 1, comp);
    mergeSort(queueForMerge, 0, numOfElem - 1, comp);
    mergeSort(listForMerge, 0, numOfElem - 1, comp);
    oddEvenSort(listForOddEven, comp);
    oddEvenSort(queueForOddEven, comp);
    quickSort< decltype(queueForQSort), Type, Comporator >( queueForQSort, 0, numOfElem - 1, comp);

    print(out, forwardList.begin(), forwardList.end()) << "\n";
    print(out, queueForMerge.begin(), queueForMerge.end()) << "\n";
    print(out, listForMerge.begin(), listForMerge.end()) << "\n";
    print(out, listForOddEven.begin(), listForOddEven.end()) << "\n";
    print(out, queueForOddEven.begin(), queueForOddEven.end()) << "\n";
    print(out, queueForQSort.begin(), queueForQSort.end()) << "\n";
  }

  void getRandForwardListOfInts(ForwardList< int >& forwardList, size_t numOfElem)
  {
    std::default_random_engine generator;
    std::uniform_int_distribution< > distribution;
    for (size_t i = 0; i < numOfElem; i++)
    {
      forwardList.push_front(distribution(generator));
    }
  }

  void getRandForwardListOfFloats(ForwardList< double >& forwardList, size_t numOfElem)
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
    getRandForwardListOfInts(forwardList, numOfElem);
    sortAndPrint< int, decltype(std::less< int >()) >(out, numOfElem, forwardList, std::less< int >());
  }

  void ascendFloat(std::ostream& out, size_t numOfElem)
  {
    ForwardList< double > forwardList;
    getRandForwardListOfFloats(forwardList, numOfElem);
    sortAndPrint< double, decltype(std::less< double >()) >(out, numOfElem, forwardList, std::less< double >());
  }

  void descendInt(std::ostream& out, size_t numOfElem)
  {
    ForwardList< int > forwardList;
    getRandForwardListOfInts(forwardList, numOfElem);
    sortAndPrint< int, decltype(std::greater< int >()) >(out, numOfElem, forwardList, std::greater< int >());
  }

  void descendFloat(std::ostream& out, size_t numOfElem)
  {
    ForwardList< double > forwardList;
    getRandForwardListOfFloats(forwardList, numOfElem);
    sortAndPrint< double, decltype(std::greater< double >()) >(out, numOfElem, forwardList, std::greater< double >());
  }
}
