#ifndef NODE_HPP
#define NODE_HPP

#include <stdexcept>
#include <utility>

namespace detail {
  template< typename T >
  struct Node {
    T data;
    Node* next;
  };

  template< typename T >
  void deleteNodes(Node< T >* head)
  {
    while (head) {
      Node< T >* oldHead = head;
      head = head->next;
      delete oldHead;
    }
  }

  template< typename T >
  std::pair< Node< T >*, Node< T >* > duplicateNodes(const Node< T >* head)
  {
    if (!head) {
      throw std::invalid_argument("Attempt to duplicate empty list");
    }
    Node< T >* const newHead = new Node< T >{head->data, nullptr};
    Node< T >* newTail = newHead;
    head = head->next;
    while (head != nullptr) {
      try {
        newTail->next = new Node< T >{head->data, nullptr};
      } catch (...) {
        deleteNodes(newHead);
        throw;
      }
      newTail = newTail->next;
      head = head->next;
    }
    return std::make_pair(newHead, newTail);
  }
}

#endif
