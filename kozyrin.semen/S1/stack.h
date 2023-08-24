#ifndef STACK_H
#define STACK_H
#include <stdexcept>
#include "node.h"

namespace bowlstalls {
  template< typename T >
  class Stack {
  public:
    Stack();
    Stack(const Stack<T>& origin);
    Stack(const Stack<T>&& origin) noexcept;
    ~Stack();
    void push(T rhs);
    T& drop();
    bool isEmpty();
  private:
    T value_;
    node_t< T >* top_;
  };

  template< typename T >
  Stack< T >::Stack():
    top_(nullptr)
  {}

  template< typename T >
  Stack< T >::Stack(const Stack<T>& origin):
    top_(origin.top_)
  {}

  template< typename T >
  Stack< T >::Stack(const Stack<T>&& origin) noexcept:
    top_(origin.top_)
  {}

  template< typename T >
  Stack< T >::~Stack()
  {
    while (top_ != nullptr) {
      node_t< T >* next = top_->next_;
      delete top_;
      top_ = next;
    }
  }

  template< typename T >
  void Stack< T >::push(const T rhs)
  {
    top_ = new node_t< T >{rhs, top_};
  }

  template< typename T >
  T& Stack< T >::drop()
  {
    if (top_ == nullptr) {
      throw std::length_error("Nothing to drop");
    }

    node_t< T >* top = top_->next_;
    value_ = top_->value_;
    delete top_;
    top_ = top;
    return value_;
  }

  template< typename T >
  bool Stack< T >::isEmpty()
  {
    return top_ == nullptr;
  }
}

#endif
