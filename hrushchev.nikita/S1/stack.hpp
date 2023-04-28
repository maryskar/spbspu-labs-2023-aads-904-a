#ifndef STACK_HPP
#define STACK_HPP
#include "list.hpp"
#include <stdexcept>

namespace hrushchev
{
  template< typename T >
  class Stack
  {
    public:
      Stack();
      ~Stack();
      Stack(const Stack< T >& other);
      Stack< T >& operator=(const Stack< T >& other);
      Stack(Stack< T >&& other);
      Stack< T >& operator=(Stack< T >&& other);
      void push(const T& value);
      void pop();
      T get() const;
      bool isEmpty() const;
    private:
      details::List< T >* value_;
  };

  template< typename T >
  Stack< T >::Stack():
    value_(nullptr)
  {}

  template< typename T >
  bool Stack< T >::isEmpty() const
  {
    return (value_ == nullptr);
  }

  template< typename T >
  void Stack< T >::push(const T& value)
  {
    details::List< T >* temp = new details::List< T >{value, value_};
    value_ = temp;
  }

  template< typename T >
  T Stack< T >::get() const
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
    details::List< T >* temp = value_->next;
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

  template< typename T >
  Stack< T >::Stack(const Stack< T >& other):
    value_(nullptr)
  {
    details::List< T >* other_value = other.value_;
    while (other_value != nullptr)
    {
      push(other_value->data_);
      other_value = other_value->next;
    }
  }

  template< typename T >
  Stack< T >& Stack< T >::operator=(const Stack< T >& other)
  {
    if (this != &other)
    {
      while (!isEmpty())
      {
        pop();
      }
      details::List< T >* other_value = other.value_;
      while (other_value != nullptr)
      {
        push(other_value->data_);
        other_value = other_value->next;
      }
    }
    return *this;
  }

  template< typename T >
  Stack< T >::Stack(Stack< T >&& other):
    value_(other.value_)
  {
    other.value_ = nullptr;
  }

  template< typename T >
  Stack< T >& Stack< T >::operator=(Stack< T >&& other)
  {
    if (this != &other)
    {
      while (!isEmpty())
      {
        pop();
      }
      value_ = other.value_;
      other.value_ = nullptr;
    }
  }
}

#endif

