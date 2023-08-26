#ifndef ODDEVEN_HPP
#define ODDEVEN_HPP

#include <functional>

template<typename ForwardIt, typename Compare = std::less<>>
void oddEvenSort(ForwardIt begin, ForwardIt end, Compare comp = Compare{})
{
  bool sorted = false;
  while (!sorted)
  {
    sorted = true;
    for (auto it = begin + 1; it < end - 1; it += 2)
    {
      if (comp(*(it + 1), *it))
      {
        std::swap(*it, *(it + 1));
        sorted = false;
      }
    }
    for (auto it = begin; it < end - 1; it += 2)
    {
      if (comp(*(it + 1), *it))
      {
        std::swap(*it, *(it + 1));
        sorted = false;
      }
    }
  }
}

#endif
