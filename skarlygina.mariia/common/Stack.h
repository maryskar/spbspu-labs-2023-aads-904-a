#ifndef STACK_H
#define STACK_H

#include <stdexcept>
#include "List.h"
namespace skarlygina
{
  template < typename T >
  class Stack
  {
  public:
    T top() const;
    void pop();
    void clear();
    void push(const T&);
    bool isEmpty() const;
  private:
    detail::List< T > list_;
  };
  template < typename T >
  T Stack< T >::top() const
  {
    if (isEmpty())
    {
      throw std::logic_error("The Stack is empty");
    }
    return list_.front();
  }
  template < typename T >
  void Stack< T >::pop()
  {
    if (isEmpty())
    {
      throw std::logic_error("Pop from empty Stack");
    }
    list_.popFront();
  }
  template < typename T >
  void Stack< T >::clear()
  {
    list_.clear();
  }
  template < typename T >
  void Stack< T >::push(const T& data)
  {
    list_.pushFront(data);
  }
  template < typename T >
  bool Stack< T >::isEmpty() const
  {
    return list_.isEmpty();
  }
}

#endif


