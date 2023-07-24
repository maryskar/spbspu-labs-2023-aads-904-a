#ifndef ITERATOR_H
#define ITERATOR_H
#include <cassert>
#include <memory>
#include <dictionary.h>
#include "forwardConstIterator.h"
#include "nodeList.h"

namespace mashkin
{
  template< class T >
  class forwardIterator: public std::iterator< std::forward_iterator_tag, T >
  {
  public:
    forwardIterator();
    ~forwardIterator() = default;
    forwardIterator(const forwardIterator< T >&) = default;
    forwardIterator(NodeList< T >* rhs);

    forwardIterator< T >& operator=(const forwardIterator< T >&) = default;
    forwardIterator< T >& operator++();
    forwardIterator< T > operator++(int);

    T& operator*();
    T* operator->();

    bool operator!=(const forwardIterator< T >& rhs) const;
    bool operator==(const forwardIterator< T >& rhs) const;

  private:
    template< typename U >
    friend class ForwardList;
    template< typename R >
    friend class forwardConstIterator;
    template< typename K, typename V, typename C >
    friend class Dictionary;
    NodeList< T >* node;
  };
}

template< class T >
mashkin::forwardIterator< T >::forwardIterator():
  node(nullptr)
{
}

template< class T >
mashkin::forwardIterator< T >::forwardIterator(NodeList< T >* lhs)
{
  node = lhs;
}

template< class T >
mashkin::forwardIterator< T >& mashkin::forwardIterator< T >::operator++()
{
  assert(node != nullptr);
  node = node->next;
  return *this;
}

template< class T >
mashkin::forwardIterator< T > mashkin::forwardIterator< T >::operator++(int)
{
  assert(node != nullptr);
  forwardIterator< T > res(*this);
  ++(*this);
  return res;
}

template< class T >
bool mashkin::forwardIterator< T >::operator==(const forwardIterator< T >& rhs) const
{
  return node == rhs.node;
}

template< class T >
bool mashkin::forwardIterator< T >::operator!=(const forwardIterator< T >& rhs) const
{
  return !(rhs == *this);
}

template< class T >
T& mashkin::forwardIterator< T >::operator*()
{
  assert(node != nullptr);
  return node->data;
}

template< class T >
T* mashkin::forwardIterator< T >::operator->()
{
  assert(node != nullptr);
  return std::addressof(node->data);
}
#endif
