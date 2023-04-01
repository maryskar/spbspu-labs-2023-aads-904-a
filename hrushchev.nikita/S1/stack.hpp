#ifndef STACK_HPP
#define STACK_HPP
#include "list.hpp"

template< typename T >
class Stack
{
  public:
    Stack();
    ~Stack();
    void push(const T& value);
    void pop();
    T& get();
    bool isEmpty() const;
  private:
    List< T >* value_;
};

template< typename T >
Stack< T >::Stack():
  value_(nullptr)
{
}

template< typename T >
bool Stack< T >::isEmpty() const
{
  return (value_ == nullptr);
}



#endif
