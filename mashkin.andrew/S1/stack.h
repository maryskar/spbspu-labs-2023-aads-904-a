#ifndef STACK_H
#define STACK_H
#include <cstddef>

template< typename T >
class Stack
{
public:
  explicit Stack();
  void push(T rhs);
  void pop();
  bool isEmpty() const;
  T drop();
private:
  T* stack_;
  size_t top_[50];
};
#endif
