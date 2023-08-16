#ifndef SORTTEST_H
#define SORTTEST_H
#include <cstddef>
#include <vector>
#include "../common/forwardlist.h"
#include "randomdatagenerator.h"
template< typename T >
void runTest(size_t size)
{
  std::vector< T > data = romanovich::generateRandomData(size, 1, 10);
  romanovich::ForwardList< T > forwardList;
  for (size_t i = 0; i < size; ++i)
  {
    forwardList.push_front(data[i]);
  }
  print(forwardList.begin(), forwardList.end());
}
#endif
