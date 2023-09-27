#ifndef CONSTFORWARDITERATOR_H
#define CONSTFORWARDITERATOR_H
#include <cassert>
#include <memory>
#include "List.h"
namespace aksenov
{
  template< typename T >
  class ForwardList;

  template< typename T >
  class ForwardIterator;

  template< typename T >
  class ConstForwardIterator
  {
  public:
    friend class ForwardList< T >;
    friend class ConstForwardIterator< T >;
    ConstForwardIterator();
    ~ConstForwardIterator() = default;
    ConstForwardIterator(listT< T > *node);
    ConstForwardIterator(const ConstForwardIterator< T > &) = default;
    ConstForwardIterator< T > &operator=(const ConstForwardIterator< T > &rhs) = default;

    ConstForwardIterator< T > &operator++();
    ConstForwardIterator< T > &operator++(int) const;

    const T &operator*() const;
    const T *operator->() const;

    bool operator!=(const ConstForwardIterator< T > &rhs) const;
    bool operator==(const ConstForwardIterator< T > &rhs) const;

  private:
    listT< T > *node_;
  };

  template< typename T >
  ConstForwardIterator< T >::ConstForwardIterator():
          node_(nullptr)
  {}

  template< typename T >
  ConstForwardIterator< T >::ConstForwardIterator(listT< T > *node):
          node_(node)
  {}
  template< typename T >
  ConstForwardIterator< T > &ConstForwardIterator< T >::operator++()
  {
    assert(node_ != nullptr);
    node_ = node_->next;
    return *this;
  }

  template< typename T >
  ConstForwardIterator< T > &ConstForwardIterator< T >::operator++(int) const
  {
    assert(node_ != nullptr);
    ConstForwardIterator< T > temp(*this);
    ++(*this);
    return temp;
  }

  template< typename T >
  const T &ConstForwardIterator< T >::operator*() const
  {
    assert(node_ != nullptr);
    return node_->data;
  }

  template< typename T >
  const T *ConstForwardIterator< T >::operator->() const
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data);
  }

  template< typename T >
  bool ConstForwardIterator< T >::operator==(const ConstForwardIterator< T > &rhs) const
  {
    return node_ == rhs.node_;
  }

  template< typename T >
  bool ConstForwardIterator< T >::operator!=(const ConstForwardIterator< T > &rhs) const
  {
    return node_ != rhs.node_;
  }
}
#endif
