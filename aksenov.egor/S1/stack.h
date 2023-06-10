#ifndef STACK_H
#define STACK_H
#include "list.h"
namespace aksenov {
  template< typename T >
  class Stack
  {
    public:
      Stack();
      ~Stack();
      void push(const T &val);
      void pop();
      T get();
      bool isEmpty();
    private:
      aksenov::List< T > *top;
  };
}
#endif
