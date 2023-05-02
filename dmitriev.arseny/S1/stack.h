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

  void push(const T& data);
  void push(T&& data);

  void popBack();
  T& getTopData();

  bool isEmpty() const;

private:
  List< T >* top;

};

template< typename T >
Stack< T >::Stack():
  top(nullptr)
{}

template< typename T >
Stack< T >::~Stack()
{
  clear(top);
}

template< typename T >
Stack< T >::Stack(const Stack< T >& otherStack):
  top(copyStack(otherStack.top))
{}

template< typename T >
List< T >* copyStack(List< T >* otherTop)
{
  if (otherTop == nullptr)
  {
    return nullptr;
  }
  List< T >* stackTop = nullptr;
  List< T >* stackTail = nullptr;

  stackTop = new List< T >{otherTop->data};
  stackTail = stackTop;
  otherTop = otherTop->otherList;

  while (otherTop != nullptr)
  {
    try
    {
      stackTail->otherList = new List< T >{otherTop->data};
    }
    catch (const std::exception&)
    {
      clear(stackTop);
      throw;
    }
    stackTail = stackTail->otherList;
    otherTop = otherTop->otherList;
  }

  return stackTop;
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
  if (this == std::addressof(otherStack))
  {
    return *this;
  }
  Stack< T > newStack(otherStack);
  clear(top);
  *this = std::move(newStack);

  return *this;
}

template< typename T >
Stack< T >& Stack< T >::operator=(Stack< T >&& otherStack) noexcept
{
  if (this == std::addressof(otherStack))
  {
    return *this;
  }
  clear(top);
  top = otherStack.top;
  otherStack.top = nullptr;

  return *this;
}

template< typename T >
void Stack< T >::push(const T& data)
{
  List< T >* newTop = new List< T >{data, top};
  top = newTop;
}

template< typename T >
void Stack< T >::push(T&& data)
{
  List< T >* newTop = new List< T >{std::move(data), top};
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
T& Stack< T >::getTopData()
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
