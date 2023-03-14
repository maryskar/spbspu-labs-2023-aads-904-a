#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>
#include "oneway-list.h"

template< typename T >
class Queue
{
  public:
    Queue();
    ~Queue();
    void push(const T & rhs);
    T drop();
    bool isEmpty() const;
  private:
    OneWayList< T > * value_;
};

template< typename T >
Queue< T >::Queue():
  value_(nullptr)
{}

template< typename T >
Queue< T >::~Queue()
{
  while (value_ != nullptr)
  {
    OneWayList< T > * element = value_;
    value_ = value_->next;
    delete element;
  }
}

template< typename T >
void Queue< T >::push(const T & rhs)
{
  if (isEmpty())
  {
    value_ = new OneWayList< T > {rhs, nullptr};
  }
  else
  {
    OneWayList< T > * element = value_;
    while (element->next != nullptr)
    {
      element = element->next;
    }
    element->next = new OneWayList< T > {rhs, nullptr};
  }
}

template< typename T >
T Queue< T >::drop()
{
  if (isEmpty())
  {
    throw std::runtime_error("queue is empty");
  }
  OneWayList< T > * element = value_;
  value_ = element->next;
  T ret = element->data;
  delete element;
  return ret;
}

template< typename T >
bool Queue< T >::isEmpty() const
{
  return value_ == nullptr;
}

#endif
