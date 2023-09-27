#ifndef FORWARDITER_H
#define FORWARDITER_H
#include <cassert>
#include <memory>
#include "ForwardList.h"
#include "ForwardConstIter.h"
#include <List.h>
namespace timofeev
{
  template< typename T >
  class ForwardList;
  template< typename T >
  class ForwardConstIterator;

  template< typename T >
  class ForwardIterator
  {
  public:
    friend class ForwardList< T >;
    friend class ForwardConstIterator< T >;
    ForwardIterator();

    ForwardIterator(List< T > *node);
    ~ForwardIterator() = default;
    ForwardIterator(const ForwardIterator< T >&) = default;
    ForwardIterator< T >& operator=(const ForwardIterator< T >&) = default;

    bool operator!=(const ForwardIterator< T > &other) const;
    bool operator==(const ForwardIterator< T > &other) const;

    T &operator*();
    T *operator->();

    ForwardIterator< T > &operator++();
    ForwardIterator< T > operator++(int);

  private:
    List<T> *node_;
  };

  template<typename T>
  ForwardIterator<T>::ForwardIterator(List< T > *node):
    node_(node)
  {}

  template< typename T >
  ForwardIterator< T > ForwardIterator< T >::operator++(int)
  {
    assert(node_ != nullptr);
    ForwardIterator< T > tmp(*this);
    ++(*this);
    return tmp;
  }

  template< typename T >
  ForwardIterator< T > &ForwardIterator< T >::operator++()
  {
    assert(node_ != nullptr);
    node_ = node_->next;
    return *this;
  }

  template< typename T >
  bool ForwardIterator< T >::operator==(const ForwardIterator< T > &other) const
  {
    return node_ == other.node_;
  }

  template< typename T >
  T *ForwardIterator< T >::operator->()
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data);
  }

  template< typename T >
  T &ForwardIterator< T >::operator*()
  {
    assert(node_ != nullptr);
    return node_->data;
  }

  template< typename T >
  bool ForwardIterator< T >::operator!=(const ForwardIterator< T > &other) const
  {
    return !(other == *this);
  }

  template< typename T >
  ForwardIterator< T >::ForwardIterator():
    node_(nullptr)
  {}

}
#endif
