#ifndef STACK_H
#define STACK_H

#include <stdexcept>
#include "oneway-node.h"

namespace turkin
{
  template< typename T >
  class Stack
  {
    public:
      Stack();
      Stack(const Stack< T > & rhs) = delete;
      Stack(Stack< T > && rhs) = delete;
      Stack & operator=(const Stack< T > & rhs) = delete;
      Stack & operator=(Stack< T > && rhs) = delete;
      ~Stack();
      void push(const T & rhs);
      T & drop();
      T & drop() const;
      bool isEmpty() const;
    private:
      OneWayNode< T > * value_;
  };
}

template< typename T >
turkin::Stack< T >::Stack():
  value_(nullptr)
{}

template< typename T >
turkin::Stack< T >::~Stack()
{
  while (value_ != nullptr)
  {
    OneWayNode< T > * element = value_;
    value_ = value_->next;
    delete element;
  }
}

template< typename T >
void turkin::Stack< T >::push(const T & rhs)
{
  value_ = new OneWayNode< T > {rhs, value_};
}

template< typename T >
T & turkin::Stack< T >::drop()
{
  return drop();
}

template< typename T >
T & turkin::Stack< T >::drop() const
{
  if (isEmpty())
  {
    throw std::runtime_error("stack is empty");
  }
  OneWayNode< T > * element = value_;
  value_ = element->next;
  T ret = element->data;
  delete element;
  return ret;
}

template< typename T >
bool turkin::Stack< T >::isEmpty() const
{
  return value_ == nullptr;
}

#endif
