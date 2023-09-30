#ifndef ODDEVEN_HPP
#define ODDEVEN_HPP

#include <functional>

namespace hrushchev
{
template< typename ForwardIt >
  size_t getDistanse(const ForwardIt begin, const ForwardIt end)
  {
    size_t res = 0;
    auto copy_begin = begin;
    auto copy_end = end;
    while (copy_begin != copy_end)
    {
      res++;
      copy_begin++;
    }
    return res;
  }

  template< typename ForwardIt, typename Compare = std::less< > >
  void oddEvenSort(ForwardIt begin, ForwardIt end, Compare comp = Compare{})
  {
    size_t size = getDistanse(begin, end);
    bool sorted = false;
    while (!sorted)
    {
      sorted = true;
      for (size_t i = 1; i < size - 1; i += 2)
      {
        auto current = begin;
        for (size_t j = 0; j != i; j++)
        {
          ++current;
        }
        auto next = current;
        next++;
        if (comp(*next, *current))
        {
          std::swap(*current, *next);
          sorted = false;
        }
      }
      for (size_t i = 0; i < size - 1; i += 2)
      {
        auto current = begin;
        for (size_t j = 0; j != i; j++)
        {
          ++current;
        }
        auto next = current;
        next++;
        if (comp(*next, *current))
        {
          std::swap(*current, *next);
          sorted = false;
        }
      }
    }
  }
}
#endif
