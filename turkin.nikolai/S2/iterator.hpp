#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cassert>
#include <memory>
#include "forward-list.hpp"
#include "oneway-list.hpp"

namespace turkin
{
  template< typename T >
  class Iterator
  {
    public:
      using List = OneWayNode< T > *;
      Iterator();
      Iterator(List rhs);
      ~Iterator() = default;
      Iterator(const Iterator< T > & rhs) = default;
      Iterator< T > & operator=(const Iterator< T > & rhs) = default;
      Iterator< T > & operator++();
      Iterator< T > operator++(int);
      T & operator*();
      T * operator->();
      bool operator==(const Iterator< T > & rhs) const;
      bool operator!=(const Iterator< T > & rhs) const;
    private:
      List cur_;
  };
}


template< typename T >
turkin::Iterator< T >::Iterator():
  cur_(nullptr)
{}

template< typename T >
turkin::Iterator< T >::Iterator(List rhs):
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
  Iterator< T > result(* this);
  ++(* this);
  return result;
}

template< typename T >
bool turkin::Iterator< T >::operator==(const Iterator< T > & rhs) const
{
  return cur_ == rhs.cur_;
}

template< typename T >
bool turkin::Iterator< T >::operator!=(const Iterator< T > & rhs) const
{
  return !(rhs == * this);
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

#endif
