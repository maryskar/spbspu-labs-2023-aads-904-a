#ifndef QUEUE_H
#define QUEUE_H
#include <stdexcept>
#include "list.h"
namespace aksenov
{
  template< typename T >
  class Queue
  {
    public:
      explicit Queue();
      Queue(const Queue< T > &otherQ);
      Queue(Queue< T > &&otherQ) noexcept;
      Queue< T > &operator=(const Queue< T > &other);
      Queue< T > &operator=(Queue< T > &&other) noexcept;
      ~Queue();
      void push(const T &val);
      void pop();
      T get() const;
      bool isEmpty() const;
    private:
      aksenov::List< T > *front_;
      aksenov::List< T > *tail_;
  };

  template< typename T >
  Queue< T >::Queue():
  front_(nullptr),
  tail_(nullptr)
  {}

  template< typename T >
  bool Queue< T >::isEmpty() const
  {
    return front_ == nullptr;
  }

  template< typename T>
  void Queue< T >::push(const T &val)
  {
    aksenov::List< T > *newTail = new aksenov::List< T >{val, nullptr};
    if (isEmpty())
    {
      front_ = tail_ = newTail;
    }
    else
    {
      tail_->next = newTail;
      tail_ = newTail;
    }
  }

  template< typename T >
  T Queue< T >::get() const
  {
    if (isEmpty())
    {
      throw std::logic_error("Empty queue");
    }
    return front_->data;
  }

  template< typename T >
  void Queue< T >::pop()
  {
    if (isEmpty())
    {
      throw std::logic_error("empty queue");
    }
    else if (front_ == tail_){
      delete tail_;
      tail_ = front_ = nullptr;
    }
    else
    {
      auto todel = front_;
      front_ = front_->next;
      delete todel;
    }
  }

  template< typename T >
  Queue< T >::~Queue()
  {
    deleteList(front_);
    front_ = tail_ = nullptr;
  }

  template< typename T>
  Queue< T >::Queue(const Queue< T > &otherQ) :
    tail_(nullptr),
    front_(nullptr)
  {
    aksenov::List< T > *cur = otherQ.front_;
    while (cur)
    {
      push(cur->data);
      cur = cur->next;
    }
  }

  template< typename T >
  Queue< T >::Queue(Queue< T > &&otherQ) noexcept :
    front_(otherQ.front_),
    tail_(otherQ.tail_)
  {
    otherQ.front_ = nullptr;
    otherQ.tail_ = nullptr;
  }

  template< typename T >
  Queue< T > &Queue< T >::operator=(const Queue< T > &other)
  {
    deleteList(front_);
    front_ = nullptr;
    tail_ = nullptr;
    aksenov::List< T > *cur = other.front_;
    while (cur)
    {
      push(cur->data);
      cur = cur->next;
    }
    return *this;
  }

  template< typename T >
  Queue< T > &Queue< T >::operator=(Queue< T > &&other) noexcept
  {
    deleteList(front_);
    front_ = nullptr;
    tail_ = nullptr;
    front_ = other.front_;
    tail_ = other.tail_;
    other.front_ = nullptr;
    other.tail_ = nullptr;
    return *this;
  }
}
#endif
