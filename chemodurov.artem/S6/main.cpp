#include <iostream>
#include <chrono>
#include <ctime>
#include <forward-list.hpp>
#include <list>
#include "merge-sort.hpp"
#include "shell-sort.hpp"

int main()
{
  constexpr size_t size = 1000;
  std::list< int > list;
  for (size_t i = 0; i < size; ++i)
  {
    list.push_front(std::rand());
  }
  auto start = std::chrono::system_clock::now();
  chemodurov::shellSort(list.begin(), size);
  auto end = std::chrono::system_clock::now();
  std::chrono::duration< double > seconds = end - start;
  for (auto i = list.cbegin(); i != list.cend(); ++i)
  {
    std::cout << *i << ' ';
  }
  std::cout << '\n';
  std::cout << seconds.count();
  std::cout << '\n';
  return 0;
}
