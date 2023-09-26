#ifndef ODDEVENSORT_H
#define ODDEVENSORT_H
#include <utility>
#include <iterator>
namespace fesenko
{
  template< typename ForwardIt, typename Compare >
  void oddEvenSort(ForwardIt first, ForwardIt last, Compare comp)
  {
    auto end = first;
    while (std::next(end) != last) {
      end++;
    }
    bool isSorted = false;
    while (!isSorted) {
      isSorted = true;
      auto odd = std::next(first);
      while (odd != end) {
        if (comp(*std::next(odd), *odd)) {
          std::swap(*std::next(odd), *odd);
          isSorted = false;
        }
        odd++;
        if (odd == end) {
          break;
        }
        odd++;
      }
      auto even = first;
      while (even != end) {
        if (comp(*std::next(even), *even)) {
          std::swap(*std::next(even), *even);
          isSorted = false;
        }
        even++;
        if (even == end) {
          break;
        }
        even++;
      }
    }
  }
}
#endif
