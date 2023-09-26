#ifndef SELECTIONSORT_H
#define SELECTIONSORT_H
#include <iterator>
namespace fesenko
{
  template< typename ForwardIt, typename Compare >
  void selectionSort(ForwardIt first, ForwardIt last, Compare comp)
  {
    auto next = first;
    next++;
    for (; next != last; first++) {
      auto min = first;
      for (auto cur = next; cur != last; cur++) {
        if (comp(*cur, *min)) {
          min = cur;
        }
      }
      std::swap(*min, *first);
      next++;
    }
  }
}
#endif
