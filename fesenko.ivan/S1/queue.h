#ifndef QUEUE_H
#define QUEUE_H
#include "list.h"
namespace fesenko
{
  template< typename T >
  class Queue
  {
   public:
    Queue();
    ~Queue();
    void push(const T rhs);
    T &getOutOfQueue();
    void pop();
    bool isEmpty();
   private:
    List< T > *head_;
    List< T > *tail_;
  };
}

template< typename T >
fesenko::Queue< T >::Queue():
  head_(nullptr),
  tail_(nullptr)
{}
#endif
