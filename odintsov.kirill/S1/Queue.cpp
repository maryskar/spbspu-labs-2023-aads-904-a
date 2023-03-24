#include "Queue.hpp"

#include "AppendableList.hpp"

template< typename T >
void odintsov::Queue< T >::pop()
{
  typename AppendableList< T >::Node* next = this->head_->next;
  delete this->head_;
  this->head_ = next;
}

template< typename T >
T& odintsov::Queue< T >::head()
{
  return this->head_->data_;
}
