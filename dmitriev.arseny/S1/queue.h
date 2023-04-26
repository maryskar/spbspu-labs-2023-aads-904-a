#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"
#include <iomanip>

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
  T& getTopData() const;

  bool isEmpty() const;

private:
  List< T >* head;
  List< T >* tail;

};

template< typename T >
Queue< T >::Queue():
  head(nullptr),
  tail(nullptr)
{}

template< typename T >
Queue< T >::~Queue()
{
  clear(head);
}

template< typename T >
Queue< T >::Queue(const Queue< T >& otherQueue):
  head(nullptr),
  tail(nullptr)
{
  if (otherQueue.head != nullptr)
  {
    List< T >* otherTail = otherQueue.head;
    push(otherTail->data);
    otherTail = otherTail->otherList;
    while (otherTail != nullptr)
    {
      try
      {
        tail->otherList = new List< T >(otherTail->data);
      }
      catch (const std::exception&)
      {
        clear(head);
        throw;
      }
      tail = tail->otherList;
      otherTail = otherTail->otherList;
    }
  }
}

template< typename T >
Queue< T >::Queue(Queue< T >&& otherQueue) noexcept:
  head(otherQueue.head),
  tail(otherQueue.tail)
{
  otherQueue.head = nullptr;
  otherQueue.tail = nullptr;
}

template<typename T>
Queue< T >& Queue< T >::operator=(const Queue< T >& otherQueue)
{
  if (this == &otherQueue)
  {
    return *this;
  }
  Queue< T > newQueue(otherQueue);
  clear(head);
  head = newQueue.head;
  tail = newQueue.tail;

  newQueue.head = nullptr;
  newQueue.tail = nullptr;

  return *this;
}

template<typename T>
Queue< T >& Queue< T >::operator=(Queue< T >&& otherQueue) noexcept
{
  if (this == &otherQueue)
  {
    return *this;
  }
  clear(head);
  head = otherQueue.head;
  tail = otherQueue.tail;

  otherQueue.head = nullptr;
  otherQueue.tail = nullptr;

  return *this;
}

template< typename T >
void Queue< T >::push(const T& rhs)
{
  if (head == nullptr)
  {
    head = new List< T >(rhs);
    tail = head;
  }
  else
  {
    tail->otherList = new List< T >(rhs);
    tail = tail->otherList;
  }
}

template< typename T >
void Queue<T>::push(T&& inp)
{
  if (head == nullptr)
  {
    head = new List< T >{ std::move(inp), nullptr };
    tail = head;
  }
  else
  {
    tail->otherList = new List< T >{ std::move(inp), nullptr };
    tail = tail->otherList;
  }
}

template< typename T >
void Queue< T >::popBack()
{
  if (head == nullptr)
  {
    throw std::underflow_error("underflow_error");
  }
  List< T >* newHead = head->otherList;
  delete head;

  head = newHead;
}

template< typename T >
T& Queue< T >::getTopData() const
{
  if (head == nullptr)
  {
    throw std::underflow_error("underflow_error");
  }
  return head->data;
}

template< typename T >
inline bool Queue< T >::isEmpty() const
{
  return head == nullptr;
}

#endif
