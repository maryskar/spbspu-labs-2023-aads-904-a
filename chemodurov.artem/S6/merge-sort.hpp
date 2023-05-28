#ifndef S6_MERGE_SORT_HPP
#define S6_MERGE_SORT_HPP
#include <functional>

namespace chemodurov
{
  template< typename ForwardIt, typename Compare = std::less< > >
  void merge(ForwardIt begin, size_t fst_l, size_t fst_r, size_t snd_r, Compare comp)
  {
    size_t n1 = fst_r - fst_l + 1;
    size_t n2 = snd_r - fst_r;
    using value_type = std::remove_reference_t< decltype(*begin) >;
    value_type * l_arr = new value_type[n1];
    value_type * r_arr = nullptr;
    try
    {
      r_arr = new value_type[n2];
    }
    catch (...)
    {
      delete [] l_arr;
      throw;
    }

    try
    {
      auto left_it = std::next(begin, fst_l);
      auto copy_left_it = left_it;
      for (size_t i = 0; i < n1; i++)
      {
        l_arr[i] = *left_it++;
      }
      for (size_t j = 0; j < n2; j++)
      {
        r_arr[j] = *left_it++;
      }
      {
        size_t i = 0;
        size_t j = 0;
        for (; i < n1 && j < n2; ++copy_left_it)
        {
          if (!comp(r_arr[j], l_arr[i]))
          {
            *copy_left_it = l_arr[i++];
          }
          else
          {
            *copy_left_it = r_arr[j++];
          }
        }

        while (i < n1)
        {
          *copy_left_it++ = l_arr[i++];
        }
        while (j < n2)
        {
          *copy_left_it++ = r_arr[j++];
        }
      }
    }
    catch (...)
    {
      delete [] l_arr;
      delete [] r_arr;
      throw;
    }
    delete [] l_arr;
    delete [] r_arr;
  }

  template< typename ForwardIt, typename Compare = std::less< > >
  void mergeSort(ForwardIt begin, size_t size, Compare comp = Compare{})
  {
    for (size_t curr_size = 1; curr_size <= size - 1; curr_size = 2 * curr_size)
    {
      for (size_t left_start = 0; left_start < size - 1; left_start += 2 * curr_size)
      {
        size_t mid = std::min(left_start + curr_size - 1, size - 1);
        size_t right_end = std::min(left_start + 2 * curr_size - 1, size - 1);
        merge(begin, left_start, mid, right_end, comp);
      }
    }
  }
}

#endif
