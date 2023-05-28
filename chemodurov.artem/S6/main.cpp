#include <iostream>
#include <forward-list.hpp>
#include "merge-sort.hpp"

int main()
{
  chemodurov::ForwardList< int > list;
  for (size_t i = 0; i < 20; ++i)
  {
    list.push_front(std::rand() % 100);
  }
  chemodurov::mergeSort(list.begin(), 20);
  for (auto i = list.cbegin(); i != list.cend(); ++i)
  {
    std::cout << *i << ' ';
  }
  std::cout << '\n';
  return 0;
}
