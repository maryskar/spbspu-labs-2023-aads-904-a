#ifndef NODE_H
#define NODE_H
#include <ostream>

namespace Chulkov {
  template < typename T >
  struct Node {
    explicit Node(const T& val):
      item(val),
      next(nullptr)
    {}
    T item;
    Node< T >* next;
  };

  template < typename T > void clear(Node< T >* head)
  {
    while (head) {
      Node< T >* cur = head;
      head = head->next;
      delete cur;
    }
  }
  template < typename T >
  std::ostream& print(std::ostream& out, const Node< T >* head) {
    std::ostream::sentry sentry(out);
    if(sentry) {
      if (head) {
        out << head->item;
      }
      head = head->next;
      while (head) {
        out << ' ' << head->item;
        head = head->next;
      }
    }
    return out;
  }
  template < typename  T >
  std::pair< Node< T >*, Node< T >* > copy(const Node< T >* head) {
    Node< T >* ret = head ? new Node< T >* (head->item) : nullptr;
    Node< T >* tail = ret;
    while (head) {
      try {
        tail->next = new Node< T >(head->item);
      } catch (...) {
        clear(ret);
        throw;
      }
      tail = tail->next;
      head = head->next;
    }
    return {ret, tail};
  }
}
#endif
