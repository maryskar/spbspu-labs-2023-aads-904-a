#ifndef STACK_H
#define STACK_H
#include "list.h"
namespace fesenko
{
  template< typename T >
  class Stack
  {
   public:
    Stack();
    ~Stack();
    void push(const T &rhs);
    T &getOutOfStack();
    void pop();
   private:
    List< T > *head_;
  };
}

template< typename T >
fesenko::Stack< T >::Stack():
  head_(nullptr)
{}

template< typename T >
fesenko::Stack< T >::~Stack()
{
  while (head_) {
    List< T > *temp = head_->next;
    delete head_;
    head_ = temp;
  }
}

template < typename T >
void fesenko::stack< T >::push(const T &rhs)
{
  List< T > *temp = new List< T >{rhs, head_};
  head_ = temp;
}
#endif
