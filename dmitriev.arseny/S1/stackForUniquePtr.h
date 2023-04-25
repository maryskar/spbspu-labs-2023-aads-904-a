#ifndef STACKFORUNIQUEPTR_H
#define STACKFORUNIQUEPTR_H

#include "stack.h"
#include "listForUniquePtr.h"
#include "mathExprPtr.h"


template<>
class Stack< MathExprPtr >
{
public:
  Stack();
  ~Stack();

  Stack(const Stack< MathExprPtr >& otherStack);
  Stack(Stack< MathExprPtr >&& otherStack) noexcept;

  Stack< MathExprPtr >& operator=(const Stack< MathExprPtr >& otherStack);
  Stack< MathExprPtr >& operator=(Stack< MathExprPtr >&& otherStack) noexcept;

  void push(MathExprPtr& rhs);//name
  void popBack();
  MathExprPtr getTopData() const;

  bool isEmpty() const;

private:
  List< MathExprPtr >* top;

};

Stack< MathExprPtr >::Stack() :
  top(nullptr)
{

}

Stack< MathExprPtr >::~Stack()
{
  clear(top);
}

Stack< MathExprPtr >::Stack(const Stack< MathExprPtr >& otherStack) :
  top(nullptr)
{
  if (otherStack.top != nullptr)
  {
    List< MathExprPtr >* otherTop = otherStack.top;
    List< MathExprPtr >* stackTail = nullptr;

    push(otherTop->data);
    stackTail = top;
    otherTop = otherTop->otherList;

    while (otherTop != nullptr)
    {
      try
      {
        stackTail->otherList = new List< MathExprPtr >(otherTop->data);
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

Stack< MathExprPtr >::Stack(Stack< MathExprPtr >&& otherStack) noexcept :
  top(otherStack.top)
{
  otherStack.top = nullptr;
}

Stack< MathExprPtr >& Stack< MathExprPtr >::operator=(const Stack& otherStack)
{
  if (this == &otherStack)
  {
    return *this;
  }
  Stack< MathExprPtr > newStack(otherStack);
  clear(top);
  top = newStack.top;
  newStack.top = nullptr;

  return *this;
}

inline Stack< MathExprPtr >& Stack< MathExprPtr >::operator=(Stack< MathExprPtr >&& otherStack) noexcept
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

void Stack< MathExprPtr >::push(MathExprPtr& rhs)
{
  List< MathExprPtr >* newTop = new List< MathExprPtr >(rhs, top);
  top = newTop;
}

void Stack< MathExprPtr >::popBack()
{
  if (isEmpty())
  {
    throw std::underflow_error("underflow_error");
  }
  List< MathExprPtr >* currentList = top;
  top = top->otherList;

  delete currentList;
}

MathExprPtr Stack< MathExprPtr >::getTopData() const
{
  if (isEmpty())
  {
    throw std::underflow_error("underflow_error");
  }
  return std::move(top->data);
}

bool Stack< MathExprPtr >::isEmpty() const
{
  return top == nullptr;
}


#endif // !STACKFU_H
