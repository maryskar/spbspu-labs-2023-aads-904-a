#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <cstddef>
#include <stdexcept>
#include <list.hpp>

namespace chemodurov
{
  template< typename T >
  class Queue
  {
   public:
    Queue();
    Queue(const Queue< T > &);
    Queue(Queue< T > &&);
    ~Queue();
    Queue< T > & operator=(const Queue< T > &);
    Queue< T > & operator=(Queue< T > &&);
    void push(const T & rhs);
    void pop();
    T & getFromQueue();
    const T & getFromQueue() const;
    bool empty() const noexcept;
   private:
    List< T > * head_;
    List< T > * last_;
    void copyQueue(const Queue< T > &);
    void deleteQueue() noexcept;
  };
}

template< typename T >
chemodurov::Queue< T >::Queue():
 head_(nullptr),
 last_(nullptr)
{}

template< typename T >
chemodurov::Queue< T >::~Queue()
{
  deleteQueue();
}

template< typename T >
void chemodurov::Queue< T >::push(const T & rhs)
{
  if (!empty())
  {
    last_->next = new List< T >{rhs, nullptr};
    last_ = last_->next;
  }
  else
  {
    last_ = new List< T >{rhs, nullptr};
    head_ = last_;
  }
}

template< typename T >
const T & chemodurov::Queue< T >::getFromQueue() const
{
  if (empty())
  {
    throw std::logic_error("Empty queue");
  }
  return (*head_).data;
}

template< typename T >
T & chemodurov::Queue< T >::getFromQueue()
{
  return const_cast< T & >((static_cast< const Queue< T > & >(*this)).getFromQueue());
}

template< typename T >
void chemodurov::Queue< T >::pop()
{
  if (empty())
  {
    throw std::logic_error("Empty queue");
  }
  List< T > * temp = head_->next;
  delete head_;
  head_ = temp;
}

template< typename T >
bool chemodurov::Queue< T >::empty() const noexcept
{
  return head_ == nullptr;
}

template< typename T >
chemodurov::Queue< T >::Queue(const chemodurov::Queue< T > & queue):
 Queue()
{
  copyQueue();
}

template< typename T >
void chemodurov::Queue< T >::copyQueue(const Queue< T > & queue)
{
  std::pair< List< T > *, List< T > * > temp = copyList(queue.head_);
  head_ = temp.first;
  last_ = temp.second;
}

template< typename T >
void chemodurov::Queue< T >::deleteQueue() noexcept
{
  deleteList(head_);
  head_ = nullptr;
  last_ = nullptr;
}

template< typename T >
chemodurov::Queue< T >::Queue(chemodurov::Queue< T > && queue):
 head_(queue.head_),
 last_(queue.last_)
{
  queue.head_ = nullptr;
  queue.last_ = nullptr;
}

template< typename T >
chemodurov::Queue< T > & chemodurov::Queue< T >::operator=(const chemodurov::Queue< T > & queue)
{
  if (this == std::addressof(queue))
  {
    return *this;
  }
  List< T > * temp = head_;
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
  deleteList(temp);
  return *this;
}

template< typename T >
chemodurov::Queue< T > & chemodurov::Queue< T >::operator=(chemodurov::Queue< T > && queue)
{
  if (this == std::addressof(queue))
  {
    return *this;
  }
  deleteQueue();
  head_ = queue.head_;
  last_ = queue.last_;
  queue.head_ = nullptr;
  queue.last_ = nullptr;
  return *this;
}

#endif
