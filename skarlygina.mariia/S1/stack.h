#ifndef STACK_H
#define STACK_H
#include "list.h"
template< typename T >
class Stack
{
public:
  Stack();
  Stack(const Stack< T >& other);
  void push(T rhs);
  T get();
  void pop();
  ~Stack();
private:
  List< T >* head_;
  List< T >* tail_;
};

template< typename T >
Stack< T >::Stack() :
  head_(nullptr),
  tail_(nullptr)
{}

template< typename T >
Stack< T >::Stack(const Stack< T >& other):
  head_(nullptr),
  tail_(nullptr)
{
  if (other.head_ == nullptr)
  {
    return;
  }
  List< T >* head_temp = other.head_;
  while (head_temp != nullptr)
  {
    push(head_temp->data);
    head_temp = head_temp->next;
  }
}

template< typename T>
void Stack< T >::push(T rhs)
{
  List< T >* new_node = new List< T >{rhs, nullptr, nullptr};
  if (head_ == nullptr)
  {
    head_ = new_node;
    tail_ = new_node;
  }
  else
  {
    new_node->prev = tail_;
    tail_->next = new_node;
    tail_ = new_node;
  }
}

template< typename T >
T Stack< T >::get()
{
  if (tail_ == nullptr)
  {
    throw std::out_of_range("Stack is empty");
  }
  return tail_->data;
}

template< typename T >
void Stack< T >::pop()
{
  if (tail_ == nullptr)
  {
    throw std::out_of_range("Stack is empty");
  }
  List< T >* node_temp = tail_;
  tail_ = tail_->prev;
  if (tail_ != nullptr)
  {
    tail_->next = nullptr;
  }
  else
  {
    head_ = nullptr;
  }
  delete node_temp;
}
#endif