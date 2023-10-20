#ifndef STACK_H
#define STACK_H
#include <cstddef>
#include <stdexcept>
namespace skarlygina
{
  template< typename T >
  class Stack
  {
  public:
    Stack();
    Stack(const Stack< T >& other);
    Stack(Stack< T >&& other);
    Stack< T >& operator=(const Stack< T >& other);
    Stack< T >& operator=(Stack< T >&& other);
    void push(const T& rhs);
    const T& top() const;
    void pop();
    const T& deep() const;
    bool isEmpty() const;
    ~Stack();
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
    root_(nullptr)
  {
    List< T >* current = other.root_;
    while (current)
    {
      push(current->data);
      current = current->next;
    }
  }

  template< typename T >
  Stack< T >::Stack(Stack< T >&& other):
    root_(other.root_)
  {
    other.root_ = nullptr;
  }

  template< typename T >
  Stack< T >& Stack< T >::operator=(const Stack< T >& other)
  {
    if (this != std::addressof(other))
    {
      Stack< T > temp(other);
      std::swap(root_, temp.root_);
    }
    return *this;
  }

  template< typename T >
  Stack< T >& Stack< T >::operator=(Stack< T >&& other)
  {
    if (this != std::addressof(other))
    {
      root_ = std::move(other.root_);
    }
    return *this;
  }

  template < typename T >
  const T& Stack< T >::top() const
  {
    if (isEmpty())
    {
      throw std::runtime_error("Stack is empty");
    }
    return root_->data;
  }

  template< typename T >
  void Stack< T >::push(const T& rhs)
  {
    try
    {
      List* new_node = new List{rhs, nullptr};
    }
    catch (const std::bad_alloc& e)
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
}
#endif
