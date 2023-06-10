#ifndef STACK_H
#define STACK_H
#include <stdexcept>
#include "list.h"
namespace aksenov {
  template< typename T >
  class Stack
  {
    public:
      Stack();
      ~Stack();
      void push(const T &val);
      void pop();
      T drop();
      bool isEmpty();
    private:
      aksenov::List< T > *top_;
  };

  template< typename T >
  Stack< T >::Stack():
  top_(nullptr)
  {}

  template< typename T >
  Stack< T >::~Stack()
  {
    deleteList(top_);
  }

  template< typename T >
  bool Stack< T >::isEmpty()
  {
    return (top_ == nullptr);
  }

  template< typename T >
  void Stack< T >::push(const T &val)
  {
    aksenov::List< T > *newTop = new aksenov::List< T >{val, top_};
    top_ = newTop;
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
  }
}
#endif
