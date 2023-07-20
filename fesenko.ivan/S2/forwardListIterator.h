#ifndef FORWARDLISTITERATOR_H
#define FORWARDLISTITERATOR_H
#include <cassert>
#include <list.h>
#include <memory>

namespace fesenko
{
  template< typename T >
  class ForwardListIterator
  {
   public:
    using this_t = ForwardListIterator< T >;
    ForwardListIterator();
    ForwardListIterator(const this_t &) = default;
    ~ForwardListIterator() = default;
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
  };

  template< typename T >
  ForwardListIterator< T >::ForwardListIterator():
    node_(nullptr)
  {}

  template< typename T >
  ForwardListIterator< T > &ForwardListIterator< T >::operator++()
  {
    assert(node_ != nullptr);
    node_ = node_->next;
    return *this;
  }

  template< typename T >
  ForwardListIterator< T > ForwardListIterator< T >::operator++(int)
  {
    assert(node_ != nullptr);
    this_t result(*this);
    ++(*this);
    return result;
  }

  template< typename T >
  const T &ForwardListIterator< T >::operator*() const
  {
    assert(node_ != nullptr);
    return node_->data;
  }

  template< typename T >
  T &ForwardListIterator< T >::operator*()
  {
    return const_cast< T & >((static_cast< const ForwardListIterator< T > >(*this)).operator*());
  }

  template< typename T >
  const T *ForwardListIterator< T >::operator->() const
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data);
  }

  template< typename T >
  T *ForwardListIterator< T >::operator->()
  {
    return const_cast< T * >((static_cast< const ForwardListIterator< T > >(*this)).operator->());
  }

  template< typename T >
  bool ForwardListIterator< T >::operator==(const this_t &rhs) const
  {
    return node_ == rhs.mode;
  }

  template< typename T >
  bool ForwardListIterator< T >::operator!=(const this_t &rhs) const
  {
    return !(rhs == *this);
  }
}

#endif
