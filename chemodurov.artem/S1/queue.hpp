#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <cstddef>

namespace chemodurov
{
  template< typename T >
  class Queue
  {
   public:
    Queue(size_t capacity);
    ~Queue();
    void push(const T & rhs);
    void pop();
    T & getFromQueue();
  };
}

#endif