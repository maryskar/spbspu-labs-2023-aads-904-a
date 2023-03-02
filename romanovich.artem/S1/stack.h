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
  Node< T > *top_;
private:
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
template < typename T >
void Stack< T >::push(const T &value)
{
  if (top_ == nullptr)
  {
    top_ = new Node< T >{value, nullptr};
  }
  else
  {
    Node< T > *newNode = new Node< T >{value, top_};
    top_ = newNode;
  }
}
template < typename T >
T Stack< T >::pop()
{
  T el = top_->data_;
  Node< T > *subTop = top_->next_;
  delete top_;
  top_ = subTop;
  return el;
}
#endif
