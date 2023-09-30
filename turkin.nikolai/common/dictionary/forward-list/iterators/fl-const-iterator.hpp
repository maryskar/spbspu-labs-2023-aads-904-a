#ifndef FL_CONST_ITERATOR_HPP
#define FL_CONST_ITERATOR_HPP

#include <cassert>
#include <memory>
#include <utility>
#include "fl-iterator.hpp"
#include "dictionary/forward-list/oneway-list.hpp"

namespace turkin
{
  template< typename T >
  class ForwardList;
  template< typename T >
  class FLConstIterator
  {
    friend class ForwardList< T >;
    using ListNode = OneWayNode< T > *;
    public:
      FLConstIterator();
      explicit FLConstIterator(const FLIterator< T > & rhs);
      FLConstIterator< T > & operator=(const FLConstIterator< T > & rhs) = default;
      ~FLConstIterator() = default;
      FLConstIterator< T > & operator++();
      FLConstIterator< T > operator++(int);
      const T & operator*() const;
      const T * operator->() const;
      bool operator==(const FLConstIterator< T > & rhs) const;
      bool operator!=(const FLConstIterator< T > & rhs) const;
    private:
      explicit FLConstIterator(ListNode rhs);
      ListNode cur_;
  };
}

template< typename T >
turkin::FLConstIterator< T >::FLConstIterator():
  cur_(nullptr)
{}

template< typename T >
turkin::FLConstIterator< T >::FLConstIterator(ListNode rhs):
  cur_(rhs)
{}

template< typename T >
turkin::FLConstIterator< T >::FLConstIterator(const FLIterator< T > & rhs):
  cur_(rhs.cur_)
{}

template< typename T >
turkin::FLConstIterator< T > & turkin::FLConstIterator< T >::operator++()
{
  assert(cur_ != nullptr);
  cur_ = cur_->next;
  return * this;
}

template< typename T >
turkin::FLConstIterator< T > turkin::FLConstIterator< T >::operator++(int)
{
  assert(cur_ != nullptr);
  FLConstIterator< T > result(*this);
  ++(*this);
  return result;
}

template< typename T >
const T & turkin::FLConstIterator< T >::operator*() const
{
  assert(cur_ != nullptr);
  return cur_->data;
}

template< typename T >
const T * turkin::FLConstIterator< T >::operator->() const
{
  assert(cur_ != nullptr);
  return std::addressof(cur_->data);
}

template< typename T >
bool turkin::FLConstIterator< T >::operator==(const FLConstIterator< T > & rhs) const
{
  return cur_ == rhs.cur_;
}

template< typename T >
bool turkin::FLConstIterator< T >::operator!=(const FLConstIterator< T > & rhs) const
{
  return !(rhs == *this);
}

#endif
