#include "stack.h"

template< typename T >
Stack< T >::Stack():
  top_(nullptr),
  size(0)
{}

template< typename T >
Stack< T >::~Stack()
{
  while (top_ != nullptr)
  {
    ListNode< T > * temp = top_->next;
    delete top_;
    top_ = tmp;
  }
}

template< typename T >
void Stack< T >::push(const T & rhs)
{
  ListNode< T > * temp = new ListNode(rhs);
  temp->next = top_;
  top_ = temp;
  size++;
}

template< typename T >
void Stack< T >::pop()
{
  if (isEmpty())
  {
    throw std::logic_error("stack is empty");
  }
  int value = top_->data_;
  ListNode< T > * temp = top_;
  top_ = top_->next_;
  delete temp;
  size--;
  return value;
}

template< typename T >
bool Stack< T >::isEmpty()
{
  return top_;
}

template< typename T >
int Stack< T >::getSize()
{
  return size;
}

template< typename T >
T Stack< T >::drop()
{
  return top_->data_;
}
