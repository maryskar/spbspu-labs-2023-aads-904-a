#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "AppendableList.hpp"

namespace odintsov {
  template< typename T >
  class Queue: public AppendableList< T > {
    public:
      T& head();
      void pop();
  };
}

#endif
