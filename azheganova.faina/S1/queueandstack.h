#ifndef QUEUEANDSTACK_H
#define QUEUEANDSTACK_H

template< typename T >
class Queue
{
public:
  void push(T rhs);
  T drop;
};

template< typename T >
class Stack 
{
public:
  void push(T rhs);
  T drop;
};


#endif