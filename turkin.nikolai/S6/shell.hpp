#ifndef SHELL_H
#define SHELL_H

#include <cstddef>
#include <iterator>

namespace turkin
{
  template< typename BidirectionalIt, typename UnaryPred >
  void shell_sort(BidirectionalIt first, BidirectionalIt last, UnaryPred p)
  {
    std::size_t size = std::distance(first, last);
    for (std::size_t gap = size / 2; gap > 0; gap /= 2)
    {
      for (std::size_t i = gap; i < size; ++i)
      {
        auto temp = *std::next(first, i);
        std::size_t j = i;
        while (j >= gap && p(temp, *std::next(first, j - gap)))
        {
          *std::next(first, j) = *std::next(first, j - gap);
          j -= gap;
        }
        *std::next(first, j) = temp;
      }
    }
  }
}
#endif
