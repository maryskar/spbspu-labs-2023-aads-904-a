#ifndef FORWARDLIST_HPP
#define FORWARDLIST_HPP

#include <cstddef>
#include <list.hpp>
#include "forwardlistiterator.hpp"

template <typename T>
class ForwardList
{
  public:
    void pushFront(const T& value);
    void clear();
    List< T >* head_;
};

template <typename T>
void ForwardList< T >::pushFront(const T& value)
{
  List< T >* temp = new List< T >();
  temp->data_ = value;
  temp->next_ = head_;
  head_ = temp;
}

template <typename T>
void ForwardList< T >::clear()
{
  while(head_->next_ != nullptr)
  {
    List< T >* temp = head_->next_;
    delete head_;
    head_ = temp;
  }
}

#endif
