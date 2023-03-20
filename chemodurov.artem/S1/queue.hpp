#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <cstddef>
#include <stdexcept>
#include "list.hpp"

namespace chemodurov
{
  template< typename T >
  class Queue
  {
   public:
    Queue();
    ~Queue();
    void push(const T & rhs);
    void pop();
    T & getFromQueue();
    bool empty() const noexcept;
   private:
    List< T > * head_;
    List< T > * last_;
  };
}

template< typename T >
chemodurov::Queue< T >::Queue():
 head_(nullptr),
 last_(nullptr)
{}

template< typename T >
chemodurov::Queue< T >::~Queue()
{
  while (head_)
  {
    List< T > * temp = head_->next;
    delete head_;
    head_ = temp;
  }
}

template< typename T >
void chemodurov::Queue< T >::push(const T & rhs)
{
  if (last_)
  {
    last_->next = new List< T >{rhs, nullptr};
    last_ = last_->next;
  }
  else
  {
    last_ = new List< T >{rhs, nullptr};
    head_ = last_;
  }
}

template< typename T >
T & chemodurov::Queue< T >::getFromQueue()
{
  if (!head_)
  {
    throw std::logic_error("Empty queue");
  }
  return (*head_).data;
}

template< typename T >
void chemodurov::Queue< T >::pop()
{
  if (!head_)
  {
    throw std::logic_error("Empty queue");
  }
  List< T > * temp = head_->next;
  delete head_;
  head_ = temp;
}

template< typename T >
bool chemodurov::Queue< T >::empty() const noexcept
{
  return head_ == nullptr;
}

#endif
