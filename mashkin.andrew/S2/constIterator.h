#ifndef S2_CONSTITERATOR_H
#define S2_CONSTITERATOR_H
#include <cassert>
#include <memory>
#include "nodeList.h"

namespace mashkin
{
  template< class T >
  struct ConstIterator: public std::iterator< std::forward_iterator_tag, T >
  {
    NodeList< T >* node;

    ConstIterator();
    ~ConstIterator() = default;
    ConstIterator(const ConstIterator< T >&) = default;
    ConstIterator(NodeList< T >* rhs);

    ConstIterator< T >& operator=(const ConstIterator< T >&) = default;
    ConstIterator< T >& operator++();
    ConstIterator< T > operator++(int);

    T& operator*() const;
    T* operator->() const;

    bool operator!=(const ConstIterator< T >& rhs) const;
    bool operator==(const ConstIterator< T >& rhs) const;
  };
}

template< class T >
mashkin::ConstIterator< T >::ConstIterator():
  node(nullptr)
{
}

template< class T >
mashkin::ConstIterator< T >::ConstIterator(NodeList< T >* lhs)
{
  node = lhs;
}


template< class T >
mashkin::ConstIterator< T >& mashkin::ConstIterator< T >::operator++()
{
  assert(node != nullptr);
  node = node->next;
}

template< class T >
mashkin::ConstIterator< T > mashkin::ConstIterator< T >::operator++(int)
{
  assert(node != nullptr);
  ConstIterator< T > res(*this);
  ++(*this);
  return res;
}

template< class T >
bool mashkin::ConstIterator< T >::operator==(const ConstIterator< T >& rhs) const
{
  return node == rhs.node;
}

template< class T >
bool mashkin::ConstIterator< T >::operator!=(const ConstIterator< T >& rhs) const
{
  return !(rhs == *this);
}

template< class T >
T& mashkin::ConstIterator< T >::operator*() const
{
  assert(node != nullptr);
  return node->data;
}

template< class T >
T* mashkin::ConstIterator< T >::operator->() const
{
  assert(node != nullptr);
  return std::addressof(node->data);
}
#endif
