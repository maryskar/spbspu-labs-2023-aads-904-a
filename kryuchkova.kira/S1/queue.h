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
      //Queue< T > & operator=(const Queue< T > &);
      //Queue< T > & operator=(Queue< T > &&);
      ~Queue();
      void push(T rhs);
      T drop();
      bool isEmpty();
    private:
      Node< T > *head_;
      Node< T > *tail_;
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
  Queue< T >::~Queue()
  {
    while (head_)
    {
      drop();
    }
  }

  template < typename T >
  void Queue< T >::push(T rhs)
  {
    Node< T > *new_node = new Node< T >(rhs);
    if (head_ == nullptr)
    {
      head_ = new_node;
      tail_ = new_node;
    }
    else
    {
     new_node->next_ = tail_;
     tail_ = new_node;
    }
  }

  template < typename T >
  T Queue< T >::drop()
  {
    Node< T > *current = tail_;
    if (isEmpty())
    {
      throw std::logic_error("Empty queue");
    }
    if (tail_->next_ == head_->next_)
    {
      head_ = nullptr;
      tail_ = nullptr;
      return current->data_;
    }
    else
    {
      while (current->next_ != head_)
      {
        current = current->next_;
      }
      T data = head_->data_;
      head_ = current;
      delete current->next_;
      return data;
    }
  }

  template < typename T >
  bool Queue< T >::isEmpty()
  {
    return head_ == nullptr;
  }
}

#endif
