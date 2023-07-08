#ifndef FORWARDLISTCONSTITERATOR_HPP
#define FORWARDLISTCONSTITERATOR_HPP

#include <memory>
#include <list.hpp>

template< typename T >
class ForwardListConstIterator
{
  public:
    ForwardListConstIterator();
    ~ForwardListConstIterator() = default;
    ForwardListConstIterator(const List< T >* rhs);
    ForwardListConstIterator< T >& operator++();
    ForwardListConstIterator< T > operator++(int);
    T& operator*();
    T* operator->();
    bool operator==(const ForwardListConstIterator< T >& rhs) const;
    bool operator!=(const ForwardListConstIterator< T >& rhs) const;
  private:
    const List< T >* ptr_;
};

template< typename T >
ForwardListConstIterator< T >::ForwardListConstIterator():
  ptr_(nullptr)
{
}

template< typename T >
ForwardListConstIterator< T >::ForwardListConstIterator(const List< T >* rhs):
  ptr_(rhs)
{
}

template< typename T >
ForwardListConstIterator< T >& ForwardListConstIterator< T >::operator++()
{
  if (ptr_)
  {
    ptr_ = ptr_->next_;
  }
  return *this;
}

template< typename T >
ForwardListConstIterator< T > ForwardListConstIterator< T >::operator++(int)
{
  ForwardListConstIterator< T > temp(*this);
  if (ptr_)
  {
    ptr_ = ptr_->next_;
  }
  return temp;
}

template< typename T >
T& ForwardListConstIterator< T >::operator*()
{
  return ptr_->data_;
}

template< typename T >
T* ForwardListConstIterator< T >::operator->()
{
  return std::addressof(ptr_.data_);
}

template< typename T >
bool ForwardListConstIterator< T >::operator==(const ForwardListConstIterator< T >& rhs) const
{
  return ptr_ == rhs.ptr_;
}

template< typename T >
bool ForwardListConstIterator< T >::operator!=(const ForwardListConstIterator< T >& rhs) const
{
  return ptr_ != rhs.ptr_;
}

#endif