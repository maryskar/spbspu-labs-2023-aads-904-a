#ifndef FORWARDITERATOR_H
#define FORWARDITERATOR_H
#include <cassert>
#include <memory>
#include <List.h>

namespace aksenov
{
  template< typename T >
  class ForwardList;

  template< typename T >
  class ConstForwardIterator;

  template< typename T >
  class ForwardIterator
  {
  public:
    friend class ForwardList< T >;
    friend class ConstForwardIterator< T >;
    ForwardIterator();
    ~ForwardIterator() = default;
    ForwardIterator(const ForwardIterator< T > &) = default;

    ForwardIterator< T > &operator=(const ForwardIterator< T > &rhs) = default;

    ForwardIterator< T > &operator++();
    ForwardIterator< T > operator++(int);

    T &operator*();
    T *operator->();

    bool operator!=(const ForwardIterator< T > &rhs) const;
    bool operator==(const ForwardIterator< T > &rhs) const;
  private:
    listT< T > *node_;
    explicit ForwardIterator(listT< T > *node);
  };

  template< typename T >
  ForwardIterator< T >::ForwardIterator(listT< T > *node):
    node_(node)
  {}

  template< typename T >
  ForwardIterator< T >::ForwardIterator():
    node_(nullptr)
  {}

  template< typename T >
  ForwardIterator< T > &ForwardIterator< T >::operator++()
  {
    assert(node_ != nullptr);
    node_ = node_->next;
    return *this;
  }

  template< typename T >
  ForwardIterator< T > ForwardIterator< T >::operator++(int)
  {
    assert(node_);
    ForwardIterator< T > temp(*this);
    ++(*this);
    return temp;
  }

  template< typename T >
  T &ForwardIterator< T >::operator*()
  {
    assert(node_);
    return node_->data;
  }

  template< typename T >
  T *ForwardIterator< T >::operator->()
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data);
  }

  template< typename T >
  bool ForwardIterator< T >::operator==(const ForwardIterator< T > &rhs) const
  {
    return node_ == rhs.node_;
  }

  template< typename T >
  bool ForwardIterator< T >::operator!=(const ForwardIterator< T > &rhs) const
  {
    return !(rhs == *this);
  }
}
#endif
