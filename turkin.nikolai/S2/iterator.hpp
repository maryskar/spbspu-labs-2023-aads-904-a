#include <cassert>
#include <memory>
#include "forward-list.hpp"
#include "oneway-list.hpp"

namespace turkin
{
  template< typename T, typename List >
  class Iterator
  {
    public:
      Iterator();
      ~Iterator() = default;
      Iterator(const Iterator< T, List > & rhs) = default;
      Iterator< T, List > & operator=(const Iterator< T, List > & rhs) = default;
      Iterator< T, List > & operator++();
      Iterator< T, List > operator++(int);
      T & operator*();
      const T & operator*() const;
      T * operator->();
      const T * operator->() const;
      bool operator==(const Iterator< T, List > & rhs) const;
      bool operator!=(const Iterator< T, List > & rhs) const;
    private:
      List cur_;
  };
}

template< typename T, typename List >
turkin::Iterator< T, List >::Iterator():
  cur_(nullptr)
{}

template< typename T, typename List >
turkin::Iterator< T, List > & turkin::Iterator< T, List >::operator++()
{
  assert(cur_ != nullptr);
  cur_ = cur_->next;
  return * this;
}

template< typename T, typename List >
turkin::Iterator< T, List > turkin::Iterator< T, List >::operator++(int)
{
  assert(cur_ != nullptr);
  Iterator< T, List > result(* this);
  ++(* this);
  return result;
}

template< typename T, typename List >
bool turkin::Iterator< T, List >::operator==(const Iterator< T, List > & rhs) const
{
  return cur_ == rhs.cur_;
}

template< typename T, typename List >
bool turkin::Iterator< T, List >::operator!=(const Iterator< T, List > & rhs) const
{
  return !(rhs == * this);
}

template< typename T, typename List >
T & turkin::Iterator< T, List >::operator*()
{
  assert(cur_ != nullptr);
  return cur_->data;
}

template< typename T, typename List >
const T & turkin::Iterator< T, List >::operator*() const
{
  assert(cur_ != nullptr);
  return cur_->data;
}

template< typename T, typename List >
T * turkin::Iterator< T, List >::operator->()
{
  assert(cur_ != nullptr);
  return std::addressof(cur_->data);
}

template< typename T, typename List >
const T * turkin::Iterator< T, List >::operator->() const
{
  assert(cur_ != nullptr);
  return std::addressof(cur_->data);
}
