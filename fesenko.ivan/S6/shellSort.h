#ifndef SHELLSORT_H
#define SHELLSORT_H
#include <utility>
#include <iterator>
namespace fesenko
{
  template< typename ForwardIt, typename Compare >
  void shellSort(ForwardIt first, ForwardIt last, Compare comp)
  {
    size_t size = std::distance(first, last);
    for (size_t gap = size / 2; gap > 0; gap /= 2) {
      for (size_t i = gap; i < size; i++) {
        auto temp = *std::next(first, i);
        size_t j = i;
        for (; j >= gap && comp(temp, *std::next(first, j - gap)); j -= gap) {
          *std::next(first, j) = *std::next(first, j - gap);
        }
        *std::next(first, j) = temp;
      }
    }
  }
}
#endif
