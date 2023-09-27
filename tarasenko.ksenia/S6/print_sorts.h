#ifndef S6_PRINT_SORTS_H
#define S6_PRINT_SORTS_H

#include <iostream>
#include <deque>
#include <list>
#include <forward_list.h>
#include "shaker.h"
#include "qsort.h"
#include "bucket.h"
#include "print.h"

namespace tarasenko
{
  template< typename OutputIt, typename Compare >
  std::ostream& printSorts(OutputIt first, OutputIt last, Compare comp, std::ostream& out)
  {
    tarasenko::print(first, last, out) << "\n";

    using value_t = typename OutputIt::value_type;
    std::list< value_t > bidir_list_1(first, last);
    std::deque< value_t > deque_1(first, last);

    tarasenko::shakerSort(deque_1.begin(), deque_1.end(), comp);
    tarasenko::print(deque_1.begin(), deque_1.end(), out) << "\n";

    std::list< value_t > bidir_list_2(first, last);
    std::deque< value_t > deque_2(first, last);
    tarasenko::quickSort(bidir_list_2.begin(), bidir_list_2.end(), comp);
    tarasenko::print(bidir_list_2.begin(), bidir_list_2.end(), out) << "\n";
    tarasenko::quickSort(deque_2.begin(), deque_2.end(), comp);
    tarasenko::print(deque_2.begin(), deque_2.end(), out) << "\n";

    tarasenko::ForwardList< value_t > forw_list_3(first, last);
    std::list< value_t > bidir_list_3(first, last);
    std::deque< value_t > deque_3(first, last);
    tarasenko::bucketSort(forw_list_3.begin(), forw_list_3.end(), comp);
    tarasenko::print(forw_list_3.begin(), forw_list_3.end(), out) << "\n";
    tarasenko::bucketSort(bidir_list_3.begin(), bidir_list_3.end(), comp);
    tarasenko::print(bidir_list_3.begin(), bidir_list_3.end(), out) << "\n";
    tarasenko::bucketSort(deque_3.begin(), deque_3.end(), comp);
    tarasenko::print(deque_3.begin(), deque_3.end(), out) << "\n";

    return out;
  }
}
#endif
