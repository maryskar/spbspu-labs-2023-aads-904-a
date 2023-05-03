#ifndef NODE_HPP
#define NODE_HPP

namespace detail {
  template< typename T >
  struct Node {
    Node* next;
    T val;
  };
}

#endif
