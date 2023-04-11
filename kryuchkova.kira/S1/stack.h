#ifndef STACK_H
#define STACK_H
#include <stdexcept>
#include "node.h"
#include <iostream>

namespace kryuchkova
{
  template < typename T >
  class Stack
  {
    public:
      Stack();
      //Stack & operator=(const Stack & stack);
      ~Stack();
      void push(T rhs);
      T drop();
      bool isEmpty();
    private:
      Node< T > *head_;
  };

  template < typename T >
  Stack< T >::Stack():
    head_(nullptr)
  {}

  template < typename T >
  Stack< T >::~Stack()
  {
    while (head_)
    {
      drop();
    }
  }

  template < typename T >
  void Stack< T >::push(T rhs)
  {
    Node< T > *new_node = new Node< T >(rhs);
    if (head_ == nullptr)
    {
      head_ = new_node;
    }
    else
    {
      new_node->next_ = head_;
      head_ = new_node;
    }
  }

  template < typename T >
  T Stack< T >::drop()
  {
    T current_data = head_->data_;
    if (isEmpty())
    {
      throw std::logic_error("Empty stack");
    }
    Node< T > *data = head_->next_;
    delete head_;
    head_ = data;
    return current_data;
  }

  template < typename T >
  bool Stack< T >::isEmpty()
  {
    return head_ == nullptr;
  }
}

#endif
