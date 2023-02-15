#ifndef QUEUE_H
#define QUEUE_H
#include "node.h"

template< typename T>
class Queue
{
public:
 void push(T& rhs); // в конец
 T& drop();  // из начала
private:
  Node<T>* head;
};

#endif
