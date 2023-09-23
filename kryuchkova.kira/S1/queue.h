#ifndef QUEUE_H
#define QUEUE_H
#include <stdexcept>
#include <node.h>

namespace kryuchkova
{
  template < typename T >
  class Queue
  {
    public:
      Queue();
      Queue(const Queue< T > &queue);
      Queue(Queue< T > &&rhs);
      Queue< T > & operator=(const Queue< T > &);
      Queue< T > & operator=(Queue< T > &&);
      ~Queue();
      void push(const T &rhs);
      T &drop();
      const T &drop() const;
      void pop();
      bool isEmpty() const;
    private:
      Node< T > *head_;
      Node< T > *tail_;
      void deleteQueue() noexcept;
      void copyQueue(const Queue< T > &);
  };

  template < typename T >
  Queue< T >::Queue():
    head_(nullptr),
    tail_(nullptr)
  {}

  template < typename T >
  Queue< T >::Queue(const Queue< T > &queue):
    Queue()
  {
    copyQueue();
  }

  template < typename T >
  void Queue< T >::deleteQueue() noexcept
  {
    deleteNode(head_);
    head_ = nullptr;
    tail_ = nullptr;
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
  }

  template < typename T >
  void Queue< T >::push(const T &rhs)
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
  void Queue< T >::pop()
  {
    if (isEmpty())
    {
      throw std::logic_error("Empty queue");
    }
    Node< T > *tmp = head_;
    if (head_ == tail_)
    {
      head_ = nullptr;
      tail_ = nullptr;
    }
    else
    {
      head_ = head_->next_;
    }
    delete tmp;
  }

  template < typename T >
  T &Queue< T >::drop()
  {
    if (isEmpty())
    {
      throw std::logic_error("empty");
    }
    return head_->data_;
  }

  template < typename T >
  const T &Queue< T >::drop() const
  {
    if (isEmpty())
    {
      throw std::logic_error("empty");
    }
    return head_->data_;
  }

  template < typename T >
  bool Queue< T >::isEmpty() const
  {
    return head_ == nullptr;
  }

  template< typename T >
  void Queue< T >::copyQueue(const Queue< T > & queue)
  {
    std::pair< Node< T > *, Node< T > * > temp = copyNode(queue.head_);
    head_ = temp.first;
    tail_ = temp.second;
  }

  template< typename T >
  Queue< T > &Queue< T >::operator=(const Queue< T > &queue)
  {
    if (this == std::addressof(queue))
    {
      return *this;
    }
    Node< T > * temp = head_;
    try
    {
      copyQueue(queue);
    }
    catch (...)
    {
      deleteQueue();
      head_ = temp;
      throw;
    }
    deleteNode(temp);
    return *this;
  }

  template< typename T >
  Queue< T > &Queue< T >::operator=(Queue< T > && queue)
  {
    if (this == std::addressof(queue))
    {
      return *this;
    }
    deleteQueue();
    head_ = queue.head_;
    tail_ = queue.last_;
    queue.head_ = nullptr;
    queue.tail_ = nullptr;
    return *this;
  }
}

#endif
