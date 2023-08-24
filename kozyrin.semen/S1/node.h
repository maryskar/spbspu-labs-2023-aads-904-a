#ifndef NODE_H
#define NODE_H

namespace bowlstalls {
  template< typename T >
  struct node_t {
    T value_ = 0;
    node_t< T >* next_ = nullptr;
  };
}

#endif
