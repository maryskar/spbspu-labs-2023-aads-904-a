#ifndef STACK_H
#define STACK_H

#include "node.h"
template< typename T >
class Stack
{
public:
 void push(T& rhs); // наверх
 T& drop(); // сверху
private:
  Node<T>* top_;
};
#endif
