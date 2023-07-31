#ifndef FA_TAKE_RANDOM_ELEM_H
#define FA_TAKE_RANDOM_ELEM_H

#include <random>
#include <iterator>

namespace tarasenko
{
  template< typename Iter, typename Generator >
  Iter takeRandomElem(Iter first, Iter last, Generator& gen)
  {
    std::uniform_int_distribution<> dis(0, std::distance(first, last) - 1);
    std::advance(first, dis(gen));
    return first;
  }

  template< typename Iter >
  Iter takeRandomElem(Iter first, Iter last)
  {
    std::random_device rd;
    std::mt19937 gen(rd());
    return takeRandomElem(first, last, gen);
  }
}
#endif
