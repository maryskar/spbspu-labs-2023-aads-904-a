#ifndef FORWARDLISTITERATOR
#define FORWARDLISTITERATOR

#include "list.hpp"

template< typename T >
class ForwardListIterator
{
  public:
    ForwardListIterator();
    ~ForwardListIterator();
    ForwardListIterator(List< T >* rhs);
    ForwardListIterator< T >& operator++();
    ForwardListIterator< T >& operator++(int);
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
    ptr_ = ptr_.next;
  }
  return *this;
}

#endif
