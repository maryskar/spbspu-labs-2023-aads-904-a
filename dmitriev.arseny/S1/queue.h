#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"
#include <iomanip>

template< typename T >
struct pair
{
  List< T >* head;
  List< T >* tail;
};

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
  pair< T > ptrPairHT;

};

template< typename T >
Queue< T >::Queue():
  ptrPairHT{nullptr, nullptr}
{}

template< typename T >
Queue< T >::~Queue()
{
  clear(ptrPairHT.head);
}

template< typename T >
Queue< T >::Queue(const Queue< T >& otherQueue) :
  ptrPairHT(copyQueue(otherQueue.ptrPairHT.head))
{}

template< typename T >
pair< T > copyQueue(List< T >* otherHead)
{
  if (otherHead == nullptr)
  {
    return pair< T >{nullptr, nullptr};
  }
  List< T >* newHead = new List< T >{otherHead->data};
  List< T >* newTail = newHead;
  otherHead = otherHead->otherList;

  while (otherHead != nullptr)
  {
    newTail = newTail->otherList;
    try
    {
      newTail = new List< T >{otherHead->data};
    }
    catch (const std::exception&)
    {
      clear(newHead);
      throw;
    }

    otherHead = otherHead->otherList;
  }

  return pair< T >{newHead, newTail};
}

template< typename T >
Queue< T >::Queue(Queue< T >&& otherQueue) noexcept:
  ptrPairHT(otherQueue.ptrPairHT)
{
  otherQueue.ptrPairHT.head = nullptr;
  otherQueue.ptrPairHT.tail = nullptr;
}

template< typename T >
Queue< T >& Queue< T >::operator=(const Queue< T >& otherQueue)
{
  if (this == std::addressof(otherQueue))
  {
    return *this;
  }
  Queue< T > newQueue(otherQueue);
  clear(ptrPairHT.head);
  *this = std::move(newQueue);

  return *this;
}

template< typename T >
Queue< T >& Queue< T >::operator=(Queue< T >&& otherQueue) noexcept
{
  if (this == std::addressof(otherQueue))
  {
    return *this;
  }
  clear(ptrPairHT.head);
  ptrPairHT.head = otherQueue.ptrPairHT.head;
  ptrPairHT.tail = otherQueue.ptrPairHT.tail;

  otherQueue.ptrPairHT.head = nullptr;
  otherQueue.ptrPairHT.tail = nullptr;

  return *this;
}

template< typename T >
void Queue< T >::push(const T& rhs)
{
  if (ptrPairHT.head == nullptr)
  {
    ptrPairHT.head = new List< T >(rhs);
    ptrPairHT.tail = ptrPairHT.head;
  }
  else
  {
    ptrPairHT.tail->otherList = new List< T >(rhs);
    ptrPairHT.tail = ptrPairHT.tail->otherList;
  }
}

template< typename T >
void Queue< T >::push(T&& inp)
{
  if (ptrPairHT.head == nullptr)
  {
    ptrPairHT.head = new List< T >{std::move(inp), nullptr};
    ptrPairHT.tail = ptrPairHT.head;
  }
  else
  {
    ptrPairHT.tail->otherList = new List< T >{std::move(inp), nullptr};
    ptrPairHT.tail = ptrPairHT.tail->otherList;
  }
}

template< typename T >
void Queue< T >::popBack()
{
  if (ptrPairHT.head == nullptr)
  {
    throw std::underflow_error("underflow_error");
  }
  List< T >* newHead = ptrPairHT.head->otherList;
  delete ptrPairHT.head;

  ptrPairHT.head = newHead;
}

template< typename T >
T& Queue< T >::getTopData()
{
  if (ptrPairHT.head == nullptr)
  {
    throw std::underflow_error("underflow_error");
  }
  return ptrPairHT.head->data;
}

template< typename T >
bool Queue< T >::isEmpty() const
{
  return ptrPairHT.head == nullptr;
}

#endif
