#ifndef FORWARD_LIST_CONST_ITERATOR_H
#define FORWARD_LIST_CONST_ITERATOR_H
#include <iterator>
#include <cassert>
#include "../common/node.h"

namespace kryuchkova
{
  template < typename T >
  class ForwardList;
  template < typename T >
  class ForwardIterator;

  template < typename T >
  class ConstForwardIterator: public std::iterator< std::forward_iterator_tag, const T >
  {
    friend class ForwardList< T >;
    friend class ForwardIterator< T >;

  public:
    using this_t = ConstForwardIterator< T >;

    ConstForwardIterator();
    ConstForwardIterator(const ForwardIterator< T > rhs);
    ~ConstForwardIterator() = default;

    this_t& operator=(const this_t&) = default;
    this_t& operator++();
    this_t operator++(int);
    bool operator!=(const this_t& rhs) const;
    bool operator==(const this_t& rhs) const;

  private:
    Node< T > * node_;
    explicit ConstForwardIterator(Node< T > * node);
  };

  template < typename T >
  ConstForwardIterator< T > & ConstForwardIterator< T >::operator++()
  {
    assert(node_ != nullptr);
    node_ = node_->next;
    return *this;
  }

  template < typename T >
  ConstForwardIterator< T > ConstForwardIterator< T >::operator++(int)
  {
    assert(node_ != nullptr);
    this_t temp(*this);
    ++(*this);
    return temp;
  }

  template < typename T >
  bool ConstForwardIterator< T >::operator!=(const ConstForwardIterator< T > & rhs) const
  {
    return !(node_ == rhs.node_);
  }

  template < typename T >
  bool ConstForwardIterator< T >::operator==(const ConstForwardIterator< T > & rhs) const
  {
    return node_ == rhs.node_;
  }

  template < typename T >
  ConstForwardIterator< T >::ConstForwardIterator(const ForwardIterator< T > rhs):
    node_(rhs.node_)
  {}
  
  template < typename T >
  ConstForwardIterator< T >::ConstForwardIterator():
    node_(nullptr)
  {}

  template < typename T >
  ConstForwardIterator< T >::ConstForwardIterator(Node< T > * node):
    node_(node)
  {}
}

#endif
