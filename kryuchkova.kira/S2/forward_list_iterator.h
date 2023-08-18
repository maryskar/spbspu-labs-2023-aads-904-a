#ifndef FORWARD_LIST_ITERATOR_H
#define FORWARD_LIST_ITERATOR_H
#include <iterator>
#include <cassert>
#include <memory>
#include "../common/node.h"

namespace kryuchkova
{
  template < typename T >
  class ForwardList;

  template < typename T >
  class ForwardIterator: public std::iterator< std::forward_iterator_tag, T >
  {
    friend class ForwardList< T >;
    friend class ConstForwardIterator< T >;
  public:
    using this_t = ForwardIterator< T >;

    ForwardIterator();
    ForwardIterator(const this_t&) = default;
    ~ForwardIterator() = default;

    this_t& operator=(const this_t&) = default;
    this_t& operator++();
    this_t operator++(int);
    bool operator!=(const this_t& rhs) const;
    bool operator==(const this_t& rhs) const;

    T & operator*();
    const T & operator*() const;
    T * operator->();
    const T * operator->() const;

  private:
    explicit ForwardIterator(Node< T > * node);
    Node< T > * node_;
  };

  template < typename T >
  T & ForwardIterator< T >::operator*()
  {
    assert(node_ != nullptr);
    return node_->data;
  }

  template < typename T >
  const T & ForwardIterator< T >::operator*() const
  {
    assert(node_ != nullptr);
    return node_->data;
  }

  template < typename T >
  T * ForwardIterator< T >::operator->()
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data);
  }

  template < typename T >
  const T * ForwardIterator< T >::operator->() const
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data);
  }

  template < typename T >
  ForwardIterator< T > & ForwardIterator< T >::operator++()
  {
    assert(node_ != nullptr);
    node_ = node_->next_;
    return *this;
  }

  template < typename T >
  ForwardIterator< T > ForwardIterator< T >::operator++(int)
  {
    assert(node_ != nullptr);
    ForwardIterator< T > temp(*this);
    ++(*this);
    return temp;
  }

  template < typename T >
  bool ForwardIterator< T >::operator!=(const ForwardIterator< T > & rhs) const
  {
    return !(node_ == rhs.node_);
  }

  template < typename T >
  bool ForwardIterator< T >::operator==(const ForwardIterator< T > & rhs) const
  {
    return node_ == rhs.node_;
  }

  template < typename T >
  ForwardIterator< T >::ForwardIterator():
    node_(nullptr)
  {}

  template< typename T >
  ForwardIterator< T >::ForwardIterator(Node< T > * node):
   node_(node)
  {}

}

#endif
