#ifndef S6_SORT_AND_PRINT_RANDOM_VALUE_HPP
#define S6_SORT_AND_PRINT_RANDOM_VALUE_HPP
#include <iostream>
#include <random>
#include <list>
#include <deque>
#include <cstring>
#include <forward-list.hpp>
#include <sort/timsort.hpp>
#include <sort/shell-sort.hpp>

namespace chemodurov
{
  template< typename InputIt >
  void print(InputIt begin, InputIt end, std::ostream & out)
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
    print(f_list.begin(), f_list.end(), out);
    out << '\n';
    std::list< Value > l_for_merge(f_list.begin(), f_list.end());
    std::list< Value > l_for_shell(f_list.begin(), f_list.end());
    std::deque< Value > d_for_merge(f_list.begin(), f_list.end());
    std::deque< Value > d_for_shell(f_list.begin(), f_list.end());
    std::deque< Value > d_for_tim(f_list.begin(), f_list.end());

    mergeSort(f_list.begin(), num_of_elem, comp);
    mergeSort(l_for_merge.begin(), num_of_elem, comp);
    shellSort(l_for_shell.begin(), num_of_elem, comp);
    mergeSort(d_for_merge.begin(), num_of_elem, comp);
    shellSort(d_for_shell.begin(), num_of_elem, comp);
    timSort(d_for_tim.begin(), num_of_elem, comp);

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

  void sortAscendingInts(std::ostream & out, size_t num_of_elem)
  {
    using gen_t = std::default_random_engine;
    using distr_t = std::uniform_int_distribution< >;
    sortAndPrintRandomValue< int, std::less< >, distr_t, gen_t >(std::less< >{}, distr_t{}, gen_t{}, out, num_of_elem);
  }

  void sortAscendingFloats(std::ostream & out, size_t num_of_elem)
  {
    using gen_t = std::default_random_engine;
    using distr_t = std::uniform_real_distribution< >;
    sortAndPrintRandomValue< double, std::less< >, distr_t, gen_t >(std::less< >{}, distr_t{}, gen_t{}, out, num_of_elem);
  }

  void sortDescendingInts(std::ostream & out, size_t num_of_elem)
  {
    using gen_t = std::default_random_engine;
    using distr_t = std::uniform_int_distribution< >;
    sortAndPrintRandomValue< int, std::greater< >, distr_t, gen_t >(std::greater< >{}, distr_t{}, gen_t{}, out, num_of_elem);
  }

  void sortDescendingFloats(std::ostream & out, size_t num_of_elem)
  {
    using gen_t = std::default_random_engine;
    using distr_t = std::uniform_real_distribution< >;
    sortAndPrintRandomValue< double, std::greater< >, distr_t, gen_t >(std::greater< >{}, distr_t{}, gen_t{}, out, num_of_elem);
  }
}

#endif
