#ifndef FILLRANDOM_H
#define FILLRANDOM_H
#include <random>
#include <dictionary/forward-list/forwardList.h>
namespace fesenko
{
  template< typename T >
  void fillRandom(ForwardList< T > &container, size_t size)
  {
    std::random_device rd;
    std::mt19937 gen(rd());
    if (std::is_same< typename ForwardList< T >::value_type, int >::value) {
      std::uniform_int_distribution< int > dis(0, 100);
      for (size_t i = 0; i < size; i++) {
        container.push_back(dis(gen));
      }
    } else {
      std::uniform_real_distribution< float > dis(0.0, 100.0);
      for (size_t i = 0; i < size; i++) {
        container.push_back(dis(gen));
      }
    }
  }
}
#endif

