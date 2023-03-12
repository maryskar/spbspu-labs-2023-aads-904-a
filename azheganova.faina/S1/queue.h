#ifndef QUEUE_H
#define QUEUE_H

template< typename T >
class Queue
{
public:
  Queue();
  ~Queue();
  void push(T rhs);
  T drop;
  bool isEmpty();
};

#endif
