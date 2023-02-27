#ifndef STACK_H
#define STACK_H
#include <stdexcept>
#include "node.h"
template < typename T >
class Stack
{
public:
  Stack();
  ~Stack();
  void push(const T &value);
  T pop();
private:
  Node< T >* top_;
  size_t size_;
};
template < typename T >
Stack< T >::Stack():
  top_(nullptr),
  size_(0)
{
}
template < typename T >
Stack< T >::~Stack()
{
  //delete ;
}
#endif
