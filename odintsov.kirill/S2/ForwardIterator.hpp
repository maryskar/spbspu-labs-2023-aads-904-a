#ifndef FORWARDITERATOR_HPP
#define FORWARDITERATOR_HPP

#include <iterator>

#include "Node.hpp"

namespace detail {
  template< typename T >
  struct ForwardIterator: public std::iterator< std::forward_iterator_tag, T > {
    using Node = detail::Node< T >;
    Node* nodePtr;

    ForwardIterator():
      nodePtr(nullptr)
    {}

    ForwardIterator(Node* ptr):
      nodePtr(ptr)
    {}

    ForwardIterator& operator++()
    {
      if (nodePtr) {
        nodePtr = nodePtr->next;
      }
      return *this;
    }

    ForwardIterator operator++(int)
    {
      ForwardIterator< T > copy(*this);
      if (nodePtr) {
        nodePtr = nodePtr->next;
      }
      return copy;
    }

    T& operator*() const
    {
      return nodePtr->val;
    }

    T* operator->() const
    {
      return std::addressof(nodePtr->val);
    }

    bool operator==(const ForwardIterator& rhs) const
    {
      return nodePtr == rhs.nodePtr;
    }

    bool operator!=(const ForwardIterator& rhs) const
    {
      return nodePtr != rhs.nodePtr;
    }
  };

  template< typename T >
  struct ConstForwardIterator: public std::iterator< std::forward_iterator_tag, T > {
    using Node = detail::Node< T >;
    const Node* nodePtr;

    ConstForwardIterator():
      nodePtr(nullptr)
    {}

    ConstForwardIterator(const Node* ptr):
      nodePtr(ptr)
    {}

    ConstForwardIterator(const ForwardIterator< T >& fi):
      nodePtr(fi.nodePtr)
    {}

    ConstForwardIterator(ForwardIterator< T >&& fi):
      nodePtr(fi.nodePtr)
    {}

    ConstForwardIterator& operator++()
    {
      if (nodePtr) {
        nodePtr = nodePtr->next;
      }
      return *this;
    }

    ConstForwardIterator operator++(int)
    {
      ConstForwardIterator< T > copy(*this);
      if (nodePtr) {
        nodePtr = nodePtr->next;
      }
      return copy;
    }

    const T& operator*() const
    {
      return nodePtr->val;
    }

    const T* operator->() const
    {
      return std::addressof(nodePtr->val);
    }

    bool operator==(const ConstForwardIterator& rhs) const
    {
      return nodePtr == rhs.nodePtr;
    }

    bool operator!=(const ConstForwardIterator& rhs) const
    {
      return nodePtr != rhs.nodePtr;
    }
  };
}

#endif
