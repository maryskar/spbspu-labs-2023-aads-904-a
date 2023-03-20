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
    bool empty() const noexcept;
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
  List< T > * temp = new List< T >{rhs, head_};
  head_ = temp;
}

template< typename T >
T & chemodurov::Stack< T >::getFromStack()
{
  if (!head_)
  {
    throw std::logic_error("Empty stack");
  }
  return (*head_).data;
}

template< typename T >
void chemodurov::Stack< T >::pop()
{
  if (!head_)
  {
    throw std::logic_error("Empty stack");
  }
  List< T > * temp = head_->next;
  delete head_;
  head_ = temp;
}

template< typename T >
bool chemodurov::Stack< T >::empty() const noexcept
{
  return head_ == nullptr;
}

#endif
