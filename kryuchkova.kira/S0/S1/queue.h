#ifndef QUEUE_H
#define QUEUE_H

template< typename T >
class Queue
{
  public:
    void push(T rhs);
    T drop();
};

#endif
