#include "datastructures.h"

template< typename T >
Queue< T >::Queue():
  head_(nullptr),
  tail_(nullptr)
{}

template< typename T >
Queue< T >::~Queue()
{
  while (head_ != nullptr) {
    qBox< T >* next = head_->prev_;
    delete *head_;
    delete head_;
    head_ = next;
  }
}

template < typename T >
void Queue< T >::push(T rhs)
{
  qBox< T >* head = new qBox< T >{rhs, head_, nullptr};
  head_->next_ = head;
  head_ = head;
}

template <typename T >
T Queue< T >::drop()
{
  qBox< T >* next = tail_->next_;
  T res = tail_->value_;
  delete *tail_;
  delete tail_;
  tail_ = next;
  return res;
}


