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
      void deleteStack() noexcept;
  };

  template < typename T >
  Stack< T >::Stack():
    head_(nullptr)
  {}

  template < typename T >
  void Stack< T >::deleteStack() noexcept
  {
    while (!isEmpty())
    {
      Node< T > * temp = head_->next_;
      delete head_;
      head_ = temp;
    }
  }

  template < typename T >
  Stack< T >::~Stack()
  {
    deleteStack();
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
    if (isEmpty())
    {
      throw std::logic_error("Empty stack");
    }
    Node< T > *tmp = head_;
    T data = head_->data_;
    head_ = head_->next_;
    delete tmp;
    return data;
  }

  template < typename T >
  bool Stack< T >::isEmpty()
  {
    return head_ == nullptr;
  }
}

#endif
