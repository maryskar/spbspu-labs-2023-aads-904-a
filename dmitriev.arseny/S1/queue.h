#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"
#include <iomanip>

namespace dmitriev
{
  template< typename T >
  struct Pair
  {
    List< T >* head;
    List< T >* tail;
  };
}
namespace
{
  template< typename T >
  dmitriev::Pair< T > copyQueue(dmitriev::List< T >* otherHead)
  {
    if (otherHead == nullptr)
    {
      return dmitriev::Pair< T >{nullptr, nullptr};
    }
    dmitriev::List< T >* newHead = new dmitriev::List< T >{ otherHead->data };
    dmitriev::List< T >* newTail = newHead;
    otherHead = otherHead->otherList;

    while (otherHead != nullptr)
    {
      newTail = newTail->otherList;
      try
      {
        newTail = new dmitriev::List< T >{ otherHead->data };
      }
      catch (const std::exception&)
      {
        clear(newHead);
        throw;
      }

      otherHead = otherHead->otherList;
    }

    return dmitriev::Pair< T >{newHead, newTail};
  }
}

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

    bool isEmpty() const;

  private:
    Pair< T > m_ptrPairHT;

  };
}

template< typename T >
dmitriev::Queue< T >::Queue():
  m_ptrPairHT{nullptr, nullptr}
{}

template< typename T >
dmitriev::Queue< T >::~Queue()
{
  clear(m_ptrPairHT.head);
}

template< typename T >
dmitriev::Queue< T >::Queue(const dmitriev::Queue< T >& otherQueue) :
  m_ptrPairHT(copyQueue(otherQueue.m_ptrPairHT.head))
{}

template< typename T >
dmitriev::Queue< T >::Queue(Queue< T >&& otherQueue) noexcept:
  m_ptrPairHT(otherQueue.m_ptrPairHT)
{
  otherQueue.m_ptrPairHT.head = nullptr;
  otherQueue.m_ptrPairHT.tail = nullptr;
}

template< typename T >
dmitriev::Queue< T >& dmitriev::Queue< T >::operator=(const Queue< T >& otherQueue)
{
  if (this == std::addressof(otherQueue))
  {
    return *this;
  }
  Queue< T > newQueue(otherQueue);
  clear(m_ptrPairHT.head);
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
  clear(m_ptrPairHT.head);
  m_ptrPairHT.head = otherQueue.m_ptrPairHT.head;
  m_ptrPairHT.tail = otherQueue.m_ptrPairHT.tail;

  otherQueue.m_ptrPairHT.head = nullptr;
  otherQueue.m_ptrPairHT.tail = nullptr;

  return *this;
}

template< typename T >
void dmitriev::Queue< T >::push(const T& rhs)
{
  if (m_ptrPairHT.head == nullptr)
  {
    m_ptrPairHT.head = new List< T >(rhs);
    m_ptrPairHT.tail = m_ptrPairHT.head;
  }
  else
  {
    m_ptrPairHT.tail->otherList = new List< T >(rhs);
    m_ptrPairHT.tail = m_ptrPairHT.tail->otherList;
  }
}

template< typename T >
void dmitriev::Queue< T >::push(T&& inp)
{
  if (m_ptrPairHT.head == nullptr)
  {
    m_ptrPairHT.head = new List< T >{std::move(inp), nullptr};
    m_ptrPairHT.tail = m_ptrPairHT.head;
  }
  else
  {
    m_ptrPairHT.tail->otherList = new List< T >{std::move(inp), nullptr};
    m_ptrPairHT.tail = m_ptrPairHT.tail->otherList;
  }
}

template< typename T >
void dmitriev::Queue< T >::popBack()
{
  if (m_ptrPairHT.head == nullptr)
  {
    throw std::underflow_error("underflow_error");
  }
  List< T >* newHead = m_ptrPairHT.head->otherList;
  delete m_ptrPairHT.head;

  m_ptrPairHT.head = newHead;
}

template< typename T >
T& dmitriev::Queue< T >::getTopData()
{
  if (m_ptrPairHT.head == nullptr)
  {
    throw std::underflow_error("underflow_error");
  }
  return m_ptrPairHT.head->data;
}

template< typename T >
bool dmitriev::Queue< T >::isEmpty() const
{
  return m_ptrPairHT.head == nullptr;
}

#endif
