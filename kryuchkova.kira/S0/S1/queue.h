#ifndef QUEUE_H
#define QUEUE_H

template< typename T >
class Queue
{
  public:
    Queue():
      begin_(nullptr),
      end_(nullptr)
    {}
    Queue()
    void push(T rhs);
    T drop();
};

#endif
