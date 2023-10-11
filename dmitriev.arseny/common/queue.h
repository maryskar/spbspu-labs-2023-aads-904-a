#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"

namespace dmitriev
{
  template< typename T >
  class Queue
  {
  public:
    Queue();
    ~Queue();

    Queue(const Queue< T >& otherQueue);
    Queue(Queue< T >&& otherQueue) noexcept;

    Queue< T >& operator=(const Queue< T >& otherQueue);
    Queue< T >& operator=(Queue< T >&& otherQueue) noexcept;

    void push(const T& inp);
    void push(T&& inp);

    void popBack();
    T& getTopData();
    const T& getConstTopData() const;

    bool isEmpty() const;

  private:
    std::pair< dmitriev::List< T >*, dmitriev::List< T >* > m_ptrPairHT;

  };
}

template< typename T >
dmitriev::Queue< T >::Queue():
  m_ptrPairHT{nullptr, nullptr}
{}

template< typename T >
dmitriev::Queue< T >::~Queue()
{
  clear(m_ptrPairHT.first);
}

template< typename T >
dmitriev::Queue< T >::Queue(const dmitriev::Queue< T >& otherQueue):
  m_ptrPairHT(dmitriev::copy(otherQueue.m_ptrPairHT.first))
{}

template< typename T >
dmitriev::Queue< T >::Queue(Queue< T >&& otherQueue) noexcept:
  m_ptrPairHT(otherQueue.m_ptrPairHT)
{
  otherQueue.m_ptrPairHT.first = nullptr;
  otherQueue.m_ptrPairHT.second = nullptr;
}

template< typename T >
dmitriev::Queue< T >& dmitriev::Queue< T >::operator=(const Queue< T >& otherQueue)
{
  if (this == std::addressof(otherQueue))
  {
    return *this;
  }
  Queue< T > newQueue(otherQueue);
  *this = std::move(newQueue);

  return *this;
}

template< typename T >
dmitriev::Queue< T >& dmitriev::Queue< T >::operator=(Queue< T >&& otherQueue) noexcept
{
  if (this == std::addressof(otherQueue))
  {
    return *this;
  }
  clear(m_ptrPairHT.first);
  m_ptrPairHT.first = otherQueue.m_ptrPairHT.first;
  m_ptrPairHT.second = otherQueue.m_ptrPairHT.second;

  otherQueue.m_ptrPairHT.first = nullptr;
  otherQueue.m_ptrPairHT.second = nullptr;

  return *this;
}

template< typename T >
void dmitriev::Queue< T >::push(const T& rhs)
{
  if (m_ptrPairHT.first == nullptr)
  {
    m_ptrPairHT.first = new List< T >{rhs};
    m_ptrPairHT.second = m_ptrPairHT.first;
  }
  else
  {
    m_ptrPairHT.second->next = new List< T >{rhs};
    m_ptrPairHT.second = m_ptrPairHT.second->next;
  }
}

template< typename T >
void dmitriev::Queue< T >::push(T&& inp)
{
  if (m_ptrPairHT.first == nullptr)
  {
    m_ptrPairHT.first = new List< T >{std::move(inp), nullptr};
    m_ptrPairHT.second = m_ptrPairHT.first;
  }
  else
  {
    m_ptrPairHT.second->next = new List< T >{std::move(inp), nullptr};
    m_ptrPairHT.second = m_ptrPairHT.second->next;
  }
}

template< typename T >
void dmitriev::Queue< T >::popBack()
{
  if (m_ptrPairHT.first == nullptr)
  {
    throw std::runtime_error("runtime_error");
  }
  List< T >* newHead = m_ptrPairHT.first->next;
  delete m_ptrPairHT.first;

  m_ptrPairHT.first = newHead;
}

template< typename T >
T& dmitriev::Queue< T >::getTopData()
{
  if (m_ptrPairHT.first == nullptr)
  {
    throw std::runtime_error("runtime_error");
  }
  return m_ptrPairHT.first->data;
}

template< typename T >
const T& dmitriev::Queue< T >::getConstTopData() const
{
  if (m_ptrPairHT.first == nullptr)
  {
    throw std::runtime_error("runtime_error");
  }
  return m_ptrPairHT.first->data;
}

template< typename T >
bool dmitriev::Queue< T >::isEmpty() const
{
  return m_ptrPairHT.first == nullptr;
}

#endif
