#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <cstddef>
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
{}

template< typename T >
void chemodurov::Queue< T >::push(const T & rhs)
{
  last_->next = new List< T >{rhs, nullptr};
  last_ = last_->next;
}

template< typename T >
T & chemodurov::Queue< T >::getFromQueue()
{
  return *head_;
}

#endif
