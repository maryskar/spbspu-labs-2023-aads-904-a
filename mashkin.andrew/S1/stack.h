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
  static const size_t OVERFLOW = 50;
  T* stack_[OVERFLOW];
  size_t top_;
};
#endif
