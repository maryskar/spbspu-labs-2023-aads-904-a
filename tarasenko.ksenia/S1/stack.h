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
   size_t size;
  };

  template< typename T >
  Stack< T >::Stack():
    top(nullptr),
    size(0)
  {}

  template< typename T >
  Stack< T >::Stack(const Stack< T >& s):
    top(nullptr),
    size(s.size)
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
    return size == 0;
  }

  template< typename T >
  void Stack< T >::push(T rhs)
  {
    top = new details::NodeOfList< T >(rhs, top);
    size++;
  }

  template< typename T >
  T Stack< T >::drop()
  {
    if (size == 0)
    {
      throw std::underflow_error("Underflow!");
    }
    details::NodeOfList< T >* temp = top;
    T temp_val = temp->data;
    top = top->next;
    delete temp;
    size--;
    return temp_val;
  }

  template< typename T >
  T Stack< T >::getTopElem() const
  {
    if (size == 0)
    {
      throw std::underflow_error("Underflow!");
    }
    return top->data;
  }

  template< typename T >
  void Stack< T >::pop()
  {
    if (size == 0)
    {
      throw std::underflow_error("Underflow!");
    }
    details::NodeOfList< T >* temp = top;
    top = top->next;
    delete temp;
    size--;
  }
};
#endif
