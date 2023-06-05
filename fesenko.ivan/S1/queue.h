#ifndef QUEUE_H
#define QUEUE_H
#include <stdexcept>
#include "list.h"
namespace fesenko
{
  template< typename T >
  class Queue
  {
   public:
    Queue();
    ~Queue();
    void push(const T rhs);
    T &front();
    void pop();
    bool isEmpty();
   private:
    List< T > *head_;
    List< T > *tail_;
  };
}

template< typename T >
fesenko::Queue< T >::Queue():
  head_(nullptr),
  tail_(nullptr)
{}

template< typename T >
fesenko::Queue< T >::~Queue()
{
  deleteList(head_);
  head_ = nullptr;
  tail_ = nullptr;
}

template< typename T >
void fesenko::Queue< T >::push(const T rhs)
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
T &fesenko::Queue< T >::front()
{
  if (isEmpty()) {
    throw std::out_of_range("Queue is empty");
  }
  return head_->data;
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

template<  typename T >
bool fesenko::Queue< T >::isEmpty()
{
  return head_ == nullptr;
}
#endif
