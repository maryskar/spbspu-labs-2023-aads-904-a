#ifndef FA_SORT_H
#define FA_SORT_H
#include <iterator>

namespace tarasenko
{
  namespace details
  {
    template< typename ForwardIt, typename UnaryPred >
    ForwardIt partition(ForwardIt first, ForwardIt last, UnaryPred p)
    {
      while (first != last && p(*first))
      {
        ++first;
      }
      if (first == last)
      {
        return first;
      }
      for (auto i = std::next(first); i != last; ++i)
        if (p(*i))
        {
          std::swap(*i, *first);
          ++first;
        }
      return first;
    }
  }

  template< typename ForwardIt, typename Compare >
  void quickSort(ForwardIt begin, ForwardIt last, Compare comp)
  {
    if (std::distance(begin, last) < 2)
    {
      return;
    }
    auto pivot = *std::next(begin, std::distance(begin, last) / 2);
    auto l = details::partition(begin, last, [pivot, comp](const auto& i)
    {
      return comp(i, pivot);
    });
    auto b = details::partition(begin, last, [pivot, comp](const auto& i)
    {
      return !comp(pivot, i);
    });
    quickSort(begin, l, comp);
    quickSort(b, last, comp);
  }
}

#endif
