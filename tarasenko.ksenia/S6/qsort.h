#ifndef S6_QSORT_H
#define S6_QSORT_H
#include <iterator>
#include <functional>

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
      {
        if (p(*i))
        {
          std::swap(*i, *first);
          ++first;
        }
      }
      return first;
    }
  }

  template< typename ForwardIt, typename Compare >
  void quickSort(ForwardIt begin, ForwardIt last, Compare comp)
  {
    auto dist = std::distance(begin, last);
    if (dist < 2)
    {
      return;
    }
    using namespace std::placeholders;
    auto pivot = *std::next(begin, dist / 2);
    auto comp1 = std::bind(comp, _1, pivot);
    auto l = details::partition(begin, last, comp1);
    auto comp2 = std::bind(comp, pivot, _1);
    auto not_comp2 = std::bind(std::logical_not<>{}, comp2);
    auto b = details::partition(begin, last, not_comp2);
    quickSort(begin, l, comp);
    quickSort(b, last, comp);
  }
}
#endif
