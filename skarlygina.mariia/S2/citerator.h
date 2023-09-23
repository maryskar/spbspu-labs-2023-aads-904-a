#ifndef CITERATOR_H
#define CITERATOR_H
#include <iterator>
#include "list.h"
namespace skarlygina
{
  template < typename T >
  class CIterator : public std::iterator< std::forward_iterator_tag, T >
  {
  public:
    bool operator ==(const CIterator&) const;
    bool operator!=(const CIterator&) const;
    CIterator& operator++();
    CIterator operator++(int);
    const T& operator*() const;
    const T* operator->() const;
  private:
    const List< T >* ptr_;
    explicit CIterator(const List< T >*);
  };

  template < typename T >
  CIterator< T >::CIterator(const List< T >* ptr) :
    ptr_(ptr)
  {}

  template < typename T >
  bool CIterator< T >::operator==(const CIterator< T >& other) const
  {
    return ptr_ == other.ptr_;
  }
  template < typename T >
  bool CIterator< T >::operator!=(const CIterator< T >& other) const
  {
    return !(*this == other);
  }
  template < typename T >
  CIterator< T >& CIterator< T >::operator++()
  {
    ptr_ = ptr_->next;
    return *this;
  }
  template < typename T >
  CIterator< T > CIterator< T >::operator++(int)
  {
    ConstIterator temp = *this;
    ++(*this);
    return temp;
  }
  template < typename T >
  const T& CIterator< T >::operator*() const
  {
    return ptr_->data;
  }
  template < typename T >
  const T* CIterator< T >::operator->() const
  {
    return std::addressof(ptr_->data);
  }
}
#endif
