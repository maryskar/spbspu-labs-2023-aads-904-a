#ifndef STACK_H
#define STACK_H
#include <stdexcept>
#include "node.h"
namespace tarasenko
{
  template< typename T >
  class Stack
  {
  public:
   Stack();
   Stack(const Stack< T >& s);
   ~Stack();
   void push(T rhs);
   T drop();
   T getTopElem() const;
   void pop();
   bool isEmpty() const;
  private:
   details::NodeOfList< T >* top;
  };

  template< typename T >
  Stack< T >::Stack():
    top(nullptr)
  {}

  template< typename T >
  Stack< T >::Stack(const Stack< T >& s):
    top(nullptr)
  {
    details::NodeOfList< T >* copy = s.top;
    while (copy)
    {
      push(copy->data);
      copy = copy->next;
    }
  }

  template< typename T >
  Stack< T >::~Stack()
  {
    while (top)
    {
      pop();
    }
  }

  template< typename T >
  bool Stack< T >::isEmpty() const
  {
    return details::isEmpty(top);
  }

  template< typename T >
  void Stack< T >::push(T rhs)
  {
    details::pushFront(&top, rhs);
  }

  template< typename T >
  T Stack< T >::drop()
  {
    if (details::isEmpty(top))
    {
      throw std::underflow_error("Underflow!");
    }
    return details::dropFront(&top);
  }

  template< typename T >
  T Stack< T >::getTopElem() const
  {
    if (details::isEmpty(top))
    {
      throw std::underflow_error("Underflow!");
    }
    return top->data;
  }

  template< typename T >
  void Stack< T >::pop()
  {
    if (details::isEmpty(top))
    {
      throw std::underflow_error("Underflow!");
    }
    details::popFront(&top);
  }
};
#endif
