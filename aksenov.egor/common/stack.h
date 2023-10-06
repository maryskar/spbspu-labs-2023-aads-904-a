#ifndef STACK_H
#define STACK_H
#include <stdexcept>
#include <List.h>
namespace aksenov
{
  template< typename T >
  class Stack
  {
    public:
      explicit Stack();
      Stack(const Stack< T > &other);
      Stack(Stack< T > &&other) noexcept;
      Stack< T > &operator=(const Stack< T > &other);
      Stack< T > &operator=(Stack< T > &&other) noexcept;
      ~Stack();
      void push(const T &val);
      void pop();
      void clear(Stack< T > &other);
      T get() const;
      bool isEmpty() const;
      size_t size() const;
    private:
      listT< T > *top_;
      size_t size_;
  };

  template< typename T >
  Stack< T >::Stack():
    top_(nullptr),
    size_(0)
  {}

  template< typename T >
  Stack< T >::~Stack()
  {
    free(top_);
    size_ = 0;
  }

  template< typename T>
  size_t Stack< T >::size() const
  {
    return size_;
  }

  template< typename T >
  void Stack< T >::clear(Stack< T > &other)
  {
    while(!isEmpty())
    {
      pop();
    }
    std::swap(top_, other.top_);
    std::swap(size_, other.size_);
  }
  template< typename T >
  bool Stack< T >::isEmpty() const
  {
    return (top_ == nullptr);
  }

  template< typename T >
  void Stack< T >::push(const T &val)
  {
    listT< T > *newTop = new listT< T >(val, top_);
    top_ = newTop;
    size_++;
  }

  template< typename T >
  T Stack< T >::get() const
  {
    if (isEmpty())
    {
      throw std::logic_error("Empty stack");
    }
    return top_->data;
  }

  template< typename T >
  void Stack< T >::pop()
  {
    if (isEmpty())
    {
      throw std::logic_error("empty stack");
    }
    auto todel = top_;
    top_ = top_->next;
    delete todel;
    size_--;
  }

  template< typename T >
  Stack< T >::Stack(const Stack< T > &other):
    top_(nullptr),
    size_(0)
  {
    listT< T > *cur = other.top_;
    while (cur)
    {
      push(cur->data);
      cur = cur->next;
    }
  }

  template < typename T >
  Stack< T > &Stack< T >::operator=(const Stack< T > &other)
  {
    if (this == other)
    {
      return *this;
    }
    clear(other);
    listT< T > cur = other.top_;
    while (cur)
    {
      push(cur->data);
      cur = cur.next;
    }
    return *this;
  }

  template < typename T >
  Stack< T >::Stack(Stack< T > &&other) noexcept:
    top_(other.top_),
    size_(other.size_)
  {
    other.top_ = nullptr;
    other.size_ = 0;
  }

  template < typename T >
  Stack< T > &Stack< T >::operator=(Stack< T > &&other) noexcept
  {
    if (this == &other)
    {
      return *this;
    }
    clear(other);
    return *this;
  }
}
#endif
