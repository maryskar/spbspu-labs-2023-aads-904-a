#ifndef RANDOM_STORAGE_HPP
#define RANDOM_STORAGE_HPP

#include <cstddef>
#include <random>

namespace turkin
{
  template< class Storage, typename T >
  Storage fill(std::size_t amount)
  {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution< float > dis(0.0, 100.0);
    Storage result;
    for (std::size_t i = 0; i < amount; i++)
    {
      result.push_front(static_cast< T >(dis(gen)));
    }
    return result;
  }
}

#endif
