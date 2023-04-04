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
    Stack(const Stack< T > &);
    Stack(Stack< T > &&);
    ~Stack();
    Stack< T > & operator=(const Stack< T > &);
    Stack< T > & operator=(Stack< T > &&);
    void push(const T & rhs);
    void pop();
    T & getFromStack() const;
    bool empty() const noexcept;
   private:
    List< T > * head_;
    void copyStack(const Stack< T > &);
    void deleteStack() noexcept;
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
T & chemodurov::Stack< T >::getFromStack() const
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

template< typename T >
void chemodurov::Stack< T >::deleteStack() noexcept
{
  deleteList(head_);
  head_ = nullptr;
}

template< typename T >
void chemodurov::Stack< T >::copyStack(const chemodurov::Stack< T > & stack)
{
  if (stack.empty())
  {
    head_ = nullptr;
    return;
  }
  List< T > * source = stack.head_;
  head_ = new List< T >{source->data, nullptr};
  List< T > * dest = head_;
  try
  {
    while (source->next)
    {
      source = source->next;
      dest->next = new List< T >{source->data, nullptr};
      dest = dest->next;
    }
  }
  catch (...)
  {
    deleteStack();
    throw;
  }
}

#endif
