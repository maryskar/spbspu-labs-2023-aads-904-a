#ifndef STACK_H
#define STACK_H
#include <cstddef>
#include <stdexcept>
#include "list.h"

namespace mashkin
{
  template< typename T >
  class Stack
  {
  public:
    Stack();
    /*Stack(const Stack< T >& lhs);
    Stack(Stack< T >&& rhs);*/

    void push(T rhs);
    void pop();
    bool isEmpty() const;
    T& drop();

  private:
    list_t< T >* top_;
  };
}

template< typename T >
mashkin::Stack< T >::Stack():
  top_(nullptr)
{
}

template< typename T >
void mashkin::Stack< T >::push(T rhs)
{
  if (!top_)
  {
    top_ = new list_t< T >{rhs, nullptr};
  }
  else
  {
    top_ = new list_t< T >{rhs, top_};
  }
}

template< typename T >
void mashkin::Stack< T >::pop()
{
  if (!top_)
  {
    throw std::underflow_error("Stack underflow");
  }
  else if (!top_->next)
  {
    delete top_;
    top_ = nullptr;
  }
  else
  {
    list_t< T >* newhead = top_->next;
    delete top_;
    top_ = newhead;
  }
}

template< typename T >
T& mashkin::Stack< T >::drop()
{
  return top_->data;
}

template< typename T >
bool mashkin::Stack< T >::isEmpty() const
{
  return top_;
}
#endif
