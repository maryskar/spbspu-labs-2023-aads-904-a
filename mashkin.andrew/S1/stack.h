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
    Stack(const Stack< T >& lhs);
    Stack(Stack< T >&& rhs) noexcept;
    ~Stack();

    void push(const T& rhs);
    void pop();
    bool isEmpty() const noexcept;
    T& getTop();

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
mashkin::Stack< T >::Stack(const Stack< T >& lhs):
  top_(lhs.top_)
{
}

template< typename T >
mashkin::Stack< T >::Stack(Stack< T >&& rhs) noexcept:
  top_(rhs.top_)
{
  rhs.top_ = nullptr;
}

template< typename T >
mashkin::Stack< T >::~Stack()
{
  while (isEmpty())
  {
    this->pop();
  }
}

template< typename T >
void mashkin::Stack< T >::push(const T& rhs)
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
  else
  {
    list_t< T >* newhead = top_->next;
    delete top_;
    top_ = newhead;
  }
}

template< typename T >
T& mashkin::Stack< T >::getTop()
{
  return top_->data;
}

template< typename T >
bool mashkin::Stack< T >::isEmpty() const noexcept
{
  return top_;
}
#endif
