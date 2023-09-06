#ifndef FORWARDLISTITER_H
#define FORWARDLISTITER_H
#include <cassert>
#include <memory>
#include "ForwardList.h"
#include "ForwardListConstIter.h"
#include "../common/List.h"
namespace timofeev
{
  template< typename T >
  class ForwardListIterator
  {
    //friend class ForwardList< T >;
    friend class ForwardListConstIterator< T >;

  public:
    ForwardListIterator();
    ~ForwardListIterator() = default;

    ForwardListIterator(List<T> *other);
    ForwardListIterator(const ForwardListIterator <T> &other) = default;
    ForwardListIterator(const ForwardListIterator <T> &&other) = default;

    bool operator!=(ForwardListIterator<T> &other) const;
    bool operator==(ForwardListIterator<T> &other) const;

    T &operator*();
    T *operator->();

    ForwardListIterator<T> &operator++();
    ForwardListIterator<T> operator++(int);

    /* ForwardListIterator (TElement *start) noexcept
     bool 	operator!= (ForwardListIterator other) const
     TElement & 	operator* () const
     ForwardListIterator & 	operator++ ()
     ForwardListIterator 	operator++ (int)
     TElement * 	operator-> () const
     bool 	operator== (ForwardListIterator other) const*/

  private:
    List<T> *node_;
  };
}

template< typename T>
timofeev::ForwardListIterator< T >::ForwardListIterator():
  node_(nullptr)
{}

template< typename T >
timofeev::ForwardListIterator< T >::ForwardListIterator(List< T >* other)
{
  node_ = other;
}

template< typename T >
bool timofeev::ForwardListIterator< T >::operator==(ForwardListIterator<T> &other) const
{
  return node_ == other.node_;
}

template< typename T >
bool timofeev::ForwardListIterator< T >::operator!=(ForwardListIterator<T> &other) const
{
  return !(*this == other);
}

template< typename T >
T& timofeev::ForwardListIterator< T >::operator*()
{
  assert(node_ != nullptr);
  return node_->data;
}

template< typename T >
T* timofeev::ForwardListIterator< T >::operator->()
{
  assert(node_ != nullptr);
  return std::addressof(node_->data);
}

template< typename T >
timofeev::ForwardListIterator< T >& timofeev::ForwardListIterator< T >::operator++()
{
  assert(node_ != nullptr);
  node_ = node_->next;
  return *this;
}

template< typename T >
timofeev::ForwardListIterator< T > timofeev::ForwardListIterator< T >::operator++(int)
{
  ForwardListIterator< T > tmp(*this);
  assert(node_ != nullptr);
  node_ = node_->next;
  return tmp;
}

#endif //SPBSPU_LABS_2023_AADS_904_A_FORWARDLISTITER_H
