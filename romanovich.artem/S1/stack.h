#ifndef STACK_H
#define STACK_H
#include <stdexcept>
#include <iostream>
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
  bool isEmpty()
  {
    return size_ == 0;
  }
  int getSize()
  {
    return size_;
  }
  void print()
  {
    Node< T > *e = top_;
    while (e != nullptr)
    {
      std::cout << e->data_;
      e = e->next_;
    }
    std::cout << "\n";
  }
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
  while (!isEmpty())
  {
    pop();
  }
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
  size_++;
}
template < typename T >
T Stack< T >::pop()
{
  T el = top_->data_;
  Node< T > *subTop = top_->next_;
  delete top_;
  top_ = subTop;
  size_--;
  return el;
}
#endif
