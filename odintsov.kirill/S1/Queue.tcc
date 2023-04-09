#include <stdexcept>
#include <tuple>

#include "Node.hpp"

template< typename T >
odintsov::Queue< T >::Queue():
  head_(nullptr),
  tail_(nullptr)
{}

template< typename T >
odintsov::Queue< T >::Queue(const Queue< T >& q):
  head_(nullptr),
  tail_(nullptr)
{
  std::tie(head_, tail_) = duplicateNodes(q.head_);
}

template< typename T >
odintsov::Queue< T >::Queue(Queue< T >&& q):
  head_(q.head_),
  tail_(q.tail_)
{
  q.head_ = nullptr;
  q.tail_ = nullptr;
}

template< typename T >
odintsov::Queue< T >::~Queue()
{
  deleteNodes(head_);
}

template< typename T >
odintsov::Queue< T >& odintsov::Queue< T >::operator=(const Queue< T >& q)
{
  if (this == &q) {
    return *this;
  }
  Node< T >* oldHead = head_;
  std::tie(head_, tail_) = duplicateNodes(q.head_);
  deleteNodes(oldHead);
  return *this;
}

template< typename T >
odintsov::Queue< T >& odintsov::Queue< T >::operator=(Queue< T >&& q)
{
  deleteNodes(head_);
  head_ = q.head_;
  tail_ = q.tail_;
  q.head_ = nullptr;
  q.tail_ = nullptr;
  return *this;
}

template< typename T >
void odintsov::Queue< T >::push(const T& data)
{
  push(new Node< T >{data, nullptr});
}

template< typename T >
void odintsov::Queue< T >::push(T&& data)
{
  push(new Node< T >{data, nullptr});
}

template< typename T >
void odintsov::Queue< T >::push(Node< T >* n)
{
  if (empty()) {
    head_ = n;
  } else {
    tail_->next = n;
  }
  tail_ = n;
}

template< typename T >
void odintsov::Queue< T >::pop()
{
  if (empty()) {
    throw std::runtime_error("Attempt to pop empty queue");
  }
  odintsov::Node< T >* oldHead = head_;
  head_ = head_->next;
  if (!head_) {
    tail_ = nullptr;
  }
  delete oldHead;
}

template< typename T >
T& odintsov::Queue< T >::head()
{
  return const_cast< T& >(const_cast< const Queue< T >* >(this)->head());
}

template< typename T >
const T& odintsov::Queue< T >::head() const
{
  if (empty()) {
    throw std::runtime_error("Attempt to get head of empty queue");
  }
  return head_->data;
}

template< typename T >
bool odintsov::Queue< T >::empty() const
{
  return !head_ || !tail_;
}
