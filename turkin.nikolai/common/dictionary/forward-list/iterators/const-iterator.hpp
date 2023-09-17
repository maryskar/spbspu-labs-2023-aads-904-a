#ifndef CONST_ITERATOR_HPP
#define CONST_ITERATOR_HPP

#include <cassert>
#include <memory>
#include <utility>
#include "iterator.hpp"
#include "dictionary/forward-list/oneway-list.hpp"

namespace turkin
{
  template< typename T >
  class ForwardList;
  template< typename T >
  class ConstIterator
  {
    friend class ForwardList< T >;
    using ListNode = OneWayNode< T > *;
    public:
      ConstIterator();
      explicit ConstIterator(const Iterator< T > & rhs);
      ConstIterator< T > & operator=(const ConstIterator< T > & rhs) = default;
      ~ConstIterator() = default;
      ConstIterator< T > & operator++();
      ConstIterator< T > operator++(int);
      const T & operator*() const;
      const T * operator->() const;
      bool operator==(const ConstIterator< T > & rhs) const;
      bool operator!=(const ConstIterator< T > & rhs) const;
    private:
      explicit ConstIterator(ListNode rhs);
      ListNode cur_;
  };
}

template< typename T >
turkin::ConstIterator< T >::ConstIterator():
  cur_(nullptr)
{}

template< typename T >
turkin::ConstIterator< T >::ConstIterator(ListNode rhs):
  cur_(rhs)
{}

template< typename T >
turkin::ConstIterator< T >::ConstIterator(const Iterator< T > & rhs):
  cur_(rhs.cur_)
{}

template< typename T >
turkin::ConstIterator< T > & turkin::ConstIterator< T >::operator++()
{
  assert(cur_ != nullptr);
  cur_ = cur_->next;
  return * this;
}

template< typename T >
turkin::ConstIterator< T > turkin::ConstIterator< T >::operator++(int)
{
  assert(cur_ != nullptr);
  ConstIterator< T > result(*this);
  ++(*this);
  return result;
}

template< typename T >
const T & turkin::ConstIterator< T >::operator*() const
{
  assert(cur_ != nullptr);
  return cur_->data;
}

template< typename T >
const T * turkin::ConstIterator< T >::operator->() const
{
  assert(cur_ != nullptr);
  return std::addressof(cur_->data);
}

template< typename T >
bool turkin::ConstIterator< T >::operator==(const ConstIterator< T > & rhs) const
{
  return cur_ == rhs.cur_;
}

template< typename T >
bool turkin::ConstIterator< T >::operator!=(const ConstIterator< T > & rhs) const
{
  return !(rhs == *this);
}

#endif
