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
  const T& top() const;
  void pop();
  const T& deep() const;
  bool isEmpty() const;
  ~Stack();
private:
  List< T >* root_;
};

template< typename T >
Stack< T >::Stack() :
  root_(nullptr)
{}

template< typename T >
Stack< T >::Stack(const Stack< T >& other):
  root_(other.root_)
{}

template< typename T >
Stack< T >::Stack(const Stack< T >&& other) :
  root_(other.root_)
{
  other.root_ = nullptr;
}

template <class T>
const T& Stack< T >::top() const
{
  if (isEmpty())
  {
    throw std::runtime_error("Stack is empty");
  }
  return root_->data;
}

template< typename T>
void Stack< T >::push(const T& rhs)
{
  List< T >* new_node = new List< T >{rhs, nullptr};
  new_node->data = rhs;
  new_node->next = root_;
  root_ = new_node;
}

template< typename T >
void Stack< T >::pop()
{
  if (isEmpty())
  {
    throw std::out_of_range("Stack is empty");
  }
  List< T >* node_temp = root_;
  root_ = node_temp->next;
  delete node_temp;
}

template< typename T >
const T& Stack< T >::deep() const
{
  if (isEmpty())
  {
    throw std::logic_error("Empty");
  }
  List< T >* current = this->root_;
  while (current->next != nullptr)
  {
    current = current->next;
  }
  List< T >* deep = current;
  return deep->data;
}

template< typename T >
bool Stack< T >::isEmpty() const
{
  return root_ == nullptr;
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
