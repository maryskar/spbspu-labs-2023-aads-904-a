#ifndef S6_BUCKET_H
#define S6_BUCKET_H

#include <cmath>
#include "qsort.h"

namespace tarasenko
{
  template< typename ForwardIt, typename Compare >
  void bucketSort(ForwardIt begin, ForwardIt last, Compare comp)
  {
    using value_t = typename ForwardIt::value_type;
    size_t num_value = 0;
    value_t min_val = *begin;
    value_t max_val = *begin;
    for (auto i = begin; i != last; i++)
    {
      num_value++;
      if (*i > max_val)
      {
        max_val = *i;
      }
      if (*i < min_val)
      {
        min_val = *i;
      }
    }
    double num_buckets = std::round(1 + 3.322 * std::log10(num_value));
    auto bucketSize = (max_val - min_val + 1) / num_buckets;
    auto buckets = new ForwardList< value_t >[static_cast< size_t >(num_buckets)];

    try
    {
      for (auto it = begin; it != last; ++it)
      {
        auto ind = static_cast< size_t >(std::floor((*it - min_val) / bucketSize));
        buckets[ind].pushBack(*it);
      }
    }
    catch (const std::exception& e)
    {
      delete [] buckets;
      throw;
    }

    for (size_t i = 0; i < num_buckets; i++)
    {
      quickSort(buckets[i].begin(), buckets[i].end(), comp);
    }

    for (size_t i = 0; i < num_buckets; i++)
    {
      for (auto it = buckets[i].begin(); it != buckets[i].end(); it++)
      {
        *begin = *it;
        begin++;
      }
    }
    delete [] buckets;
  }
}
#endif
