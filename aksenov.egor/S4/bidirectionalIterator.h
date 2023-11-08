#ifndef BIDIRECTIONALITERATOR_H
#define BIDIRECTIONALITERATOR_H
#include <functional>
#include <cassert>
#include "tree.h"
#include "constBidirectionalIterator.h"
namespace aksenov
{
  template < class T >
  class BidirectionalIterator : public std::iterator< std::bidirectional_iterator_tag, T >
  {

  public:
    friend struct node_t< T >;
    using TreeNode = node_t< T >;
    using NodePtr = node_t< T >*;
    template < class, class, class >
    friend class BinarySearchTree;
    template < class, class, class >
    friend class AVL;

    ~BidirectionalIterator() = default;
    BidirectionalIterator(const BidirectionalIterator&) = default;
    BidirectionalIterator& operator=(const BidirectionalIterator&) = default;

    BidirectionalIterator& operator++();
    BidirectionalIterator operator++(int);
    BidirectionalIterator& operator--();
    BidirectionalIterator operator--(int);

    T& operator*();
    T* operator->();

    explicit BidirectionalIterator(NodePtr node):
      iter_(node)
    {}
    bool operator!=(const BidirectionalIterator&) const;
    bool operator==(const BidirectionalIterator&) const;
  private:
    ConstBidirectionalIterator< T > iter_;
  };

  template < class T >
  class BidirectionalIterator< T >::BidirectionalIterator& BidirectionalIterator< T >::operator++()
  {
    ++iter_;
    return *this;
  }

  template < class T >
  class BidirectionalIterator< T >::BidirectionalIterator BidirectionalIterator< T >::operator++(int)
  {
    BidirectionalIterator toReturn(*this);
    ++iter_;
    return toReturn;
  }

  template < class T >
  class BidirectionalIterator< T >::BidirectionalIterator& BidirectionalIterator< T >::operator--()
  {
    --iter_;
    return *this;
  }

  template < class T >
  class BidirectionalIterator< T >::BidirectionalIterator BidirectionalIterator< T >::operator--(int)
  {
    BidirectionalIterator toReturn(*this);
    --iter_;
    return toReturn;
  }

  template < class T >
  T& BidirectionalIterator< T >::operator*()
  {
    return const_cast< T& >(*iter_);
  }

  template < class T >
  T* BidirectionalIterator< T >::operator->()
  {
    return std::addressof(const_cast< T& >(*iter_));
  }

  template < class T >
  bool BidirectionalIterator< T >::operator!=(const BidirectionalIterator& other) const
  {
    return iter_ != other.iter_;
  }

  template < class T >
  bool BidirectionalIterator< T >::operator==(const BidirectionalIterator& other) const
  {
    return iter_ == other.iter_;
  }
}
#endif
