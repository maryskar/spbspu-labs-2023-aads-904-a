#include <iostream>
#include <chrono>
#include <ctime>
#include <list>
#include <forward-list.hpp>
#include <deque>
#include "shell-sort.hpp"
#include "timsort.hpp"

int main()
{
  constexpr size_t size = 10;
  std::deque< int > deque;
  for (size_t i = 0; i < size; ++i)
  {
    deque.push_front(std::rand() % 100);
  }
  auto start = std::chrono::system_clock::now();
  chemodurov::detail::insertionSort(deque.begin(), size, std::less< >{});
  auto end = std::chrono::system_clock::now();
  std::chrono::duration< double > seconds = end - start;
  for (auto i = deque.cbegin(); i != deque.cend(); ++i)
  {
    std::cout << *i << ' ';
  }
  std::cout << '\n';
  std::cout << seconds.count();
  std::cout << '\n';
  return 0;
}
