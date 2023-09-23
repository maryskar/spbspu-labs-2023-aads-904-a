#ifndef FORWARDITER_H
#define FORWARDITER_H
#include <cassert>
#include <memory>
#include <list.h>

namespace chulkov {
  template < typename T >
  class FrdList;
  template < typename T >
  class ForwardConstIter;

  template < typename T >
  class ForwardIter: public std::iterator< std::forward_iterator_tag, T >
  {
  public:
    ForwardIter();
    ForwardIter(const ForwardIter< T >&) = default;
    ForwardIter(List< T >* node);
    ~ForwardIter() = default;
    ForwardIter< T >& operator++();
    ForwardIter< T > operator++(int);
    T& operator*();
    T* operator->();
    bool operator!=(const ForwardIter< T >& rhs) const;
    bool operator==(const ForwardIter< T >& rhs) const;
    ForwardIter< T >& operator=(const ForwardIter< T >&) = default;
    ForwardIter< T > eraseAfter(ForwardIter< T > it);

  private:
    friend class FrdList< T >;
    friend class ForwardConstIter< T >;
    List< T >* node_;
  };

  template < typename T >
  ForwardIter< T >::ForwardIter():
    node_(nullptr)
  {}

  template < typename T >
  ForwardIter< T >::ForwardIter(List< T >* node):
    node_(node)
  {}

  template < typename T >
  T& ForwardIter< T >::operator*()
  {
    return node_->item_;
  }

  template < typename T >
  T* ForwardIter< T >::operator->()
  {
    return std::addressof(node_->item_);
  }

  template < typename T >
  ForwardIter< T > eraseAfter(ForwardIter< T > it)
  {
    if (it.node_ && it.node_->next) {
      List< T >* temp = it.node_->next;
      it.node_->next = temp->next;
      delete temp;
      return it;
    }
    return ForwardIter< T >(nullptr);
  }

  template < typename T >
  typename ForwardIter< T >::ForwardIter ForwardIter< T >::operator++(int)
  {
    ForwardIter< T > res(*this);
    ++(*this);
    return res;
  }

  template < typename T >
  typename ForwardIter< T >::ForwardIter& ForwardIter< T >::operator++()
  {
    node_ = node_->next_;
    return *this;
  }

  template < typename T >
  bool ForwardIter< T >::operator!=(const ForwardIter& rhs) const
  {
    return !(rhs == *this);
  }

  template < typename T >
  bool ForwardIter< T >::operator==(const ForwardIter& rhs) const
  {
    return node_ == rhs.node_;
  }
}

#endif
