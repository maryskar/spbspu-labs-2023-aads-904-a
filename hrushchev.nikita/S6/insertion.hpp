#ifndef INSERTION_HPP
#define INSERTION_HPP

#include <functional>

namespace hrushchev
{
  template< typename BidirectionalIt, typename Compare = std::less< > >
  void insertionSort(BidirectionalIt begin, BidirectionalIt end, Compare comp = Compare{})
  {
    for (auto it = std::next(begin); it != end; ++it)
    {
      auto current = *it;
      auto j = it;
      while (j != begin && comp(current, *(std::prev(j))))
      {
        *j = *(std::prev(j));
        --j;
      }
      *j = current;
    }
  }
}

#endif
