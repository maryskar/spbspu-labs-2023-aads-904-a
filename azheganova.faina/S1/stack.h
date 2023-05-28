#ifndef STACK_H
#define STACK_H
#include <cstddef>
#include <stdexcept>
#include "node.h"

namespace azheganova
{
  template< typename T >
  class Stack
  {
  public:
    Stack();
    ~Stack();
    Stack(const Stack< T > & rhs);
    Stack(Stack< T > && rhs);
    Stack< T > & operator=(const Stack< T > & rhs);
    Stack< T > & operator=(Stack< T > && rhs);
    void push(const T & rhs);
    void pop();
    bool isEmpty() const;
    T get() const;
    void clearStack();
  private:
    details::ListNode< T > * top_;
  };

  template< typename T >
  Stack< T >::Stack():
    top_(nullptr)
  {}

  template< typename T >
  Stack< T >::~Stack()
  {
    clearStack();
  }

  template< typename T >
  Stack< T >::Stack(const Stack< T > & rhs):
   top_(nullptr)
  {
    details::ListNode< T > * node1 = rhs.top_;
    top_ = new details::ListNode< T >(node1->data_);
    details::ListNode< T > * node2 = top_;
    while (node1->next_)
    {
      node1 = node1->next_;
      try
      {
        node2->next_ = new details::ListNode< T >(node1->data_);
      }
      catch (const std::exception & e)
      {
        clearStack();
        throw;
      }
      node2 = node2->next_;
    }
  }

  template< typename T >
  Stack< T >::Stack(Stack< T > && rhs):
   top_(rhs.top_)
  {
    rhs.top_ = nullptr;
  }

  template < typename T >
  void Stack< T >::push(const T & rhs)
  {
    details::ListNode< T > * tmp = new details::ListNode< T >{rhs, top_};
    top_ = tmp;
  }

  template< typename T >
  Stack< T > & Stack< T >::operator=(const Stack< T > & rhs)
   {
     if (this != std::addressof(rhs))
     {
      Stack< T > newstack(rhs);
      *this = std::move(newstack);
     }
     return *this;
   }

  template< typename T >
  Stack< T > & Stack< T >::operator=(Stack< T > && rhs)
  {
    if (this != std::addressof(rhs))
    {
      clear();
      top_ = rhs.top_;
      rhs.top_ = nullptr;
    }
    return *this;
  }

  template< typename T >
  void Stack< T >::pop()
  {
    if (isEmpty())
    {
      throw std::logic_error("empty stack");
    }
    details::ListNode< T > * tmp = top_->next_;
    delete top_;
    top_ = tmp;
  }

  template< typename T >
  bool Stack< T >::isEmpty() const
  {
    return top_ == nullptr;
  }

  template< typename T >
  T Stack< T >::get() const
  {
    if (isEmpty())
    {
      throw std::logic_error("empty stack");
    }
    return top_->data_;
  }

  template < typename T >
  void Stack< T >::clearStack()
  {
    while (!isEmpty())
    {
      pop();
    }
  }
}

#endif
