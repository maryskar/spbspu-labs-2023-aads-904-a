#ifndef STACK_H
#define STACK_H
#include <stdexcept>
#include <utility>
#include <memory>
#include "forward_list.h"
namespace tarasenko
{
  template< typename T >
  class Stack
  {
  public:
   Stack():
     top_()
   {}
   Stack(const Stack< T >& s):
     top_(s.top_)
   {}
   Stack(Stack< T >&& s):
     top_(std::move(s.top_))
   {}
   Stack< T >& operator=(const Stack< T >& other)
   {
     if (this != std::addressof(other))
     {
       top_ = other.top_;
     }
     return *this;
   }
   Stack< T >& operator=(Stack< T >&& other)
   {
     if (this != std::addressof(other))
     {
       top_ = std::move(other.top_);
     }
     return *this;
   }
   ~Stack()
   {}
   void push(const T& rhs);
   T getTopElem() const;
   void pop();
   bool isEmpty() const;
  private:
   ForwardList< T > top_;
  };

  template< typename T >
  bool Stack< T >::isEmpty() const
  {
    return top_.isEmpty();
  }

  template< typename T >
  void Stack< T >::push(const T& rhs)
  {
    top_.pushFront(rhs);
  }

  template< typename T >
  T Stack< T >::getTopElem() const
  {
    if (top_.isEmpty())
    {
      throw std::logic_error("It's empty!");
    }
    return top_.getFront();
  }

  template< typename T >
  void Stack< T >::pop()
  {
    if (top_.isEmpty())
    {
      throw std::logic_error("It's empty!");
    }
    top_.popFront();
  }
}
#endif
