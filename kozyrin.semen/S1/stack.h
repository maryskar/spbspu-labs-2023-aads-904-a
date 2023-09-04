#ifndef STACK_H
#define STACK_H
#include <stdexcept>
#include "node.h"

namespace kozyrin {
  template< typename T >
  class Stack {
  public:
    Stack();
    Stack(const Stack< T >& origin);
    Stack(const Stack< T >&& origin) noexcept;
    Stack< T >& operator=(const Stack< T >& other);
    Stack< T >& operator=(Stack< T >&& other) noexcept;
    ~Stack();
    void push(const T& rhs);
    T& drop();
    void clearBin();
    bool isEmpty();
  private:
    node_t< T >* bin_ = nullptr;
    node_t< T >* top_ = nullptr;
  };

  template< typename T >
  Stack< T >::Stack():
    top_(nullptr)
  {}

  template< typename T >
  Stack< T >::Stack(const Stack< T >& origin):
    top_(copy(origin.top_))
  {}

  template< typename T >
  Stack< T >::Stack(const Stack< T >&& origin) noexcept:
    top_(copy(origin.top_))
  {}

  template< typename T >
  Stack< T >& Stack< T >::operator=(const Stack< T >& other)
  {
    if (this == other) {
      return *this;
    }
    top_ = copy(other.top_);
    return *this;
  }

  template< typename T >
  Stack< T >& Stack< T >::operator=(Stack< T >&& other) noexcept
  {
    if (this == other) {
      return *this;
    }
    top_ = copy(other.top_);
    return *this;
  }

  template< typename T >
  Stack< T >::~Stack()
  {
    while (top_ != nullptr) {
      node_t< T >* next = top_->next_;
      delete top_;
      top_ = next;
    }
    clearBin();
  }

  template< typename T >
  void Stack< T >::push(const T& rhs)
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
    top_->next_ = bin_;
    bin_ = top_;
    top_ = top;
    return bin_->value_;
  }

  template< typename T >
  void Stack< T >::clearBin()
  {
    while (bin_ != nullptr) {
      node_t< T >* next = bin_->next_;
      delete bin_;
      bin_ = next;
    }
  }

  template< typename T >
  bool Stack< T >::isEmpty()
  {
    return top_ == nullptr;
  }
}

#endif
