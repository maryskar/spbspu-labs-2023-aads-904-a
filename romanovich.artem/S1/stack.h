#ifndef STACK_H
#define STACK_H
#include <stdexcept>
#include <iostream>
#include "node.h"
namespace romanovich
{
  template < typename T >
  class Stack
  {
  public:
    Stack();
    ~Stack();
    void push(const T &value);
    void pop();
    T get() const;
    bool isEmpty() const
    {
      return size_ == 0;
    }
  private:
    details::ListNode< T > *top_;
    size_t size_;
  };
  template < typename T >
  Stack< T >::Stack():
    top_(nullptr),
    size_(0)
  {
  }
  template < typename T >
  Stack< T >::~Stack()
  {
    while (!isEmpty())
    {
      pop();
    }
  }
  template < typename T >
  void Stack< T >::push(const T &value)
  {
    if (top_ == nullptr)
    {
      top_ = new details::ListNode< T >{value, nullptr};
    }
    else
    {
      details::ListNode< T > *newNode = new details::ListNode< T >{value, top_};
      top_ = newNode;
    }
    size_++;
  }
  template < typename T >
  T Stack< T >::get() const
  {
    if (isEmpty())
    {
      throw std::range_error("Stack is empty.");
    }
    return top_->data_;
  }
  template < typename T >
  void Stack< T >::pop()
  {
    if (isEmpty())
    {
      throw std::range_error("Stack is empty.");
    }
    details::ListNode< T > *subTop = top_->next_;
    delete top_;
    top_ = subTop;
    size_--;
  }
}
#endif
