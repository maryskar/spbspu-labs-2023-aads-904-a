#ifndef FORWARDLIST_HPP
#define FORWARDLIST_HPP

#include <cstddef>
#include <utility>

#include <list.hpp>
#include "forwardlistiterator.hpp"
#include "forwardlistconstiterator.hpp"

template< typename T >
class ForwardList
{
  public:
    using iterator = ForwardListIterator< T >;
    using const_iterator = ForwardListConstIterator< T >;
    iterator begin() noexcept;
    bool empty();
    size_t max_size() const noexcept;
    void pushFront(const T& value);
    void pushFront(T&& value);
    void clear();
    iterator insert_after(const_iterator pos, const T& value);
    iterator insert_after(const_iterator pos, T&& value );
    iterator insert_after(const_iterator pos, size_t count, const T& value );
    iterator insert_after(const_iterator pos, iterator first, iterator last );
    template< typename... Args >
    iterator emplace_after(const_iterator pos, Args&&... args);
    List< T >* head_;
};

template < typename T >
typename ForwardList< T >::iterator ForwardList< T >::begin() noexcept
{
  return iterator(head_);
}

template < typename T >
bool ForwardList< T >::empty()
{
  return head_ == nullptr;
}

template < typename T >
size_t ForwardList< T >::max_size() const noexcept
{
  size_t size = 0;
  List< T >* temp = head_;
  while (temp)
  {
    temp = temp->next_;
    size++;
  }
  return size;
}

template< typename T >
void ForwardList< T >::pushFront(const T& value)
{
  List< T >* temp = new List< T >();
  temp->data_ = value;
  temp->next_ = head_;
  head_ = temp;
}

template< typename T >
void ForwardList< T >::pushFront(T&& value)
{
  pushFront(value);
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
  List< T >* cur = const_cast< List< T >* >(pos.ptr_);
  temp->next_ = cur->next_;
  cur->next_ = temp;
  return iterator(temp);
}

template< typename T >
typename ForwardList< T >::iterator ForwardList< T >::insert_after(const_iterator pos, T&& value)
{
  return insert_after(pos, value);
}

template< typename T >
typename ForwardList< T >::iterator ForwardList< T >::insert_after(const_iterator pos, size_t count, const T& value)
{
  iterator temp;
  for (size_t i = 0; i < count; i++)
  {
    temp = insert_after(pos, value);
    pos++;
  }
  return temp;
}

template< typename T >
typename ForwardList< T >::iterator ForwardList< T >::insert_after(const_iterator pos, iterator first, iterator last )
{
  iterator temp;
  while (first != last)
  {
    temp = insert_after(pos, first.ptr_->data_);
    first++;
  }
  return temp;
}

template< typename T >
template< typename... Args >
typename ForwardList< T >::iterator ForwardList< T >::emplace_after(const_iterator pos, Args&&... args)
{
  List< T >* temp = new List< T >(std::forward<Args>(args)...);
  List< T >* cur = const_cast< List< T >* >(pos.ptr_);
  temp->next_ = cur->next_;
  cur->next_ = temp;
  return iterator(temp);
}

#endif
