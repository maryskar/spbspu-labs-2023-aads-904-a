#ifndef SORTUTILS_H
#define SORTUTILS_H
#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>
#include "quicksort.h"
#include "shellsort.h"
#include "oddevensort.h"
namespace romanovich
{
  template< typename T >
  void sortData(std::vector< T > &data, const std::string &sortOrder)
  {
    if (sortOrder == "ascending")
    {
      oddEvenSort(data.begin(), data.size(), std::less<>());
    }
    else if (sortOrder == "descending")
    {
      quickSort(data.begin(), data.size(), std::greater<>());
    }
    else
    {
      throw std::invalid_argument("Invalid sort order.");
    }
  }
  template< typename InputIt >
  void printData(InputIt begin, InputIt end)
  {
    for (auto it = begin; it != end; ++it)
    {
      if (it != begin)
      {
        std::cout << ' ';
      }
      std::cout << *it;
    }
  }
}
#endif
