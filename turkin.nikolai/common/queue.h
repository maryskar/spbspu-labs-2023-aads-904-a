#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>
#include "oneway-node.h"

namespace turkin
{
  template< typename T >
  class Queue
  {
    public:
      Queue();
      Queue(const Queue< T > & rhs) = delete;
      Queue(Queue< T > && rhs) = delete;
      Queue & operator=(const Queue< T > & rhs) = delete;
      Queue & operator=(Queue< T > && rhs) = delete;
      ~Queue();
      void push(const T & rhs);
      T drop();
      bool isEmpty() const;
    private:
      OneWayNode< T > * value_;
  };
}

template< typename T >
turkin::Queue< T >::Queue():
  value_(nullptr)
{}

template< typename T >
turkin::Queue< T >::~Queue()
{
  while (value_ != nullptr)
  {
    OneWayNode< T > * element = value_;
    value_ = value_->next;
    delete element;
  }
}

template< typename T >
void turkin::Queue< T >::push(const T & rhs)
{
  if (isEmpty())
  {
    value_ = new OneWayNode< T > {rhs, nullptr};
  }
  else
  {
    OneWayNode< T > * element = value_;
    while (element->next != nullptr)
    {
      element = element->next;
    }
    element->next = new OneWayNode< T > {rhs, nullptr};
  }
}

template< typename T >
T turkin::Queue< T >::drop()
{
  if (isEmpty())
  {
    throw std::runtime_error("queue is empty");
  }
  OneWayNode< T > * element = value_;
  value_ = element->next;
  T ret = element->data;
  delete element;
  return ret;
}

template< typename T >
bool turkin::Queue< T >::isEmpty() const
{
  return value_ == nullptr;
}

#endif
