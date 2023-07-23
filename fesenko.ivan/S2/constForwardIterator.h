#ifndef CONSTFORWARDITERATOR_H
#define CONSTFORWARDITERATOR_H
#include <cassert>
#include <memory>
#include <list.h>
#include "forwardIterator.h"
namespace fesenko
{
  template< typename T >
  class ConstForwardIterator
  {
   public:
    using this_t = ConstForwardIterator< T >;
    ConstForwardIterator();
    ConstForwardIterator(const this_t &) = default;
    explicit ConstForwardIterator(const ForwardIterator< T > &);
    ~ConstForwardIterator() = default;
    this_t &operator=(const this_t &) = default;
    this_t &operator++();
    this_t operator++(int);
    const T &operator*() const;
    const T *operator->() const;
    bool operator!=(const this_t &) const;
    bool operator==(const this_t &) const;
   private:
    List< T > *node_;
  };

  template< typename T >
  ConstForwardIterator< T >::ConstForwardIterator():
    node_(nullptr)
  {}

  template< typename T >
  ConstForwardIterator< T >::ConstForwardIterator(const ForwardIterator< T > &rhs):
    node_(static_cast< const List< T > * >(rhs.node_))
  {}

  template< typename T >
  ConstForwardIterator< T > &ConstForwardIterator< T >::operator++()
  {
    assert(node_ != nullptr);
    node_ = node_->next;
    return *this;
  }

  template< typename T >
  ConstForwardIterator< T > ConstForwardIterator< T >::operator++(int)
  {
    assert(node_ != nullptr);
    this_t result(*this);
    ++(*this);
    return result;
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
  bool ConstForwardIterator< T >::operator==(const this_t &rhs) const
  {
    return node_ == rhs.mode;
  }

  template< typename T >
  bool ConstForwardIterator< T >::operator!=(const this_t &rhs) const
  {
    return !(rhs == *this);
  }
}

#endif
