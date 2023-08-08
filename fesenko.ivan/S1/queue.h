#ifndef QUEUE_H
#define QUEUE_H
#include <stdexcept>
#include <utility>
#include <memory>
#include "list.h"
namespace fesenko
{
  template< typename T >
  class Queue
  {
   public:
    Queue();
    Queue(const Queue< T > &);
    Queue(Queue< T > &&);
    Queue< T > &operator=(const Queue< T > &);
    Queue< T > &operator=(Queue< T > &&);
    ~Queue();
    void push(const T &);
    void push(T &&);
    const T &front() const;
    T &front();
    void pop();
    bool isEmpty() const noexcept;
   private:
    List< T > *head_;
    List< T > *tail_;
    void copy(const Queue< T > &);
  };
}

template< typename T >
fesenko::Queue< T >::Queue():
  head_(nullptr),
  tail_(nullptr)
{}

template< typename T >
fesenko::Queue< T >::Queue(const Queue< T > &other):
  Queue()
{
  copy(other);
}

template< typename T >
fesenko::Queue< T >::Queue(Queue< T > &&other):
  head_(std::move(other.head_)),
  tail_(other.tail_)
{}

template< typename T >
fesenko::Queue< T > &fesenko::Queue< T >::operator=(const Queue< T > &other)
{
  if (this != std::addressof(other))
  {
    copy(other);
  }
  return *this;
}

template< typename T >
fesenko::Queue< T > &fesenko::Queue< T >::operator=(Queue< T > &&other)
{
  if (this != std::addressof(other))
  {
    head_ = std::move(other.head_);
    tail_ = other.tail_;
  }
  return *this;
}

template< typename T >
fesenko::Queue< T >::~Queue()
{
  deleteList(head_);
  tail_ = nullptr;
}

template< typename T >
void fesenko::Queue< T >::push(const T &rhs)
{
  if (isEmpty()) {
    tail_ = new List< T >{rhs, nullptr};
    head_ = tail_;
  } else {
    tail_->next = new List< T >{rhs, nullptr};
    tail_ = tail_->next;
  }
}

template< typename T >
void fesenko::Queue< T >::push(T &&rhs)
{
  if (isEmpty()) {
    tail_ = new List< T >{std::move(rhs), nullptr};
    head_ = tail_;
  } else {
    tail_->next = new List< T >{std::move(rhs), nullptr};
    tail_ = tail_->next;
  }
}

template< typename T >
const T &fesenko::Queue< T >::front() const
{
  if (isEmpty()) {
    throw std::out_of_range("Queue is empty");
  }
  return head_->data;
}

template< typename T >
T &fesenko::Queue< T >::front()
{
   return const_cast< T & >((static_cast< const Queue< T > & >(*this)).front());
}

template< typename T >
void fesenko::Queue< T >::pop()
{
  if (isEmpty()) {
    throw std::out_of_range("Queue is empty");
  }
  List< T > *temp = head_->next;
  delete head_;
  head_ = temp;
}

template< typename T >
bool fesenko::Queue< T >::isEmpty() const noexcept
{
  return head_ == nullptr;
}

template< typename T >
void fesenko::Queue< T >::copy(const Queue< T > &other)
{
  auto res = copyList(other.head_);
  head_ = res.first;
  tail_ = res.second;
}
#endif
