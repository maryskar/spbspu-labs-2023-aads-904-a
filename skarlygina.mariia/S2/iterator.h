#ifndef ITERATOR_H
#define ITERATOR_H
#include <iterator>
#include "citerator.h"
#include "list.h"
#include "forwardlist.h"

namespace skarlygina
{
  template < typename T >
  class Iterator : public std::iterator< std::forward_iterator_tag, T >
  {
  public:
    friend class ForwardList< T >;
    bool operator==(const Iterator&) const;
    bool operator!=(const Iterator&) const;
    explicit Iterator(const CIterator< T >&);
    Iterator& operator++();
    Iterator operator++(int);
    T& operator*();
    T* operator->();
  private:
    CIterator< T > iterator_;
  };

  template < typename T >
  Iterator< T >::Iterator(const CIterator< T >& other) :
    iterator_(other)
  {}

  template < typename T >
  bool Iterator< T >::operator==(const Iterator< T >& other) const
  {
    return iterator_ == other.iterator_;
  }
  template < typename T >
  bool Iterator< T >::operator!=(const Iterator< T >& other) const
  {
    return !(*this == other);
  }
  template < typename T >
  Iterator< T >& Iterator< T >::operator++()
  {
    ++iterator_;
    return *this;
  }
  template < typename T >
  Iterator< T > Iterator< T >::operator++(int)
  {
    return Iterator< T >(iterator_++);
  }
  template < typename T >
  T& Iterator< T >::operator*()
  {
    return const_cast<T&>(*iterator_);
  }
  template < typename T >
  T* Iterator< T >::operator->()
  {
    return const_cast<T*>(std::addressof(*iterator_));
  }
}
#endif
