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
        while (i < n1 && j < n2)
        {
          if (l_arr[i] <= r_arr[j])
          {
            *copy_left_it = l_arr[i++];
          }
          else
          {
            *copy_left_it = r_arr[j++];
          }
          ++copy_left_it;
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
    //
  }
}

#endif
