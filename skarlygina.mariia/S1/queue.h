#ifndef QUEUE_H
#define QUEUE_H
#include "node.h"
template< typename T >
class Queue
{
public:
  Queue();
  void push(T rhs);
  T drop();
  ~Queue();
private:
  Node< T >* head;
};
#endif
