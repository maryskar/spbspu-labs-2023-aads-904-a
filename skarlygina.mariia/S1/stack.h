#ifndef STACK_H
#define STACK_H
#include <cstddef>
#include <stdexcept>
#include "list.h"
template< typename T >
class Stack
{
public:
  Stack();
  Stack(const Stack< T >& other);
  Stack(const Stack< T >&& other);
  void push(const T& rhs);
  T& get() const;
  T& top() const;
  void pop();
  bool isEmpty() const;
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
  head_(other.head_),
  tail_(other.tail_)
{}

template< typename T >
Stack< T >::Stack(const Stack< T >&& other) :
  head_(other.head_),
  tail_(other.tail_)
{
  other.head_ = nullptr;
  other.tail_ = nullptr;
}

template <class T>
T& Stack< T >::top() const
{
  if (isEmpty())
  {
    throw std::runtime_error("Stack is empty");
  }
  return head_->data;
}

template< typename T>
void Stack< T >::push(const T& rhs)
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
T& Stack< T >::get() const
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

template< typename T >
bool Stack< T >::isEmpty() const
{
  return head_ == nullptr;
}

template< typename T>
Stack< T >::~Stack()
{
  while (head_ != nullptr)
  {
    pop();
  }
}
#endif
