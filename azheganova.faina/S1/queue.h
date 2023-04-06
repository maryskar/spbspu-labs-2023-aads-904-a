#ifndef QUEUE_H
#define QUEUE_H
#include "node.h"

template< typename T >
class Queue
{
public:
  Queue();
  ~Queue();
  void push(const T & rhs);
  T pop();
  bool isEmpty();
private:
  ListNode< T > * top_;
  ListNode< T > * last_;
};

#endif
