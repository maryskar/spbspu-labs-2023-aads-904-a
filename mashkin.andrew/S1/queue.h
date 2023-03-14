#ifndef QUEUE_H
#define QUEUE_H

template< typename T >
class Queue
{
public:
  void enqueue(T rhs);
  void dequeue();
  T drop();
};
#endif
