#ifndef STACK_H
#define STACK_H

#include "list.h"

namespace
{
  template< typename T >
  dmitriev::List< T >* copyStack(dmitriev::List< T >* otherTop)
  {
    std::pair< dmitriev::List< T >*, dmitriev::List< T >* > headTail;
    headTail = dmitriev::copy(otherTop);

    return headTail.first;
  }
}

namespace dmitriev
{
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
    const T& getConstTopData() const;

    bool isEmpty() const;

  private:
    List< T >* m_top;

  };
}
template< typename T >
dmitriev::Stack< T >::Stack():
  m_top(nullptr)
{}

template< typename T >
dmitriev::Stack< T >::~Stack()
{
  clear(m_top);
}

template< typename T >
dmitriev::Stack< T >::Stack(const Stack< T >& otherStack):
  m_top(copyStack(otherStack.m_top))
{}

template< typename T >
dmitriev::Stack< T >::Stack(Stack< T >&& otherStack) noexcept:
  m_top(otherStack.m_top)
{
  otherStack.m_top = nullptr;
}

template< typename T >
dmitriev::Stack< T >& dmitriev::Stack< T >::operator=(const Stack& otherStack)
{
  if (this == std::addressof(otherStack))
  {
    return *this;
  }
  Stack< T > newStack(otherStack);
  *this = std::move(newStack);

  return *this;
}

template< typename T >
dmitriev::Stack< T >& dmitriev::Stack< T >::operator=(Stack< T >&& otherStack) noexcept
{
  if (this == std::addressof(otherStack))
  {
    return *this;
  }
  clear(m_top);
  m_top = otherStack.m_top;
  otherStack.m_top = nullptr;

  return *this;
}

template< typename T >
void dmitriev::Stack< T >::push(const T& data)
{
  List< T >* newTop = new List< T >{data, m_top};
  m_top = newTop;
}

template< typename T >
void dmitriev::Stack< T >::push(T&& data)
{
  List< T >* newTop = new List< T >{std::move(data), m_top};
  m_top = newTop;
}

template< typename T >
void dmitriev::Stack< T >::popBack()
{
  if (isEmpty())
  {
    throw std::runtime_error("runtime_error");
  }
  List< T >* currentList = m_top;
  m_top = m_top->otherList;

  delete currentList;
}

template< typename T >
T& dmitriev::Stack< T >::getTopData()
{
  if (isEmpty())
  {
    throw std::runtime_error("runtime_error");
  }
  return m_top->data;
}

template< typename T >
const T& dmitriev::Stack< T >::getConstTopData() const
{
  if (isEmpty())
  {
    throw std::runtime_error("runtime_error");
  }
  return m_top->data;
}

template< typename T >
bool dmitriev::Stack< T >::isEmpty() const
{
  return m_top == nullptr;
}

#endif
