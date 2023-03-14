#ifndef STACK_H
#define STACK_H

#include <stdexcept>
#include "oneway-list.h"

template< typename T >
class Stack
{
  public:
    Stack();
    ~Stack();
    void push(const T & rhs);
    T drop();
    bool isEmpty() const;
  private:
    OneWayList< T > * value_;
};

template< typename T >
Stack< T >::Stack():
  value_(nullptr)
{}

template< typename T >
Stack< T >::~Stack()
{
  while (value_ != nullptr)
  {
    OneWayList< T > * element = value_;
    value_ = value_->next;
    delete element;
  }
}

template< typename T >
void Stack< T >::push(const T & rhs)
{
  value_ = new OneWayList< T > {rhs, value_};
}

template< typename T >
T Stack< T >::drop()
{
  if (isEmpty())
  {
    throw std::runtime_error("stack is empty");
  }
  OneWayList< T > * element = value_;
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
