#ifndef FORWARDLIST_HPP
#define FORWARDLIST_HPP

#include <cstddef>
#include <list.hpp>
#include "forwardlistiterator.hpp"
#include "forwardlistconstiterator.hpp"

template< typename T >
class ForwardList
{
  public:
    using iterator = ForwardListIterator< T >;
    using const_iterator = ForwardListConstIterator< T >;
    void pushFront(const T& value);
    void clear();
    iterator insert_after(const_iterator pos, const T& value);
    List< T >* head_;

};

template< typename T >
void ForwardList< T >::pushFront(const T& value)
{
  List< T >* temp = new List< T >();
  temp->data_ = value;
  temp->next_ = head_;
  head_ = temp;
}

template< typename T >
void ForwardList< T >::clear()
{
  while(head_->next_ != nullptr)
  {
    List< T >* temp = head_->next_;
    delete head_;
    head_ = temp;
  }
}

template< typename T >
typename ForwardList< T >::iterator ForwardList< T >::insert_after(const_iterator pos, const T& value)
{
  List< T >* temp = new List< T >();
  temp->data_ = value;
  List< T >* cur = const_cast<List< T >*>(pos.ptr_);
  temp->next_ = cur->next_;
  cur->next_ = temp;
  return iterator(temp);
}

#endif
