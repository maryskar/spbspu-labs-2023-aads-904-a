#ifndef NODE_HPP
#define NODE_HPP

#include <utility>

namespace detail {
  template< typename T >
  struct Node {
    T data;
    Node< T >* next;
  };

  template< typename T >
  void deleteNodes(Node< T >* head);
  template< typename T >
  std::pair< Node< T >*, Node< T >* > duplicateNodes(const Node< T >* head);
}

#include "Node.tcc"

#endif
