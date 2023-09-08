#ifndef ITERATOR_H
#define ITERATOR_H
#include <cassert>
#include <memory>
#include "ForwardConstIterator.h"
#include "dictionary.h"
#include "nodeList.h"

namespace mashkin
{
  template< class T >
  class ForwardIterator: public std::iterator< std::forward_iterator_tag, T >
  {
  public:
    ForwardIterator();
    ~ForwardIterator() = default;
    ForwardIterator(const ForwardIterator< T >&) = default;
    ForwardIterator(NodeList< T >* rhs);

    ForwardIterator< T >& operator=(const ForwardIterator< T >&) = default;
    ForwardIterator< T >& operator++();
    ForwardIterator< T > operator++(int);

    T& operator*();
    T* operator->();

    bool operator!=(const ForwardIterator< T >& rhs) const;
    bool operator==(const ForwardIterator< T >& rhs) const;

  private:
    template< typename U >
    friend class ForwardList;
    template< typename R >
    friend class ForwardConstIterator;
    template< typename K, typename V, typename C >
    friend class Dictionary;
    NodeList< T >* node;
  };
}

template< class T >
mashkin::ForwardIterator< T >::ForwardIterator():
  node(nullptr)
{
}

template< class T >
mashkin::ForwardIterator< T >::ForwardIterator(NodeList< T >* lhs)
{
  node = lhs;
}

template< class T >
mashkin::ForwardIterator< T >& mashkin::ForwardIterator< T >::operator++()
{
  assert(node != nullptr);
  node = node->next;
  return *this;
}

template< class T >
mashkin::ForwardIterator< T > mashkin::ForwardIterator< T >::operator++(int)
{
  assert(node != nullptr);
  ForwardIterator< T > res(*this);
  ++(*this);
  return res;
}

template< class T >
bool mashkin::ForwardIterator< T >::operator==(const ForwardIterator< T >& rhs) const
{
  return node == rhs.node;
}

template< class T >
bool mashkin::ForwardIterator< T >::operator!=(const ForwardIterator< T >& rhs) const
{
  return !(rhs == *this);
}

template< class T >
T& mashkin::ForwardIterator< T >::operator*()
{
  assert(node != nullptr);
  return node->data;
}

template< class T >
T* mashkin::ForwardIterator< T >::operator->()
{
  assert(node != nullptr);
  return std::addressof(node->data);
}
#endif
