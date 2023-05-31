#include <iostream>
#include <list>
#include <deque>
#include <algorithm>
#include <random>
#include <cstring>
#include <map.hpp>
#include <forward-list.hpp>
#include "shell-sort.hpp"
#include "timsort.hpp"

int main(int argc, char ** argv)
{
  if (argc != 4)
  {
    std::cerr << "Incorrect amount of CML args\n";
    return 1;
  }
  if (std::strcmp(argv[1], "ascending") != 0 && std::strcmp(argv[1], "descending") != 0)
  {
    std::cerr << "Incorrect first argument\n";
    return 1;
  }
  size_t num_of_elem = 0;
  try
  {
    num_of_elem = std::strtoull(argv[3], nullptr, 10);
  }
  catch (...)
  {
    std::cerr << "Incorrect third argument\n";
    return 1;
  }
  std::default_random_engine generator;
  if (!std::strcmp(argv[2], "ints"))
  {
    std::uniform_int_distribution< > distrib;
    chemodurov::ForwardList< int > f_list;
    for (size_t i = 0; i < num_of_elem; ++i)
    {
      f_list.push_front(distrib(generator));
    }
    std::list< int > l_for_merge(f_list.begin(), f_list.end());
    std::list< int > l_for_shell(f_list.begin(), f_list.end());
    std::deque< int > d_for_merge(f_list.begin(), f_list.end());
    std::deque< int > d_for_shell(f_list.begin(), f_list.end());
    std::deque< int > d_for_tim(f_list.begin(), f_list.end());
    if (!std::strcmp(argv[1], "ascending"))
    {
      chemodurov::mergeSort(f_list.begin(), num_of_elem);
      chemodurov::mergeSort(l_for_merge.begin(), num_of_elem);
      chemodurov::shellSort(l_for_shell.begin(), num_of_elem);
      chemodurov::mergeSort(d_for_merge.begin(), num_of_elem);
      chemodurov::shellSort(d_for_shell.begin(), num_of_elem);
      chemodurov::timSort(d_for_tim.begin(), num_of_elem);
    }
    else
    {
      chemodurov::mergeSort(f_list.begin(), num_of_elem, std::greater< >{});
      chemodurov::mergeSort(l_for_merge.begin(), num_of_elem, std::greater< >{});
      chemodurov::shellSort(l_for_shell.begin(), num_of_elem, std::greater< >{});
      chemodurov::mergeSort(d_for_merge.begin(), num_of_elem, std::greater< >{});
      chemodurov::shellSort(d_for_shell.begin(), num_of_elem, std::greater< >{});
      chemodurov::timSort(d_for_tim.begin(), num_of_elem, std::greater< >{});
    }
  }
  return 0;
}
