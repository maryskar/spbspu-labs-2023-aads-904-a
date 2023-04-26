#ifndef STACK_H
#define STACK_H
#include <stdexcept>
#include <iostream>
#include "node.h"
namespace romanovich
{
  template < typename T >
  class Stack
  {
  public:
    Stack();
    Stack(const Stack< T > &stack);
    Stack(Stack< T > &&stack) noexcept;
    ~Stack();
    Stack< T > &operator=(Stack< T > stack);
    Stack< T > &operator=(Stack< T > &&stack) noexcept;
    void push(const T &value);
    void pop();
    T get() const;
    bool isEmpty() const
    {
      return size_ == 0;
    }
  private:
    details::ListNode< T > *top_;
    size_t size_;
    void deleteStack();
    void swapStack(Stack< T > &stack) noexcept;
  };
  template < typename T >
  void Stack< T >::swapStack(Stack< T > &stack) noexcept
  {
    std::swap(top_, stack.head_);
    std::swap(size_, stack.size_);
  }
  template < typename T >
  Stack< T > &Stack< T >::operator=(Stack< T > &&stack) noexcept
  {
    if (this != &stack)
    {
      deleteStack();
      doSwap(stack);
    }
    return *this;
  }
  template < typename T >
  Stack< T > &Stack< T >::operator=(Stack< T > stack)
  {
    doSwap(stack);
    return *this;
  }
  template < typename T >
  Stack< T >::Stack(Stack< T > &&stack) noexcept:
    top_(stack.top_),
    size_(stack.size_)
  {
    stack.top_ = nullptr;
    stack.size_ = 0;
  }
  template < typename T >
  Stack< T >::Stack(const Stack< T > &stack)
  {
    if (stack.top_ == nullptr)
    {
      top_ = nullptr;
      size_ = 0;
    }
    else
    {
      using list_node_tuple = std::tuple < details::ListNode< T > *, details::ListNode< T > * >;
      list_node_tuple *newStack = details::copy(stack.top_);
      top_ = std::get<0>(newStack);
    }
  }
  template < typename T >
  void Stack< T >::deleteStack()
  {
    details::clear(top_);
    top_ = nullptr;
    size_ = 0;
  }
  template < typename T >
  Stack< T >::Stack():
    top_(nullptr),
    size_(0)
  {
  }
  template < typename T >
  Stack< T >::~Stack()
  {
    Stack< T >::deleteStack();
  }
  template < typename T >
  void Stack< T >::push(const T &value)
  {
    if (top_ == nullptr)
    {
      top_ = new details::ListNode< T >{value, nullptr};
    }
    else
    {
      details::ListNode< T > *newNode = new details::ListNode< T >{value, top_};
      top_ = newNode;
    }
    size_++;
  }
  template < typename T >
  T Stack< T >::get() const
  {
    if (isEmpty())
    {
      throw std::range_error("Stack is empty.");
    }
    return top_->data_;
  }
  template < typename T >
  void Stack< T >::pop()
  {
    if (isEmpty())
    {
      throw std::range_error("Stack is empty.");
    }
    details::ListNode< T > *subTop = top_->next_;
    delete top_;
    top_ = subTop;
    size_--;
  }
}
#endif
