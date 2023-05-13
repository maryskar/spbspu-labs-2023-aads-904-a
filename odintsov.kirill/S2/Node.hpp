#ifndef NODE_HPP
#define NODE_HPP

namespace odintsov {
  namespace detail {
    template< typename T >
    struct Node {
      Node* next;
      T val;
    };
  }
}

#endif
