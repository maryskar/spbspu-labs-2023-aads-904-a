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
  size_t size;
};

template< typename T >
Stack< T >::Stack() :
  root_(nullptr),
  size(0)
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
  const int MAX_SIZE = 100;
  if (size >= MAX_SIZE)
  {
    throw std::overflow_error("Stack is full");
  }
  List< T >* new_node = new List< T >{rhs, nullptr};
  if (new_node == nullptr)
  {
    throw std::bad_alloc();
  }
  new_node->data = rhs;
  new_node->next = root_;
  root_ = new_node;
  size++;
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
    throw std::logic_error("Stack is empty");
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
  while (root_ != nullptr)
  {
    List< T >* node_temp = root_;
    root_ = root_->next;
    delete node_temp;
  }
}
#endif
