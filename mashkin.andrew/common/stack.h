#ifndef STACK_H
#define STACK_H
#include <cstddef>
#include <stdexcept>
#include "ForwardList/list.h"

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
    const T& getTop() const;

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
  top_(nullptr)
{
  auto var = lhs.top_;
  if (var)
  {
    top_ = new list_t< T >{var->data, nullptr};
    auto end = top_;
    var = var->next;
    while (var)
    {
      end->next = new list_t< T >{var->data, nullptr};
      end = end->next;
      var = var->next;
    }
  }
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
    pop();
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
  if (!top_)
  {
    throw std::underflow_error("Stack underflow");
  }
  return top_->data;
}

template< typename T >
const T& mashkin::Stack< T >::getTop() const
{
  return getTop();
}

template< typename T >
bool mashkin::Stack< T >::isEmpty() const noexcept
{
  return top_;
}
#endif
