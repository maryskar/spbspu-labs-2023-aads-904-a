#ifndef STACK_H
#define STACK_H

#include <stdexcept>
#include "oneway-node.h"

template< typename T >
class Stack
{
  public:
    Stack();
    Stack(const Stack< T > & rhs);
    Stack(Stack< T > && rhs);
    Stack & operator=(const Stack< T > & rhs);
    Stack & operator=(Stack< T > && rhs);
    ~Stack();
    void push(const T & rhs);
    T drop();
    bool isEmpty() const;
  private:
    OneWayNode< T > * value_;
};

template< typename T >
Stack< T >::Stack():
  value_(nullptr)
{}

template< typename T >
Stack< T >::Stack(const Stack< T > & rhs):
  value_(nullptr)
{
  OneWayNode< T > * clone = rhs.value_;
  while(clone)
  {
    push(clone->data);
    clone = clone->next;
  }
}

template< typename T >
Stack< T >::Stack(Stack< T > && rhs):
  value_(rhs.value_)
{
  rhs.value_ = nullptr;
}

template< typename T >
Stack< T > & Stack< T >::operator=(const Stack< T > & rhs)
{
  if (this == & rhs)
  {
    return * this;
  }
  return * this;
}

template< typename T >
Stack< T > & Stack< T >::operator=(Stack < T > && rhs)
{
  if (this == & rhs)
  {
    return * this;
  }
  value_ = rhs.value_;
  rhs.value_ = nullptr;
  return * this;
}

template< typename T >
Stack< T >::~Stack()
{
  while (value_ != nullptr)
  {
    OneWayNode< T > * element = value_;
    value_ = value_->next;
    delete element;
  }
}

template< typename T >
void Stack< T >::push(const T & rhs)
{
  value_ = new OneWayNode< T > {rhs, value_};
}

template< typename T >
T Stack< T >::drop()
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
bool Stack< T >::isEmpty() const
{
  return value_ == nullptr;
}

#endif
