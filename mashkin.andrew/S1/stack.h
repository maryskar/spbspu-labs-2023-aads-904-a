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

  Stack* operator[](size_t id) const;
  Stack* at(size_t id) const;
private:
  static const size_t OVERFLOW = 50;
  T* stack_[OVERFLOW];
  size_t top_;
};
#endif
