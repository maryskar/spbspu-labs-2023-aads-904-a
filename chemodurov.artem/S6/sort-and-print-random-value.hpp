#ifndef S6_SORT_AND_PRINT_RANDOM_VALUE_HPP
#define S6_SORT_AND_PRINT_RANDOM_VALUE_HPP
#include <iostream>
#include <random>
#include <list>
#include <deque>
#include <cstring>
#include <forward-list.hpp>
#include "timsort.hpp"
#include "shell-sort.hpp"

namespace chemodurov
{
  template< typename OutputIt >
  void print(OutputIt begin, OutputIt end, std::ostream & out)
  {
    for (auto i = begin; i != end; ++i)
    {
      if (i != begin)
      {
        out << ' ';
      }
      out << *i;
    }
  }

  template< typename Value, typename Compare, typename Distribution, typename Generator >
  void sortAndPrintRandomValue(Compare comp, Distribution distrib, Generator gen, std::ostream & out, size_t num_of_elem)
  {
    ForwardList< Value > f_list;
    for (size_t i = 0; i < num_of_elem; ++i)
    {
      f_list.push_front(distrib(gen));
    }
    std::list< Value > l_for_merge(f_list.begin(), f_list.end());
    std::list< Value > l_for_shell(f_list.begin(), f_list.end());
    std::deque< Value > d_for_merge(f_list.begin(), f_list.end());
    std::deque< Value > d_for_shell(f_list.begin(), f_list.end());
    std::deque< Value > d_for_tim(f_list.begin(), f_list.end());

    using namespace std::placeholders;
    auto merge = std::bind(mergeSort, _1, num_of_elem, comp);
    auto shell = std::bind(shellSort, _1, num_of_elem, comp);
    auto tim = std::bind(timSort, _1, num_of_elem, comp);

    merge(f_list.begin());
    merge(l_for_merge.begin());
    shell(l_for_shell.begin());
    merge(d_for_merge.begin());
    shell(d_for_shell.begin());
    tim(d_for_tim.begin());

    print(f_list.begin(), f_list.end(), out);
    out << '\n';
    print(l_for_merge.begin(), l_for_merge.end(), out);
    out << '\n';
    print(l_for_shell.begin(), l_for_shell.end(), out);
    out << '\n';
    print(d_for_merge.begin(), d_for_merge.end(), out);
    out << '\n';
    print(d_for_shell.begin(), d_for_shell.end(), out);
    out << '\n';
    print(d_for_tim.begin(), d_for_tim.end(), out);
    out << '\n';
  }
}

#endif
