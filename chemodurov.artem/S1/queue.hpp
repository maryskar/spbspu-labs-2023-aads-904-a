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
    size_t size_;
  };
}

template< typename T >
chemodurov::Queue< T >::Queue():
 head_(nullptr),
 size_(0)
{}

#endif
