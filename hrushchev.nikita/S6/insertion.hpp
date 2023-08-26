#ifndef INSERTION_HPP
#define INSERTION_HPP

#include <functional>

template<typename RandomIt, typename Compare = std::less<>>
void insertionSort(RandomIt begin, RandomIt end, Compare comp = Compare{})
{
  for (auto it = begin + 1; it != end; ++it)
  {
    auto current = *it;
    auto j = it;
    while (j != begin && comp(current, *(j - 1)))
    {
      *j = *(j - 1);
      --j;
    }
    *j = current;
  }
}

#endif
