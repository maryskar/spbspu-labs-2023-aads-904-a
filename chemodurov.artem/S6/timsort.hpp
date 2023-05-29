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
    void sortInsertion(RandomIt begin, size_t size, Compare comp)
    {
      using value_type = std::remove_reference_t< decltype(*begin) >;
      for (size_t i = 1; i < size; ++i)
      {
        value_type temp = begin[i];
        size_t j = i;
        while (j > 1 && comp(temp, begin[j - 1]))
        {
          begin[j] = begin[j - 1];
          --j;
        }
        begin[j] = temp;
      }
    }
  }
  template< typename RandomIt, typename Compare = std::less< > >
  void timsort(RandomIt begin, RandomIt end, Compare comp = Compare{})
  {

  }
}
#endif
