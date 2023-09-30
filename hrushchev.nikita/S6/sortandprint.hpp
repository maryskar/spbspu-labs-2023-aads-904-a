#ifndef SORTANDPRINT_HPP
#define SORTANDPRINT_HPP

#include <ostream>
#include <string>
#include <deque>
#include <list>
#include <forwardlist.hpp>
#include "insertion.hpp"
#include "oddeven.hpp"
#include "shaker.hpp"

namespace hrushchev
{
  template< typename Container >
  void printContainer(std::ostream& out, Container contain)
  {
    auto begin = contain.begin();
    auto end = contain.end();

    if (begin == end)
    {
      return;
    }
    out << *begin;
    begin++;

    for (; begin != end; begin++)
    {
      out << " " << *begin;
    }
    out << "\n";
  }

  template< typename T, typename Compare >
  void sortAndPrint(std::ostream& out, ForwardList< T >& forward_list, Compare comp)
  {
    auto begin_list = forward_list.begin();
    auto end_list = forward_list.end();

    std::deque< T > deque_to_oddeven(begin_list, end_list);
    std::list< T > bidir_list_to_oddeven(begin_list, end_list);
    ForwardList< T > forward_list_to_oddeven = forward_list;

    std::deque< T > deque_to_insertion(begin_list, end_list);
    std::list< T > list_to_insertion(begin_list, end_list);

    std::deque< T > deque_to_shaker(begin_list, end_list);

    oddEvenSort(deque_to_oddeven.begin(), deque_to_oddeven.end(), comp);
    oddEvenSort(bidir_list_to_oddeven.begin(), bidir_list_to_oddeven.end(), comp);
    oddEvenSort(forward_list_to_oddeven.begin(), forward_list_to_oddeven.end(), comp);

    insertionSort(deque_to_insertion.begin(), deque_to_insertion.end(), comp);
    insertionSort(list_to_insertion.begin(), list_to_insertion.end(), comp);

    shakerSort(deque_to_shaker.begin(), deque_to_shaker.end(), comp);

    printContainer(out, forward_list);

    printContainer(out, deque_to_oddeven);
    printContainer(out, bidir_list_to_oddeven);
    printContainer(out, forward_list_to_oddeven);

    printContainer(out, deque_to_insertion);
    printContainer(out, list_to_insertion);

    printContainer(out, deque_to_shaker);
  }
}

#endif
