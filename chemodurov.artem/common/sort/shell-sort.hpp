#ifndef S6_SHELL_SORT_HPP
#define S6_SHELL_SORT_HPP
#include <functional>
#include <map.hpp>

namespace chemodurov
{
  template< typename BidirectionalIt, typename Compare = std::less< > >
  void shellSort(BidirectionalIt begin, size_t size, Compare comp = Compare{})
  {
    BidirectionalIt * iters = new BidirectionalIt[size];
    for (size_t i = 0; i < size; ++i)
    {
      iters[i] = begin++;
    }
    for (size_t d = size / 2; d != 0; d /= 2)
    {
      for (size_t i = d; i != size; ++i)
      {
        try
        {
          for (size_t j = i; j >= d && comp(*(iters[j]), *(iters[j - d])); j -= d)
          {
            std::swap(*(iters[j]), *(iters[j - d]));
          }
        }
        catch (...)
        {
          delete [] iters;
          throw;
        }
      }
    }
    delete [] iters;
  }

  //template< typename BidirectionalIt, typename Compare = std::less< > >
  //void shellSort2(BidirectionalIt begin, size_t size, Compare comp = Compare{})
  //{
  //  for (size_t d = size / 2, cnt = d; d != 0; d /= 2, cnt = d)
  //  {
  //    for (auto i = std::next(begin, d); cnt != size; ++i, ++cnt)
  //    {
  //      for (auto j = i; std::distance(j, begin) >= d;)
  //      {
  //        BidirectionalIt b1 = std::prev(j, d);
  //        if (comp(*j, *b1))
  //        {
  //          std::swap(*j, *b1);
  //        }
  //        j = b1;
  //      }
  //    }
  //  }
  //}
}

#endif
