#ifndef S6_TIMSORT_HPP
#define S6_TIMSORT_HPP
#include "merge-sort.hpp"

namespace chemodurov
{
  namespace detail
  {
    size_t getMinRun(size_t size)
    {
      size_t r = 0;
      while (size >= 64)
      {
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

    template< typename RandomIt, typename Compare = std::less< > >
    std::pair< size_t, size_t > * splitIntoSortedArrays(RandomIt begin, size_t size, Compare comp, size_t & num_of_run)
    {
      size_t min_run = detail::getMinRun(size);
      num_of_run = size / min_run + 1;
      auto runs_inds_sizes = new std::pair< size_t, size_t >[num_of_run];
      try
      {
        for (size_t i = 0, j = 0; i < size - 1; ++i, ++j)
        {
          runs_inds_sizes[j].second = 2;
          if (comp(begin[i + 1], begin[i]))
          {
            ++i;
            while (i < size - 1 && comp(begin[i + 1], begin[i]))
            {
              ++i;
              ++(runs_inds_sizes[j].second);
            }
            if (runs_inds_sizes[j].second >= min_run)
            {
              for (size_t k = i - runs_inds_sizes[j].second + 1, l = i; k < l; ++k, --l)
              {
                std::swap(begin[k], begin[l]);
              }
            }
          }
          else
          {
            ++i;
            while (i < size - 1 && !comp(begin[i + 1], begin[i]))
            {
              ++i;
              ++(runs_inds_sizes[j].second);
            }
          }
          if (runs_inds_sizes[j].second < min_run)
          {
            size_t delta = min_run - runs_inds_sizes[j].second;
            if (i + delta < size)
            {
              runs_inds_sizes[j].second += delta;
              i += delta;
            }
            else
            {
              runs_inds_sizes[j].second += size - i - 1;
              i += size - i - 1;
            }
            detail::insertionSort(begin + i + 1 - runs_inds_sizes[j].second, runs_inds_sizes[j].second, comp);
          }
          num_of_run = j + 1;
        }
        runs_inds_sizes[0].first = 0;
        for (size_t i = 1; i < num_of_run; ++i)
        {
          runs_inds_sizes[i].first = runs_inds_sizes[i - 1].first + runs_inds_sizes[i - 1].second;
        }
      }
      catch (...)
      {
        delete [] runs_inds_sizes;
        throw;
      }
      return runs_inds_sizes;
    }
  }

  template< typename RandomIt, typename Compare = std::less< > >
  void timSort(RandomIt begin, size_t size, Compare comp = Compare{})
  {
    if (size < 2)
    {
      return;
    }
    size_t num_of_runs = 0;
    std::pair< size_t, size_t > * runs_sizes = detail::splitIntoSortedArrays(begin, size, comp, num_of_runs);
    try
    {
      if (num_of_runs == 1)
      {
        delete [] runs_sizes;
        return;
      }
      else
      {
        for (size_t i = 1; i < num_of_runs; ++i)
        {
          using namespace detail;
          size_t ind_i = runs_sizes[i].first;
          merge(begin, runs_sizes[i - 1].first, ind_i - 1, ind_i + runs_sizes[i].second - 1, comp);
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
