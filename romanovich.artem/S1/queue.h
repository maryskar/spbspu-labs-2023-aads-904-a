#ifndef QUEUE_H
#define QUEUE_H
#include "node.h"
template< typename T >
class Queue {
public:
  Queue();
  ~Queue();
  void push(T rhs);
  T drop();
private:
  Node< T >* head_;
  Node< T >* tail_;
  size_t size_;
};

template < typename T >
T Queue< T >::drop()
{
  return nullptr;
}

template < typename T >
Queue< T >::Queue():
  head_(nullptr),
  tail_(nullptr),
  size_(0)
{
}

template < typename T >
Queue< T >::~Queue()
{
}
#endif
