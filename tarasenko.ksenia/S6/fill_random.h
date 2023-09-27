#ifndef S6_FILL_RANDOM_H
#define S6_FILL_RANDOM_H

#include <random>
#include <stdexcept>
#include <forward_list.h>

namespace tarasenko
{
  template< typename T >
  void fillRandom(ForwardList< T >& container, size_t size)
  {
    std::random_device rd;
    std::mt19937 gen(rd());
    if (std::is_same< typename ForwardList< T >::value_type, int >::value)
    {
      std::uniform_int_distribution< int > dis(0, 100);
      for (size_t i = 0; i < size; ++i)
      {
        container.pushBack(dis(gen));
      }
    }
    else if (std::is_same< typename ForwardList< T >::value_type, float >::value)
    {
      std::uniform_real_distribution< float > dis(0.0, 100.0);
      for (size_t i = 0; i < size; ++i)
      {
        container.pushBack(dis(gen));
      }
    }
    else
    {
      throw std::invalid_argument("Unsupported type");
    }
  }

}
#endif
