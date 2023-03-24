#include "Queue.hpp"

#include <stdexcept>

#include "AppendableList.hpp"

template< typename T >
void odintsov::Queue< T >::pop()
{
  if (!this->head_) {
    throw std::runtime_error("Cannot pop empty queue");
  }
  typename AppendableList< T >::Node* next = this->head_->next;
  delete this->head_;
  this->head_ = next;
  if (!this->head_) {
    this->tail_ = nullptr;
  }
}

template< typename T >
T& odintsov::Queue< T >::head()
{
  if (!this->head_) {
    throw std::runtime_error("Attempt to get head of empty queue");
  }
  return this->head_->data_;
}
