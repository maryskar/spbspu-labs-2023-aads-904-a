#include <iostream>
#include <deque>
#include <list>
#include <algorithm>
#include <functional>
#include <random>
#include "insertion.hpp"
#include "oddeven.hpp"
#include "shaker.hpp"
#include "filllist.hpp"
#include <forwardlist.hpp>

int main()
{
  hrushchev::ForwardList < int > my_list;
  hrushchev::fillRandomInts(my_list, 10);
  std::deque< int > data(my_list.begin(), my_list.end());
  std::cout << "Original data: ";
  for (const auto& num : data)
  {
      std::cout << num << " ";
  }
  std::cout << "\n";

  auto insertion_data = data;
  insertionSort(insertion_data.begin(), insertion_data.end());
  std::cout << "Insertion Sort: ";
  for (const auto& num : insertion_data)
  {
      std::cout << num << " ";
  }
  std::cout << "\n";

  auto odd_even_data = data;
  oddEvenSort(odd_even_data.begin(), odd_even_data.end());
  std::cout << "OddEven Sort: ";
  for (const auto& num : odd_even_data)
  {
      std::cout << num << " ";
  }
  std::cout << "\n";

  auto shaker_data = data;
  shakerSort(shaker_data.begin(), shaker_data.end());
  std::cout << "Shaker Sort: ";
  for (const auto& num : shaker_data)
  {
      std::cout << num << " ";
  }
  std::cout << "\n";

  auto odd_even_list = my_list;
  oddEvenSort(odd_even_list.begin(), odd_even_list.end(), std::greater< >());
  std::cout << "OddEven Sort: ";
  for (const auto& num : odd_even_list)
  {
      std::cout << num << " ";
  }
  std::cout << "\n";
}
