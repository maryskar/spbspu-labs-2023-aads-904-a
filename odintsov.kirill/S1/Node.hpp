#ifndef NODE_HPP
#define NODE_HPP

#include <utility>

namespace detail {
  template< typename T >
  struct Node {
    T data;
    Node* next;
  };

  template< typename T >
  struct ConstNodeIter {
    const Node< T >* nodePtr;
    ConstNodeIter();

    ConstNodeIter< T >& operator++();
    ConstNodeIter< T > operator++(int);

    const T& operator*() const;
    const T* operator->() const;

    bool operator==(const ConstNodeIter< T >& rhs) const;
    bool operator!=(const ConstNodeIter< T >& rhs) const;
  };

  template< typename T >
  void deleteNodes(Node< T >* head);
  template< typename T >
  std::pair< Node< T >*, Node< T >* > duplicateNodes(const Node< T >* head);
}

#include "Node.tcc"

#endif
