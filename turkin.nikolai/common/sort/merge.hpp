#ifndef MERGE_HPP
#define MERGE_HPP

#include <cstddef>
#include <iterator>

namespace details
{
  template< typename ForwardIt, typename UnaryPred >
  void merge(ForwardIt first, size_t lhs, size_t mid, size_t rhs, UnaryPred p)
  {
    std::size_t n1 = mid - lhs + 1;
    std::size_t n2 = rhs - mid;
    using value_t = std::remove_reference_t< decltype(*first) >;
    value_t * l_arr = new value_t[n1];
    value_t * r_arr = nullptr;
    try
    {
      r_arr = new value_t[n2];
    }
    catch (...)
    {
      delete[] l_arr;
      throw;
    }
    try
    {
      auto left_it = first;
      for (std::size_t i = 0; i < lhs; i++, left_it++);
      auto copy_left_it = left_it;
      for (std::size_t i = 0; i < n1; i++)
      {
        l_arr[i] = *left_it++;
      }
      for (std::size_t j = 0; j < n2; j++)
      {
        r_arr[j] = *left_it++;
      }
      {
        std::size_t i = 0;
        std::size_t j = 0;
        for (; i < n1 && j < n2; ++copy_left_it)
        {
          if (!p(r_arr[j], l_arr[i]))
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
      delete[] l_arr;
      delete[] r_arr;
      throw;
    }
    delete[] l_arr;
    delete[] r_arr;
  }
}

namespace turkin
{
  template< typename ForwardIt, typename UnaryPred >
  void merge_sort(ForwardIt first, std::size_t size, UnaryPred p)
  {
    for (std::size_t cur = 1; cur <= size - 1; cur = 2 * cur)
    {
      for (std::size_t lhs = 0; lhs < size - 1; lhs += 2 * cur)
      {
        std::size_t mid = std::min(lhs + cur - 1, size - 1);
        std::size_t rhs = std::min(lhs + 2 * cur - 1, size - 1);
        details::merge(first, lhs, mid, rhs, p);
      }
    }
  }
}

#endif
