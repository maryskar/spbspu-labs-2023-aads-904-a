#ifndef STACK_H
#define STACK_H
#include <stdexcept>
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
    T &top();
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
  deleteList(head_);
}

template< typename T >
void fesenko::Stack< T >::push(const T &rhs)
{
  List< T > *temp = new List< T >{rhs, head_};
  head_ = temp;
}

template< typename T >
T &fesenko::Stack< T >::top()
{
  if (isEmpty()) {
    throw std::out_of_range("Stack is empty");
  }
  return (*head_).data;
}

template< typename T >
void fesenko::Stack< T >::pop()
{
  if (isEmpty()) {
    throw std::out_of_range("Stack is empty");
  }
  List< T > *temp = head_->next;
  delete head_;
  head_ = temp;
}

template< typename T >
bool fesenko::Stack< T >::isEmpty()
{
  return head_ == nullptr;
}
#endif
