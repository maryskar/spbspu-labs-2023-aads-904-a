#ifndef STACK_HPP
#define STACK_HPP
#include "list.hpp"
#include <cstddef> 

template< typename T >
class Stack
{
  public:
    Stack();
    ~Stack();
    void push(const T& value);
    void popOutOfTheStack();
    T& getInStack();
    bool isEmpty() const;
  private:
    List< T >* value_;
    size_t size_;
};

template< typename T>
Stack< T >::Stack():
  value_(nullptr),
  size_(0)
{
}
#endif
