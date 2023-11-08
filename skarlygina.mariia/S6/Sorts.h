#ifndef SORTS_H
#define SORTS_H

#include <iterator>
#include <memory>
#include <cmath>
#include <algorithm>
#include <type_traits>
#include "BidirectionalList.h"
namespace skarlygina
{
  template < typename ForwardIt, typename Compare >
  void bubbleSort(ForwardIt first, ForwardIt last, const Compare& cmp)
  {
    for (auto i = first; i != last; ++i)
    {
      auto j = first;
      while (j != last)
      {
        auto prev = j++;
        if ((j != last) && cmp(*j, *prev))
        {
          std::iter_swap(j, prev);
        }
      }
    }
  }
  template < typename BidirIt, typename Compare >
  void qsort(BidirIt first, BidirIt last, const Compare& cmp)
  {
    if (first == last)
    {
      return;
    }
    auto left = first;
    auto right = last;
    auto pivot = left++;
    while (left != right)
    {
      if (cmp(*left, *pivot))
      {
        ++left;
      }
      else
      {
        while ((left != (--right)) && cmp(*pivot, *right));
        std::iter_swap(left, right);
      }
    }
    --left;
    std::iter_swap(first, left);
    qsort< BidirIt, Compare >(first, left, cmp);
    qsort< BidirIt, Compare >(right, last, cmp);
  }
  template < typename Iter >
  struct twoBuckets
  {
  public:
    using diff = typename std::iterator_traits< Iter >::difference_type;
    twoBuckets(Iter first, Iter second):
      diff_(std::distance(first, second))
    {}
    size_t operator()()
    {
      return 2;
    }
  private:
    diff diff_;
  };
  template < typename BidirIt, typename Compare, typename Strategy >
  void bucketSort(BidirIt first, BidirIt last, const Compare& cmp, Strategy strategy)
  {
    if (first == last)
    {
      return;
    }
    using Type = typename std::iterator_traits< BidirIt >::value_type;
    static_assert(std::is_arithmetic< Type >(), "This algorithm requires arithmetic types");
    auto minMax = std::minmax_element(first, last);
    auto min = *minMax.first;
    auto max = *minMax.second;
    if (max == min)
    {
      return;
    }
    size_t nBuckets = strategy();
    std::unique_ptr< BidirectionalList< Type >[] > buckets(new BidirectionalList< Type >[nBuckets]);
    for (auto i = first; i != last; ++i)
    {
      auto index = std::floor(nBuckets * (max - *i) / (max - min));
      if (cmp(min, max))
      {
        index = std::floor(nBuckets * (*i - min) / (max - min));
      }
      index = (index == nBuckets) ? (index - 1) : index;
      buckets[index].pushBack(*i);
    }
    for (size_t i = 0; i < nBuckets; ++i)
    {
      if (!buckets[i].isEmpty())
      {
        qsort< BiIterator< Type >, Compare >(buckets[i].begin(), buckets[i].end(), cmp);
      }
    }
    auto current = first;
    for (size_t i = 0; i < nBuckets ; ++i)
    {
      if (!buckets[i].isEmpty())
      {
        for (auto j = buckets[i].begin(); j != buckets[i].end(); ++j)
        {
          *(current++) = *j;
        }
      }
    }
  }
}

#endif


