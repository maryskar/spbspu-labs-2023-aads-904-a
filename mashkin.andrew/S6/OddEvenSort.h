#ifndef MASHKIN_ANDREW_ODDEVENSORT_H
#define MASHKIN_ANDREW_ODDEVENSORT_H
#include <cstddef>
#include <iterator>

namespace mashkin
{
  template< class Iter >
  void swapValOfIter(Iter& first, Iter& second)
  {
    auto var = *first;
    *first = *second;
    *second = var;
  }

  template< class DataStruct, class Comporator >
  void oddEvenSort(DataStruct& dataStruct, Comporator comp)
  {
    bool isSorted = false;

    while (!isSorted)
    {
      isSorted = true;

      auto first = dataStruct.begin();
      auto second = ++dataStruct.begin();
      auto beforeEnd = --dataStruct.end();

      for (;first != beforeEnd && first != dataStruct.end(); std::advance(first, 2), std::advance(second, 2))
      {
        if (!comp(*first, *second))
        {
          swapValOfIter(first, second);
          isSorted = false;
        }
      }

      first = ++dataStruct.begin();
      second = ++++dataStruct.begin();

      for (;first != beforeEnd && first != dataStruct.end(); std::advance(first, 2), std::advance(second, 2))
      {
        if (!comp(*first, *second))
        {
          swapValOfIter(first, second);
          isSorted = false;
        }
      }
    }
  }
}
#endif
