#include "Queue.hpp"

#include <stdexcept>

template< typename T >
odintsov::Queue< T >::Queue():
  head_(nullptr),
  tail_(nullptr)
{}

template< typename T >
odintsov::Queue< T >::~Queue()
{
  while (!empty()) {
    Node* oldHead = head_;
    head_ = head_->next;
    delete oldHead;
  }
}

template< typename T >
void odintsov::Queue< T >::push(const T& data)
{
  Node* newNode = new Node{data, nullptr};
  if (empty()) {
    head_ = newNode;
  } else {
    tail_->next = newNode;
  }
  tail_ = newNode;
}

template< typename T >
void odintsov::Queue< T >::pop()
{
  if (empty()) {
    throw std::runtime_error("Attempt to pop empty queue");
  }
  Node* oldHead = head_;
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
  return head_->data_;
}

template< typename T >
bool odintsov::Queue< T >::empty() const
{
  return !head_ || !tail_;
}
