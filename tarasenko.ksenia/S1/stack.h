#ifndef STACK_H
#define STACK_H
#include <stdexcept>
#include "forward_list.h"
namespace tarasenko
{
  template< typename T >
  class Stack
  {
  public:
   Stack()
   {}
   Stack(const Stack< T >& s)
   {
     top.copy(s.top);
   }
   Stack(Stack< T >&& s):
     top(s.top)
   {}
   Stack< T >& operator=(const Stack< T >& s)
   {
     try
     {
       top = s.top;
     }
     catch (...)
     {
       throw;
     }
     return *this;
   }
   Stack< T >& operator=(Stack< T >&& s)
   {
     top.clear();
     top = s.top;
     s.top = nullptr;
     return *this;
   }
   ~Stack()
   {}
   void push(T& rhs);
   T getTopElem() const;
   void pop();
   bool isEmpty() const;
  private:
   ForwardList< T > top;
  };

  template< typename T >
  bool Stack< T >::isEmpty() const
  {
    return top.isEmpty();
  }

  template< typename T >
  void Stack< T >::push(T& rhs)
  {
    top.pushFront(rhs);
  }

  template< typename T >
  T Stack< T >::getTopElem() const
  {
    if (top.isEmpty())
    {
      throw std::underflow_error("Underflow!");
    }
    return top.getFront();
  }

  template< typename T >
  void Stack< T >::pop()
  {
    if (top.isEmpty())
    {
      throw std::underflow_error("Underflow!");
    }
    top.popFront();
  }
};
#endif
