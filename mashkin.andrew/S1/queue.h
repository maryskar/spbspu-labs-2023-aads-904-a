#ifndef QUEUE_H
#define QUEUE_H
#include <cstddef>
#include "list.h"

template< typename T >
class Queue
{
public:
  explicit Queue(T symb);
  void enqueue(T rhs);
  void dequeue();
  T drop();

private:
  list_t< T > head_;
  list_t< T > tail_;
};
#endif
