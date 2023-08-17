#ifndef SORTTEST_H
#define SORTTEST_H
#include <cstddef>
#include <vector>
#include <list>
#include <deque>
#include "../common/forwardlist.h"
#include "randomdatagenerator.h"
#include "sortutils.h"
void runTest(size_t size)
{
  std::vector< int > data = romanovich::generateRandomData(size, 1, 10);
  romanovich::printData(data.begin(), data.end());
  std::cout << '\n';
  romanovich::ForwardList< int > forwardList;
  for (size_t i = 0; i < size; ++i)
  {
    forwardList.push_front(data[i]);
  }
  std::list< int > listQuick(data.begin(), data.end());
  std::list< int > listShell(data.begin(), data.end());
  std::deque< int > dequeQuick(data.begin(), data.end());
  std::deque< int > dequeShell(data.begin(), data.end());
  std::deque< int > dequeOddEven(data.begin(), data.end());
  auto comp = std::less<>();
  //
  romanovich::oddEvenSort(forwardList.begin(), size, comp);
  romanovich::oddEvenSort(listQuick.begin(), size, comp);
  romanovich::oddEvenSort(dequeQuick.begin(), size, comp);
//
  romanovich::shellSort(listShell.begin(), size, comp);
  romanovich::shellSort(dequeShell.begin(), size, comp);
//
  romanovich::quickSort(dequeOddEven.begin(), size, comp);

  romanovich::printData(forwardList.begin(), forwardList.end());
  std::cout << '\n';
  romanovich::printData(listQuick.begin(), listQuick.end());
  std::cout << '\n';
  romanovich::printData(dequeQuick.begin(), dequeQuick.end());
  std::cout << '\n';
  romanovich::printData(listShell.begin(), listShell.end());
  std::cout << '\n';
  romanovich::printData(dequeShell.begin(), dequeShell.end());
  std::cout << '\n';
  romanovich::printData(dequeOddEven.begin(), dequeOddEven.end());
  std::cout << '\n';
}
#endif
