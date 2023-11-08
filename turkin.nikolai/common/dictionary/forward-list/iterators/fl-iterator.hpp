#ifndef FL_ITERATOR_HPP
#define FL_ITERATOR_HPP

#include <cassert>
#include <memory>
#include <utility>
#include "dictionary/forward-list/oneway-list.hpp"

namespace turkin
{
  template< typename T >
  class ForwardList;
  template< typename T >
  class FLConstIterator;
  template< typename T >
  class FLIterator
  {
    friend class ForwardList< T >;
    friend class FLConstIterator< T >;
    using ListNode = OneWayNode< T > *;
    public:
      FLIterator();
      FLIterator< T > & operator=(const FLIterator< T > & rhs) = default;
      ~FLIterator() = default;
      FLIterator< T > & operator++();
      FLIterator< T > operator++(int);
      T & operator*();
      T * operator->();
      bool operator==(const FLIterator< T > & rhs) const;
      bool operator!=(const FLIterator< T > & rhs) const;
    private:
      explicit FLIterator(ListNode rhs);
      ListNode cur_;
  };
}

template< typename T >
turkin::FLIterator< T >::FLIterator():
  cur_(nullptr)
{}

template< typename T >
turkin::FLIterator< T >::FLIterator(ListNode rhs):
  cur_(rhs)
{}

template< typename T >
turkin::FLIterator< T > & turkin::FLIterator< T >::operator++()
{
  assert(cur_ != nullptr);
  cur_ = cur_->next;
  return * this;
}

template< typename T >
turkin::FLIterator< T > turkin::FLIterator< T >::operator++(int)
{
  assert(cur_ != nullptr);
  FLIterator< T > result(*this);
  ++(*this);
  return result;
}

template< typename T >
T & turkin::FLIterator< T >::operator*()
{
  assert(cur_ != nullptr);
  return cur_->data;
}

template< typename T >
T * turkin::FLIterator< T >::operator->()
{
  assert(cur_ != nullptr);
  return std::addressof(cur_->data);
}

template< typename T >
bool turkin::FLIterator< T >::operator==(const FLIterator< T > & rhs) const
{
  return cur_ == rhs.cur_;
}

template< typename T >
bool turkin::FLIterator< T >::operator!=(const FLIterator< T > & rhs) const
{
  return !(rhs == *this);
}

#endif
