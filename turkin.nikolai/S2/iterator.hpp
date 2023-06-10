#include <cassert>
#include <memory>
#include "oneway-list.hpp"

namespace turkin
{
  template< typename T >
  class FLIterator
  {
    public:
      FLIterator();
      ~FLIterator() = default;
      FLIterator(const FLIterator< T > & rhs) = default;
      FLIterator< T > & operator=(const FLIterator< T > & rhs) = default;
      FLIterator< T > & operator++();
      FLIterator< T > operator++(int);
      T & operator*();
      const T & operator*() const;
      T * operator->();
      const T * operator->() const;
      bool operator==(const FLIterator< T > & rhs) const;
      bool operator!=(const FLIterator< T > & rhs) const;
    private:
      OneWayNode< T > * cur_;
  };
}

template< typename T >
turkin::FLIterator< T >::FLIterator():
  cur_(nullptr)
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
  FLIterator< T > result(* this);
  ++(* this);
  return result;
}

template< typename T >
bool turkin::FLIterator< T >::operator==(const FLIterator< T > & rhs) const
{
  return cur_ == rhs.cur_;
}

template< typename T >
bool turkin::FLIterator< T >::operator!=(const FLIterator< T > & rhs) const
{
  return !(rhs == * this);
}

template< typename T >
T & turkin::FLIterator< T >::operator*()
{
  assert(cur_ != nullptr);
  return cur_->data;
}

template< typename T >
const T & turkin::FLIterator< T >::operator*() const
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
const T * turkin::FLIterator< T >::operator->() const
{
  assert(cur_ != nullptr);
  return std::addressof(cur_->data);
}
