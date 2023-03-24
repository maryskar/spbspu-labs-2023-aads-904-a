#include "AppendableList.hpp"

#include <stdexcept>

template< typename T >
odintsov::AppendableList< T >::AppendableList():
  head_(nullptr),
  tail_(nullptr)
{}

template< typename T >
odintsov::AppendableList< T >::~AppendableList()
{
  while (head_) {
    Node* next = head_->next;
    delete head_;
    head_ = next;
  };
}

template< typename T >
void odintsov::AppendableList< T >::push(const T& data)
{
  Node* next = new Node{data, nullptr};
  if (!head_) {
    head_ = next;
  } else {
    tail_->next = next;
  }
  tail_ = next;
}

template< typename T >
void odintsov::AppendableList< T >::pop()
{
  if (!head_ || !tail_) {
    throw std::runtime_error("Cannot pop empty list");
  }
  unsafePop();
}
