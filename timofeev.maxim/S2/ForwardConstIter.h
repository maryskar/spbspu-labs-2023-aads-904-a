#ifndef FORWARDCONSTITER_H
#define FORWARDCONSTITER_H
#include "ForwardList.h"
#include "ForwardIter.h"
//#include <List.h>
#include "../common/List.h"
namespace timofeev
{
  template< typename T >
  class ForwardList;

  template< typename T >
  class ForwardIterator;

  template< typename T >
  class ForwardConstIterator
  {
  public:
    friend class ForwardList< T >;
    friend class ForwardIterator< T >;

    ForwardConstIterator();
    ~ForwardConstIterator() = default;

    ForwardConstIterator(List< T > *node);
    ForwardConstIterator(const ForwardConstIterator < T > &) = default;
    ForwardConstIterator< T >& operator=(const ForwardConstIterator< T >&) = default;

    bool operator!=(const ForwardConstIterator< T > &other) const;
    bool operator==(const ForwardConstIterator< T > &other) const;

    const T &operator*() const;
    const T *operator->() const;

    const ForwardConstIterator< T > &operator++();
    const ForwardConstIterator< T > operator++(int) const;

  private:
    List< T > *node_;
  };

  template< typename T >
  ForwardConstIterator< T >::ForwardConstIterator(List< T > *node):
    node_(node)
  {}

  template< typename T >
  const ForwardConstIterator< T > ForwardConstIterator< T >::operator++(int) const
  {
    assert(node_ != nullptr);
    ForwardConstIterator< T > tmp(*this);
    ++(*this);
    return tmp;
  }

  template< typename T >
  const ForwardConstIterator< T > &ForwardConstIterator< T >::operator++()
  {
    assert(node_ != nullptr);
    node_ = node_->next;
    return *this;
  }

  template< typename T >
  bool ForwardConstIterator< T >::operator==(const ForwardConstIterator< T > &other) const
  {
    return node_ == other.node_;
  }

  template< typename T >
  bool ForwardConstIterator< T >::operator!=(const ForwardConstIterator< T > &other) const
  {
    return node_ != other.node_;
  }

  template< typename T >
  const T *ForwardConstIterator< T >::operator->() const
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data);
  }

  template< typename T >
  const T &ForwardConstIterator< T >::operator*() const
  {
    assert(node_ != nullptr);
    return node_->data;
  }

  template< typename T >
  ForwardConstIterator< T >::ForwardConstIterator():
    node_(nullptr)
  {}
}

#endif
