#ifndef STACK_H
#define STACK_H
#include <stdexcept>

template< typename T >
struct sBox {
  T value_ = 0;
  sBox< T >* prev_ = nullptr;
};

template< typename T >
class Stack {
public:
  Stack();
  ~Stack();
  void push(T rhs);
  T drop();
  bool isEmpty();
private:
  sBox< T >* top_;
};

template< typename T >
Stack< T >::Stack():
top_(nullptr)
{}

template< typename T >
Stack< T >::~Stack()
{
  while (top_->prev_ != nullptr) {
    sBox< T >* next = top_->prev_;
    delete top_;
    top_ = next;
  }
}

template< typename T >
void Stack< T >::push(const T rhs)
{
  top_ = new sBox< T >{rhs, top_};
}

template< typename T >
T Stack< T >::drop()
{
  if (top_ == nullptr) {
    throw std::length_error("Nothing to drop");
  }

  sBox< T >* top = top_->prev_;
  T res = top_->value_;
  delete top_;
  top_ = top;
  return res;
}

template< typename T >
bool Stack< T >::isEmpty()
{
  return top_ == nullptr;
}

#endif
