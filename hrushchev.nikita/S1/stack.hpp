#ifndef STACK_HPP
#define STACK_HPP
#include "list.hpp"
#include <stdexcept>

template< typename T >
class Stack
{
  public:
    Stack();
    ~Stack();
    void push(const T& value);
    void pop();
    T& get() const;
    bool isEmpty() const;
  private:
    List< T >* value_;
};

template< typename T >
Stack< T >::Stack():
  value_(nullptr)
{
}

template< typename T >
bool Stack< T >::isEmpty() const
{
  return (value_ == nullptr);
}

template< typename T >
void Stack< T >::push(const T& value)
{
  List< T >* temp = new List< T >{value, value_};
  value_ = temp;
}

template< typename T >
T& Stack< T >::get() const
{
  if(isEmpty())
  {
    throw std::logic_error("Empty stack");
  }
  return value_->data;
}

template< typename T >
void Stack< T >::pop()
{
  if(isEmpty())
  {
    throw std::logic_error("Empty stack");
  }
  List< T >* temp = value_->data;
  delete value_;
  value_ = temp;
}

template< typename T >
Stack< T >::~Stack()
{
  while(!isEmpty())
  {
    pop();
  }
}
#endif
