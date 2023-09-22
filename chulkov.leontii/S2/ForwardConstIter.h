#ifndef FORWARDCONSTITER_H
#define FORWARDCONSTITER_H
#include <cassert>
#include <memory>
#include "ForwardIter.h"

namespace chulkov {
  template < typename T >
  class FrdList;
  template < typename T >
  class ForwardIter;

  template < typename T >
  class ForwardConstIter: public std::iterator< std::forward_iterator_tag, T >
  {
  public:
    ForwardConstIter();
    ForwardConstIter(List< T >* node);
    ForwardConstIter(const ForwardConstIter< T >&) = default;
    ForwardConstIter(const ForwardIter< T >& rhs);
    ~ForwardConstIter() = default;

    ForwardConstIter< T >& operator=(const ForwardConstIter< T >&) = default;
    ForwardConstIter< T >& operator++();
    ForwardConstIter< T > operator++(int);
    T& operator*() const;
    T* operator->() const;
    bool operator!=(const ForwardConstIter< T >&) const;
    bool operator==(const ForwardConstIter< T >&) const;

  private:
    friend class FrdList< T >;
    friend class ForwardIter< T >;
    List< T >* cnode_;
  };

  template < typename T >
  ForwardConstIter< T >::ForwardConstIter():
    cnode_(nullptr)
  {}

  template < typename T >
  ForwardConstIter< T >::ForwardConstIter(List< T >* node):
    cnode_(node)
  {}

  template < typename T >
  ForwardConstIter< T >::ForwardConstIter(const ForwardIter< T >& rhs):
    cnode_(rhs.node_)
  {}

  template < typename T > T& ForwardConstIter< T >::operator*() const
  {
    return cnode_->item_;
  }

  template < typename T >
  T* ForwardConstIter< T >::operator->() const
  {
    return std::addressof(cnode_->item_);
  }

  template < typename T >
  typename ForwardConstIter< T >::ForwardConstIter& ForwardConstIter< T >::operator++()
  {
    assert(cnode_ != nullptr);
    cnode_ = cnode_->next_;
    return *this;
  }

  template < typename T >
  typename ForwardConstIter< T >::ForwardConstIter ForwardConstIter< T >::operator++(int)
  {
    ForwardConstIter< T > res(*this);
    ++(*this);
    return res;
  }

  template < typename T >
  bool ForwardConstIter< T >::operator!=(const ForwardConstIter& rhs) const
  {
    return !(rhs == *this);
  }

  template < typename T >
  bool ForwardConstIter< T >::operator==(const ForwardConstIter& rhs) const
  {
    return cnode_ == rhs.cnode_;
  }
}

#endif
