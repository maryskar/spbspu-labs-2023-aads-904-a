#ifndef QUEUE_H
#define QUEUE_H
#include <stdexcept>
#include "node.h"

namespace kryuchkova
{
  template < typename T >
  class Queue
  {
    public:
      Queue();
      Queue(const Queue< T > &queue);
      Queue(Queue< T > &&rhs);
      //Queue< T > & operator=(const Queue< T > &);
      //Queue< T > & operator=(Queue< T > &&);
      ~Queue();
      void push(T rhs);
      T drop();
      bool isEmpty();
    private:
      Node< T > *head_;
      Node< T > *tail_;
      void deleteQueue() noexcept;
  };

  template < typename T >
  Queue< T >::Queue():
    head_(nullptr),
    tail_(nullptr)
  {}

  template < typename T >
  Queue< T >::Queue(const Queue< T > &queue):
    head_(nullptr),
    tail_(nullptr)
  {
    Node< T > *first = queue.head_;
    while (first)
    {
      push(first->data_);
      first = first->next_;
    }
  }

  template < typename T >
  void Queue< T >::deleteQueue() noexcept
  {
    while (head_)
    {
      Node< T > * temp = head_->next_;
      delete head_;
      head_ = temp;
    }
  }

  template < typename T >
  Queue< T >::Queue(Queue< T > &&rhs):
    head_(rhs.head_),
    tail_(rhs.tail_)
  {
    head_ = nullptr;
    tail_ = nullptr;
  }

  template < typename T >
  Queue< T >::~Queue()
  {
    deleteQueue();
    head_ = nullptr;
    tail_ = nullptr;
  }

  template < typename T >
  void Queue< T >::push(T rhs)
  {
    if (head_ == nullptr)
    {
      head_ = new Node< T >(rhs);
      tail_ = head_;
    }
    else
    {
      Node< T > *new_node = new Node< T >(rhs);
      tail_->next_ = new_node;
      tail_ = new_node;
    }
  }

  template < typename T >
  T Queue< T >::drop()
  {
    if (isEmpty())
    {
      throw std::logic_error("Empty queue");
    }
    Node< T > *tmp = head_;
    T data = head_->data_;
    head_ = head_->next_;
    delete tmp;
    return data;
  }

  template < typename T >
  bool Queue< T >::isEmpty()
  {
    return head_ == nullptr;
  }
}

#endif
