#ifndef FORWARDLISTITERATOR
#define FORWARDLISTITERATOR

#include "list.hpp"

template< typename T >
class ForwardListIterator
{
  public:
    ForwardListIterator();
    ~ForwardListIterator() = default;
    ForwardListIterator(List< T >* rhs);
    ForwardListIterator< T >& operator++();
    ForwardListIterator< T > operator++(int);
    T& operator*() const;
    T* operator->() const;
    bool operator==(const ForwardListIterator< T >& rhs) const;
    bool operator!=(const ForwardListIterator< T >& rhs) const;
  private:
    List< T >* ptr_;
};

template< typename T >
ForwardListIterator< T >::ForwardListIterator():
  ptr_(nullptr)
{
}

template< typename T >
ForwardListIterator< T >::ForwardListIterator(List< T >* rhs):
  ptr_(rhs)
{
}

template< typename T >
ForwardListIterator< T >& ForwardListIterator< T >::operator++()
{
  if (ptr_)
  {
    ptr_ = ptr_->next_;
  }
  return *this;
}

template< typename T >
ForwardListIterator< T > ForwardListIterator< T >::operator++(int)
{
  ForwardListIterator< T > temp(*this);
  if (ptr_)
  {
    ptr_ = ptr_->next_;
  }
  return temp;
}

template< typename T >
T& ForwardListIterator< T >::operator*() const
{
  return ptr_->data_;
}

template< typename T >
T* ForwardListIterator< T >::operator->() const
{
  return std::addressof(ptr_.data_);
}

template < typename T >
bool ForwardListIterator< T >::operator==(const ForwardListIterator< T >& rhs) const
{
  return ptr_ == rhs.ptr_;
}

template< typename T >
bool ForwardListIterator< T >::operator!=(const ForwardListIterator< T >& rhs) const
{
  return ptr_ != rhs.ptr_;
}

#endif
