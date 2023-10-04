#ifndef STACK_H
#define STACK_H
#include <cstddef>
#include <stdexcept>
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
  friend std::ostream& operator<<(std::ostream& os, const Stack< T >& queue)
  {
    typename Stack< T >::List* current = queue.root_;
    while (current != nullptr)
    {
      os << current->data << " ";
      current = current->next;
    }
    return os;
  }
private:
  struct List
  {
    T data;
    List* next;
  };
  List* root_;
};

template< typename T >
Stack< T >::Stack():
  root_(nullptr)
{}

template< typename T >
Stack< T >::Stack(const Stack< T >& other):
  root_(other.root_)
{}

template< typename T >
Stack< T >::Stack(const Stack< T >&& other):
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
  List* new_node = new List{rhs, nullptr};
  if (new_node == nullptr)
  {
    throw std::bad_alloc();
  }
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
  List* node_temp = root_;
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
  List* current = this->root_;
  while (current->next != nullptr)
  {
    current = current->next;
  }
  List* deep = current;
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
  while (!isEmpty())
  {
    pop();
  }
}
#endif
