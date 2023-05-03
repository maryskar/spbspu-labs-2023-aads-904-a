#ifndef FORWARDITERATOR_HPP
#define FORWARDITERATOR_HPP

#include <iterator>

#include "Node.hpp"

namespace detail {
  template< typename T >
  struct ForwardIterator: public std::iterator< std::forward_iterator_tag, T > {
    Node< T >* nodePtr;

    ForwardIterator():
      nodePtr(nullptr)
    {}

    ForwardIterator(Node< T >* ptr):
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
      return nodePtr->data;
    }

    T* operator->() const
    {
      return std::addressof(nodePtr->data);
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
    const Node< T >* nodePtr;

    ConstForwardIterator():
      nodePtr(nullptr)
    {}

    ConstForwardIterator(const Node< T >* ptr):
      nodePtr(ptr)
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
      return nodePtr->data;
    }

    const T* operator->() const
    {
      return std::addressof(nodePtr->data);
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
