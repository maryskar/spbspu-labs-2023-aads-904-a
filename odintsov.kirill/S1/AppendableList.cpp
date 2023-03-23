#include "AppendableList.hpp"

template< typename T >
odintsov::AppendableList< T >::AppendableList(const T& data):
  head_(new Node{data, nullptr}),
  tail_(head_)
{}

template< typename T >
odintsov::AppendableList< T >::~AppendableList()
{
  do {
    Node* next = head_->next;
    delete head_;
    head_ = next;
  } while (head_);
}

template< typename T >
void odintsov::AppendableList< T >::push(const T& data)
{
  Node* next = new Node{data, nullptr};
  tail_->next = next;
  tail_ = next;
}
