#ifndef STACK_H
#define STACK_H
#include <stdexcept>
#include "List.h"
namespace timofeev
{
  template <typename T>
  class Stack
  {
  public:
    explicit Stack();
    ~Stack();
    void push(const T& rhs);
    void pop();
    T& drop();
    const T& drop() const;
    bool isEmpty() const;
  private:
    List< T >* top_;
  };
}

#endif