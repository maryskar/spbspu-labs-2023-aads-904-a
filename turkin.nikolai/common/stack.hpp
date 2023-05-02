#ifndef STACK_HPP
#define STACK_HPP

#include <stdexcept>
#include "s-q-help.hpp"
#include "oneway-list.hpp"

namespace turkin
{
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
      void swap(Stack< T > & rhs) noexcept;
      void push(const T & rhs);
      T drop();
      T drop() const;
      bool isEmpty() const;
    private:
      pattern::OneWayNode< T > * value_;
  };
}

template< typename T >
turkin::Stack< T >::Stack():
  value_(nullptr)
{}

template< typename T >
turkin::Stack< T >::Stack(const Stack< T > & rhs):
  value_(copyList(rhs.value_))
{}

template< typename T >
turkin::Stack< T >::Stack(Stack< T > && rhs):
  value_(rhs.value_)
{
  rhs.value_ = nullptr;
}

template< typename T >
turkin::Stack< T > & turkin::Stack< T >::operator=(const Stack< T > & rhs)
{
  Stack< T > temp(rhs);
  swap(temp);
  return * this;
}

template< typename T >
turkin::Stack< T > & turkin::Stack< T >::operator=(Stack< T > && rhs)
{
  Stack< T > temp;
  swap(temp);
  value_ = rhs.value_;
  rhs.value_ = nullptr;
  return * this;
}

template< typename T >
turkin::Stack< T >::~Stack()
{
  turkin::sqhelp::free(value_);
}

template< typename T >
void turkin::Stack< T >::swap(Stack< T > & rhs) noexcept
{
  std::swap(value_, rhs.value_);
}

template< typename T >
void turkin::Stack< T >::push(const T & rhs)
{
  value_ = new pattern::OneWayNode< T > {rhs, value_};
}

template< typename T >
T turkin::Stack< T >::drop()
{
  if (isEmpty())
  {
    throw std::runtime_error("stack is empty");
  }
  pattern::OneWayNode< T > * element = value_;
  value_ = element->next;
  T ret = element->data;
  delete element;
  return ret;
}

template< typename T >
T turkin::Stack< T >::drop() const
{
  if (isEmpty())
  {
    throw std::runtime_error("stack is empty");
  }
  return turkin::sqhelp::remove(value_);
}

template< typename T >
bool turkin::Stack< T >::isEmpty() const
{
  return value_ == nullptr;
}

#endif
