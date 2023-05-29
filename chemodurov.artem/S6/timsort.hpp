#ifndef S6_TIMSORT_HPP
#define S6_TIMSORT_HPP
#include <functional>

namespace chemodurov
{
  namespace detail
  {
    size_t getMinRun(size_t size)
    {
      size_t r = 0;
      while (size >= 64) {
        r |= size & 1;
        size >>= 1;
      }
      return size + r;
    }

    template< typename RandomIt, typename Compare = std::less< > >
    void insertionSort(RandomIt begin, size_t size, Compare comp)
    {
      using value_type = std::remove_reference_t< decltype(*begin) >;
      for (size_t i = 1; i < size; ++i)
      {
        value_type temp = begin[i];
        size_t j = i;
        while (j > 0 && comp(temp, begin[j - 1]))
        {
          begin[j] = begin[j - 1];
          --j;
        }
        begin[j] = temp;
      }
    }
  }

  template< typename RandomIt, typename Compare = std::less< > >
  void timSort(RandomIt begin, size_t size, Compare comp = Compare{})
  {
    if (size < 2)
    {
      return;
    }
    size_t min_run = detail::getMinRun(size);
    size_t num_of_runs = size / min_run + 1;
    auto runs_sizes = new size_t[num_of_runs];
    try
    {
      for (size_t i = 0, j = 0; i < size - 1; ++i)
      {
        runs_sizes[j] = 2;
        if (comp(begin[i + 1], begin[i++]))
        {
          while (i < size - 1 && comp(begin[i + 1], begin[i]))
          {
            ++i;
            ++(runs_sizes[j]);
          }
          if (runs_sizes[j] >= min_run)
          {
            for (size_t k = i - runs_sizes[j] + 1; k < (i + k) / 2; ++k)//??
            {
              std::swap(begin[k], begin[i - k]);
            }
          }
        }
        else
        {
          while (i < size - 1 && !comp(begin[i + 1], begin[i]))
          {
            ++i;
            ++(runs_sizes[j]);
          }
        }
        if (runs_sizes[j] < min_run)
        {
          size_t delta = min_run - runs_sizes[j];
          if (i + delta < size)
          {
            runs_sizes[j] += delta;
            i += delta;
          }
          else
          {
            runs_sizes[j] += size - i;
            i += size - i;
          }
          detail::insertionSort(begin + i - runs_sizes[j], runs_sizes[j], comp);
        }
      }
    }
    catch (...)
    {
      delete [] runs_sizes;
      throw;
    }
    delete [] runs_sizes;
  }
}
#endif
