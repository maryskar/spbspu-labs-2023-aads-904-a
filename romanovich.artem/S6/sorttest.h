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

  quickSort(forwardList.begin(), size, comp);
  quickSort(listQuick.begin(), size, comp);
  quickSort(dequeQuick.begin(), size, comp);

  shellSort(listShell.begin(), size, comp);
  shellSort(dequeShell.begin(), size, comp);

  oddEvenSort(dequeOddEven.begin(), size, comp);
}
#endif
