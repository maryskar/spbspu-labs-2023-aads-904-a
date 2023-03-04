#ifndef STACK_HPP
#define STACK_HPP
#include <cstddef>
#include <stdexcept>
#include "list.hpp"

namespace chemodurov
{
  template< typename T >
  class Stack
  {
   public:
    Stack();
    ~Stack();
    void push(const T & rhs);
    void pop();
    T & getFromStack();
   private:
    List< T > * head_;
  };
}

template< typename T >
chemodurov::Stack< T >::Stack():
 head_(nullptr)
{}

template< typename T >
chemodurov::Stack< T >::~Stack()
{
  while (head_)
  {
    List< T > * temp = head_->next;
    delete head_;
    head_ = temp;
  }
}

template< typename T >
void chemodurov::Stack< T >::push(const T & rhs)
{
  if (capacity_ == size_)
  {
    T * new_value = new T[capacity_ + 1];
    try
    {
      for (size_t i = 0; i < size_; ++i)
      {
        new_value[i] = value_[i];
      }
      value_[size_] = rhs;
    }
    catch (...)
    {
      delete [] new_value;
      throw;
    }
    delete [] value_;
    value_ = new_value;
    ++capacity_;
    ++size_;
  }
  else
  {
    value_[size_] = rhs;
    ++size_;
  }
}

template< typename T >
void chemodurov::Stack< T >::pop()
{
  if (!size_)
  {
    throw std::logic_error("Empty stack");
  }
  value_[size_ - 1] = T();
  --size_;
}

template< typename T >
T & chemodurov::Stack< T >::getFromStack()
{
  if (!size_)
  {
    throw std::logic_error("Empty stack");
  }
  return *value_;
}

#endif
