#ifndef FORWARDITERATOR_H
#define FORWARDITERATOR_H
#include <cassert>
#include <memory>
#include "list.h"
#include "constForwardIterator.h"

namespace fesenko
{
  template< typename T >
  class ForwardList;

  template< typename T >
  class ConstForwardIterator;

  template< typename T >
  class ForwardIterator
  {
    friend class ForwardList< T >;
    friend class ConstForwardIterator< T >;
   public:
    using this_t = ForwardIterator< T >;
    ForwardIterator();
    ForwardIterator(const this_t &) = default;
    ~ForwardIterator() = default;
    this_t &operator=(const this_t &) = default;
    this_t &operator++();
    this_t operator++(int);
    T &operator*();
    const T &operator*() const;
    T *operator->();
    const T *operator->() const;
    bool operator!=(const this_t &) const;
    bool operator==(const this_t &) const;
   private:
    List< T > *node_;
    explicit ForwardIterator(List< T > *);
  };

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
    assert(node_ != nullptr);
    this_t result(*this);
    ++(*this);
    return result;
  }

  template< typename T >
  const T &ForwardIterator< T >::operator*() const
  {
    assert(node_ != nullptr);
    return node_->data;
  }

  template< typename T >
  T &ForwardIterator< T >::operator*()
  {
    return const_cast< T & >((static_cast< const ForwardIterator< T > >(*this)).operator*());
  }

  template< typename T >
  const T *ForwardIterator< T >::operator->() const
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data);
  }

  template< typename T >
  T *ForwardIterator< T >::operator->()
  {
    return const_cast< T * >((static_cast< const ForwardIterator< T > >(*this)).operator->());
  }

  template< typename T >
  bool ForwardIterator< T >::operator==(const this_t &rhs) const
  {
    return node_ == rhs.node_;
  }

  template< typename T >
  bool ForwardIterator< T >::operator!=(const this_t &rhs) const
  {
    return !(rhs == *this);
  }

  template< typename T >
  ForwardIterator< T >::ForwardIterator(List< T > *head):
    node_(head)
  {}
}

#endif
