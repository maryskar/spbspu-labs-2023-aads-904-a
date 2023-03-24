#include "AppendableList.hpp"

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
  if (tail_) {
    tail_->next = next;
  } else {
    head_ = next;
  }
  tail_ = next;
}
