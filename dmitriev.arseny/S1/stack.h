#ifndef STACK_H
#define STACK_H

#include "list.h"
#include <iomanip>

template< typename T >
class Stack
{
public:
  Stack();
  ~Stack();

  Stack(const Stack< T >& otherStack);
  Stack(Stack< T >&& otherStack) noexcept;

  Stack< T >& operator=(const Stack< T >& otherStack);
  Stack< T >& operator=(Stack< T >&& otherStack) noexcept;

  void push(const T& rhs);
  void popBack();
  T getTopData() const;

  bool isEmpty() const;

private:
  List< T >* top;

};

template< typename T >
Stack< T >::Stack():
  top(nullptr)
{

}

template< typename T >
Stack< T >::~Stack()
{
  clear(top);
}

template< typename T >
Stack< T >::Stack(const Stack< T >& otherStack):
  top(nullptr)
{
  if (otherStack.top != nullptr)
  {
    List< T >* otherTop = otherStack.top;
    List< T >* stackTail = nullptr;

    push(otherTop->data);
    stackTail = top;
    otherTop = otherTop->otherList;

    while (otherTop != nullptr)
    {
      try
      {
        stackTail->otherList = new List< T >(otherTop->data);
      }
      catch (const std::exception&)
      {
        clear(top);
        throw;
      }
      stackTail = stackTail->otherList;
      otherTop = otherTop->otherList;
    }
  }
}

template< typename T >
Stack< T >::Stack(Stack< T >&& otherStack) noexcept:
  top(otherStack.top)
{
  otherStack.top = nullptr;
}

template< typename T >
Stack< T >& Stack< T >::operator=(const Stack& otherStack)
{
  if (this == &otherStack)
  {
    return *this;
  }
  Stack< T > newStack(otherStack);
  clear(top);
  top = newStack.top;
  newStack.top = nullptr;

  return *this;
}

template< typename T >
inline Stack< T >& Stack< T >::operator=(Stack< T >&& otherStack) noexcept
{
  if (this == &otherStack)
  {
    return *this;
  }
  clear(top);
  top = otherStack.top;
  otherStack.top = nullptr;

  return *this;
}

template< typename T >
void Stack< T >::push(const T& rhs)
{
  List< T >* newTop = new List< T >(rhs, top);
  top = newTop;
}

template< typename T >
void Stack< T >::popBack()
{
  if (isEmpty())
  {
    throw std::underflow_error("underflow_error");
  }
  List< T >* currentList = top;
  top = top->otherList;

  delete currentList;
}

template< typename T >
T Stack< T >::getTopData() const
{
  if (isEmpty())
  {
    throw std::underflow_error("underflow_error");
  }
  return top->data;
}

template< typename T >
bool Stack< T >::isEmpty() const
{
  return top == nullptr;
}

#endif
