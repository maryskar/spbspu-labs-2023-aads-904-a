#ifndef SORTTEST_H
#define SORTTEST_H
#include <cstddef>
#include <vector>
#include <list>
#include <deque>
#include <forwardlist.h>
#include "randomdatagenerator.h"
namespace
{
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
  template< typename T >
  struct ConditionalComparator
  {
    explicit ConditionalComparator(std::string order):
      order(std::move(order))
    {
    }
    bool operator()(T a, T b) const
    {
      if (order == "ascending")
      {
        return std::less<>()(a, b);
      }
      else if (order == "descending")
      {
        return std::greater<>()(a, b);
      }
      else
      {
        throw std::invalid_argument("Invalid order");
      }
    }
    std::string order;
  };
}
namespace romanovich
{
  template< typename T >
  void runTest(std::vector< T > data, size_t size, const std::string &order)
  {
    printData(data.begin(), data.end());
    std::cout << '\n';
    ForwardList <T> forwardList;
    for (size_t i = 0; i < size; ++i)
    {
      forwardList.push_front(data[i]);
    }
    std::list< T > listQuick(data.begin(), data.end());
    std::list< T > listShell(data.begin(), data.end());
    std::deque< T > dequeQuick(data.begin(), data.end());
    std::deque< T > dequeShell(data.begin(), data.end());
    std::deque< T > dequeOddEven(data.begin(), data.end());
    ConditionalComparator< T > comp(order);
    oddEvenSort(forwardList.begin(), size, comp);
    oddEvenSort(listQuick.begin(), size, comp);
    oddEvenSort(dequeQuick.begin(), size, comp);
    shellSort(listShell.begin(), size, comp);
    shellSort(dequeShell.begin(), size, comp);
    quickSort(dequeOddEven.begin(), size, comp);
    printData(forwardList.begin(), forwardList.end());
    std::cout << '\n';
    printData(listQuick.begin(), listQuick.end());
    std::cout << '\n';
    printData(dequeQuick.begin(), dequeQuick.end());
    std::cout << '\n';
    printData(listShell.begin(), listShell.end());
    std::cout << '\n';
    printData(dequeShell.begin(), dequeShell.end());
    std::cout << '\n';
    printData(dequeOddEven.begin(), dequeOddEven.end());
    std::cout << '\n';
  }
}
#endif
