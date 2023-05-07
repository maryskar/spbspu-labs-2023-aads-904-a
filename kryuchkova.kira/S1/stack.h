#ifndef STACK_H
#define STACK_H
#include <stdexcept>
#include "node.h"
#include <iostream>

namespace kryuchkova
{
  template< typename T >
  class Stack
  {
    public:
      Stack();
      Stack(const Stack< T > &);
      Stack(Stack< T > &&);
      ~Stack();
      Stack< T > & operator=(const Stack< T > &);
      Stack< T > & operator=(Stack< T > &&);
      void push(T rhs);
      T drop();
      bool isEmpty();
    private:
      Node< T > *head_;
      void deleteStack() noexcept;
      void copyStack(const Stack< T > &);
  };

  template< typename T >
  Stack< T >::Stack():
    head_(nullptr)
  {}

  template < typename T >
  void Stack< T >::deleteStack() noexcept
  {
    deleteNode(head_);
    head_ = nullptr;
  }

  template< typename T >
  Stack< T >::~Stack()
  {
    while(!isEmpty())
    {
      Node< T > *temp = head_->next_;
      delete head_;
      head_ = temp;
    }
  }

  template< typename T >
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

  template< typename T >
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

  template< typename T >
  bool Stack< T >::isEmpty()
  {
    return head_ == nullptr;
  }

  template< typename T >
  void Stack< T >::copyStack(const Stack< T > &stack)
  {
    head_ = copyNode(stack.head_);
  }

  template< typename T >
  Stack< T >::Stack(Stack< T > &&stack):
    head_(stack.head_)
  {
    stack.head_ = nullptr;
  }

  template< typename T >
  Stack< T >::Stack(const Stack< T > &stack):
    Stack()
  {
    copyStack(stack);
  }

  template< typename T >
  Stack< T > &Stack< T >::operator=(const Stack< T > &stack)
  {
    if (this == std::addressof(stack))
    {
      return *this;
    }
    Node< T > *temp = head_;
    try
    {
      copyStack(stack);
    }
    catch (...)
    {
      deleteStack();
      head_ = temp;
      throw;
    }
    deleteNode(temp);
    return *this;
  }

  template< typename T >
  Stack< T > &Stack< T >::operator=(Stack< T > &&stack)
  {
    if (this == std::addressof(stack))
    {
      return *this;
    }
    deleteStack();
    head_ = stack.head_;
    stack.head_ = nullptr;
    return *this;
  }
}

#endif
