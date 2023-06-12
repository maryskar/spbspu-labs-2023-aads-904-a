#ifndef CONST_ITERATOR_HPP
#define CONST_ITERATOR_HPP

#include <cassert>
#include <memory>
#include "forward-list.hpp"
#include "oneway-list.hpp"

namespace turkin
{
  template< typename T >
  class ConstIterator
  {
    public:
      using List = const OneWayNode< T > *;
      ConstIterator();
      ConstIterator(List rhs);
      ~ConstIterator() = default;
      ConstIterator(const ConstIterator< T > & rhs) = default;
      ConstIterator< T > & operator=(const ConstIterator< T > & rhs) = default;
      ConstIterator< T > & operator++();
      ConstIterator< T > operator++(int);
      const T & operator*() const;
      const T * operator->() const;
      bool operator==(const ConstIterator< T > & rhs) const;
      bool operator!=(const ConstIterator< T > & rhs) const;
    private:
      List cur_;
  };
}


template< typename T >
turkin::ConstIterator< T >::ConstIterator():
  cur_(nullptr)
{}

template< typename T >
turkin::ConstIterator< T >::ConstIterator(List rhs):
  cur_(rhs)
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
  ConstIterator< T > result(* this);
  ++(* this);
  return result;
}

template< typename T >
bool turkin::ConstIterator< T >::operator==(const ConstIterator< T > & rhs) const
{
  return cur_ == rhs.cur_;
}

template< typename T >
bool turkin::ConstIterator< T >::operator!=(const ConstIterator< T > & rhs) const
{
  return !(rhs == * this);
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

#endif
