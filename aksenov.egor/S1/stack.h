#ifndef STACK_H
#define STACK_H
#include <stdexcept>
#include "list.h"
namespace aksenov {
  template< typename T >
  class Stack
  {
    public:
      explicit Stack();
      ~Stack();
      void push(const T &val);
      void pop();
      T drop();
      bool isEmpty() const;
      size_t size();
    private:
      List< T > *top_;
      size_t size_;
  };

  template< typename T >
  Stack< T >::Stack():
    top_(nullptr),
    size_(0)
  {}

  template< typename T >
  Stack< T >::~Stack()
  {
    deleteList(top_);
  }

  template< typename T>
  size_t Stack< T >::size()
  {
    return size_;
  }
  template< typename T >
  bool Stack< T >::isEmpty() const
  {
    return (top_ == nullptr);
  }

  template< typename T >
  void Stack< T >::push(const T &val)
  {
    aksenov::List< T > *newTop = new aksenov::List< T >{val, top_};
    top_ = newTop;
    size_++;
  }

  template< typename T >
  T Stack< T >::drop()
  {
    if (isEmpty())
    {
      throw std::logic_error("Empty stack");
    }
    return top_->data;
  }

  template< typename T >
  void Stack< T >::pop()
  {
    if (isEmpty())
    {
      throw std::logic_error("empty stack");
    }
    auto todel = top_;
    top_ = top_->next;
    delete todel;
    size_--;
  }
}
#endif
