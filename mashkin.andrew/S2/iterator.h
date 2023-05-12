#ifndef ITERATOR_H
#define ITERATOR_H
#include <cassert>
#include <memory>
#include "forwardList.h"

namespace mashkin
{
  template< class T >
  struct Iterator: public std::iterator< std::forward_iterator_tag, T >
  {
    ForwardList< T >* node;

    Iterator();
    ~Iterator() = default;
    Iterator(const Iterator< T >&) = default;

    Iterator< T >& operator=(const ForwardList< T >&) = default;
    Iterator< T >& operator++();
    Iterator< T > operator++(int);

    T& operator*();
    T& operator*() const;
    T* operator->();
    T* operator->() const;

    bool operator!=(const ForwardList< T >& rhs) const;
    bool operator==(const ForwardList< T >& rhs) const;
  };
}

template< class T >
mashkin::Iterator< T >::Iterator():
  node(nullptr)
{
}

template< class T >
mashkin::Iterator< T >& mashkin::Iterator< T >::operator++()
{
  assert(node != nullptr);
  node = node->next;
}

template< class T >
mashkin::Iterator< T > mashkin::Iterator< T >::operator++(int)
{
  assert(node != nullptr);
  Iterator< T > res(*this);
  ++(*this);
  return res;
}

template< class T >
bool mashkin::Iterator< T >::operator==(const ForwardList< T >& rhs) const
{
  return node == rhs.node;
}

template< class T >
bool mashkin::Iterator< T >::operator!=(const ForwardList< T >& rhs) const
{
  return !(rhs == *this);
}

template< class T >
T& mashkin::Iterator< T >::operator*()
{
  assert(node != nullptr);
  return node->data;
}

template< class T >
T* mashkin::Iterator< T >::operator->()
{
  assert(node != nullptr);
  return std::addressof(node->data);
}

template< class T >
T& mashkin::Iterator< T >::operator*() const
{
  return this->operator*();
}

template< class T >
T* mashkin::Iterator< T >::operator->() const
{
  return this->operator->();
}
#endif
