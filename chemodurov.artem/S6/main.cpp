#include <iostream>
#include <forward-list.hpp>
#include "merge-sort.hpp"
#include "shell-sort.hpp"

int main()
{
  chemodurov::ForwardList< int > list;
  for (size_t i = 0; i < 10000; ++i)
  {
    list.push_front(std::rand());
  }
  chemodurov::shellSort(list.begin(), 10000);
  for (auto i = list.cbegin(); i != list.cend(); ++i)
  {
    std::cout << *i << ' ';
  }
  std::cout << '\n';
  return 0;
}
