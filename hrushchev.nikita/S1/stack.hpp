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
    void popOutOfTheStack();
    T& getInStack();
    bool isEmpty() const;
  private:
    List< T >* value_;
};

#endif
