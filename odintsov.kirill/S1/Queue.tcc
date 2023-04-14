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
  std::tie(head_, tail_) = detail::duplicateNodes(q.head_);
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
  detail::deleteNodes(head_);
}

template< typename T >
odintsov::Queue< T >& odintsov::Queue< T >::operator=(const Queue< T >& q)
{
  if (this == &q) {
    return *this;
  }
  detail::Node< T >* oldHead = head_;
  std::tie(head_, tail_) = detail::duplicateNodes(q.head_);
  detail::deleteNodes(oldHead);
  return *this;
}

template< typename T >
odintsov::Queue< T >& odintsov::Queue< T >::operator=(Queue< T >&& q)
{
  detail::deleteNodes(head_);
  head_ = q.head_;
  tail_ = q.tail_;
  q.head_ = nullptr;
  q.tail_ = nullptr;
  return *this;
}

template< typename T >
void odintsov::Queue< T >::push(const T& data)
{
  push(new detail::Node< T >{data, nullptr});
}

template< typename T >
void odintsov::Queue< T >::push(T&& data)
{
  push(new detail::Node< T >{data, nullptr});
}

template< typename T >
void odintsov::Queue< T >::push(detail::Node< T >* n)
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
  detail::Node< T >* oldHead = head_;
  head_ = head_->next;
  if (!head_) {
    tail_ = nullptr;
  }
  delete oldHead;
}

template< typename T >
detail::ConstNodeIter< T > odintsov::Queue< T >::cbegin() const
{
  detail::ConstNodeIter< T > iter;
  iter.nodePtr = head_;
  return iter;
}

template< typename T >
detail::ConstNodeIter< T > odintsov::Queue< T >::cend() const
{
  return detail::ConstNodeIter< T >();
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
