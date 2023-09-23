#ifndef NODE_H
#define NODE_H

#include <utility>

namespace kryuchkova
{
  template< typename T >
  struct Node
  {
    T data_;
    Node *next_;
    Node(T rhs):
      data_(rhs),
      next_(nullptr)
    {}
  };

  template< typename T >
  void deleteNode(Node< T > *head)
  {
    while (head)
    {
      Node< T > *temp = head->next_;
      delete head;
      head = temp;
    }
  }

  template< typename T >
  std::pair< Node< T > *, Node< T > * > copyNode(const Node< T > *head)
  {
    if (!head)
    {
      return {nullptr, nullptr};
    }
    Node< T > *from = head;
    Node< T > *to = new Node< T >{ from->data_, nullptr };
    Node< T > *temp = to;
    Node< T > *to_head = temp;
    try
    {
      while (from->next_)
      {
        from = from->next_;
        to_head = temp;
        temp->next_ = new Node< T >{ from->data_, nullptr };
        temp = temp->next_;
      }
    }
    catch(...)
    {
      deleteNode(to);
      throw;
    }
    return {to, to_head};
  }
}

#endif
