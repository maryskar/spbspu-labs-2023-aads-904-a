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
    bool isEmpty();
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

template< typename T >
void fesenko::Stack< T >::push(const T &rhs)
{
  List< T > *temp = new List< T >{rhs, head_};
  head_ = temp;
}

template< typename T >
T &fesenko::Stack< T >::getOutOfStack()
{
  if (isEmpty()) {
    throw std::out_of_range("List is empty");
  }
  return *head_.data;
}

template< typenamt T >
void fesenko::Stack< T >::pop()
{
  if (isEmpty()) {
    throw std::out_of_range("List is empty");
  }
  List< T > *temp = head_->next;
  delete head_;
  head_ = temp;
}

template < typename T >
bool fesenko::Stack< T >::isEmpty()
{
  return head_ == nullptr;
}
#endif
