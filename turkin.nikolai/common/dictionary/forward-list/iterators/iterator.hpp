#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cassert>
#include <memory>
#include <utility>
#include "forward-list/oneway-list.hpp"

namespace turkin
{
  template< typename T >
  class ForwardList;
  template< typename T >
  class ConstIterator;
  template< typename T >
  class Iterator
  {
    friend class ForwardList< T >;
    friend class ConstIterator< T >;
    using ListNode = OneWayNode< T > *;
    public:
      Iterator();
      Iterator< T > & operator=(const Iterator< T > & rhs) = default;
      ~Iterator() = default;
      Iterator< T > & operator++();
      Iterator< T > operator++(int);
      T & operator*();
      T * operator->();
      bool operator==(const Iterator< T > & rhs) const;
      bool operator!=(const Iterator< T > & rhs) const;
    private:
      explicit Iterator(ListNode rhs);
      ListNode cur_;
  };
}

template< typename T >
turkin::Iterator< T >::Iterator():
  cur_(nullptr)
{}

template< typename T >
turkin::Iterator< T >::Iterator(ListNode rhs):
  cur_(rhs)
{}

template< typename T >
turkin::Iterator< T > & turkin::Iterator< T >::operator++()
{
  assert(cur_ != nullptr);
  cur_ = cur_->next;
  return * this;
}

template< typename T >
turkin::Iterator< T > turkin::Iterator< T >::operator++(int)
{
  assert(cur_ != nullptr);
  Iterator< T > result(*this);
  ++(*this);
  return result;
}

template< typename T >
T & turkin::Iterator< T >::operator*()
{
  assert(cur_ != nullptr);
  return cur_->data;
}

template< typename T >
T * turkin::Iterator< T >::operator->()
{
  assert(cur_ != nullptr);
  return std::addressof(cur_->data);
}

template< typename T >
bool turkin::Iterator< T >::operator==(const Iterator< T > & rhs) const
{
  return cur_ == rhs.cur_;
}

template< typename T >
bool turkin::Iterator< T >::operator!=(const Iterator< T > & rhs) const
{
  return !(rhs == *this);
}

#endif
