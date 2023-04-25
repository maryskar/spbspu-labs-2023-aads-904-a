#ifndef QUEUEFORUNIQUEPTR_H
#define QUEUEFORUNIQUEPTR_H

#include "queue.h"
#include "listForUniquePtr.h"
#include "mathExprPtr.h"

template<>
class Queue< MathExprPtr>
{
public:
  Queue();
  ~Queue();

  Queue(const Queue< MathExprPtr >& otherQueue);
  Queue(Queue< MathExprPtr >&& otherQueue) noexcept;

  Queue< MathExprPtr >& operator=(const Queue< MathExprPtr >& otherQueue);
  Queue< MathExprPtr >& operator=(Queue< MathExprPtr >&& otherQueue) noexcept;

  void push(MathExprPtr& rhs);
  void popBack();
  MathExprPtr getTopData() const;

  bool isEmpty() const;

private:
  List< MathExprPtr >* head;
  List< MathExprPtr >* tail;

};

Queue< MathExprPtr >::Queue() :
  head(nullptr),
  tail(nullptr)
{

}

Queue< MathExprPtr >::~Queue()
{
  clear(head);
}

Queue< MathExprPtr >::Queue(const Queue< MathExprPtr >& otherQueue) :
  head(nullptr),
  tail(nullptr)
{
  if (otherQueue.head != nullptr)
  {
    List< MathExprPtr >* otherTail = otherQueue.head;
    push(otherTail->data);
    otherTail = otherTail->otherList;
    while (otherTail != nullptr)
    {
      try
      {
        tail->otherList = new List< MathExprPtr >(otherTail->data);
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

Queue< MathExprPtr >::Queue(Queue< MathExprPtr >&& otherQueue) noexcept :
  head(otherQueue.head),
  tail(otherQueue.tail)
{
  otherQueue.head = nullptr;
  otherQueue.tail = nullptr;
}

Queue< MathExprPtr >& Queue< MathExprPtr >::operator=(const Queue< MathExprPtr >& otherQueue)
{
  if (this == &otherQueue)
  {
    return *this;
  }
  Queue< MathExprPtr > newQueue(otherQueue);
  clear(head);
  head = newQueue.head;
  tail = newQueue.tail;

  newQueue.head = nullptr;
  newQueue.tail = nullptr;

  return *this;
}

Queue< MathExprPtr >& Queue< MathExprPtr >::operator=(Queue< MathExprPtr >&& otherQueue) noexcept
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

void Queue< MathExprPtr >::push(MathExprPtr& rhs)
{
  if (head == nullptr)
  {
    head = new List< MathExprPtr >(rhs);
    tail = head;
  }
  else
  {
    tail->otherList = new List< MathExprPtr >(rhs);
    tail = tail->otherList;
  }
}

void Queue< MathExprPtr >::popBack()
{
  if (head == nullptr)
  {
    throw std::underflow_error("underflow_error");
  }
  List< MathExprPtr >* newHead = head->otherList;
  delete head;

  head = newHead;
}

MathExprPtr Queue< MathExprPtr >::getTopData() const
{
  if (head == nullptr)
  {
    throw std::underflow_error("underflow_error");
  }
  return std::move(head->data);
}

inline bool Queue< MathExprPtr >::isEmpty() const
{
  return head == nullptr;
}

#endif
