#ifndef S2_FORWARDCONSTITERATOR_H
#define S2_FORWARDCONSTITERATOR_H
#include <cassert>
#include <memory>
#include <list.h>
#include "ForwardIterator.h"
#include "dictionary.h"
#include "forwardList.h"

namespace mashkin
{
  template< class T >
  class ForwardConstIterator: public std::iterator< std::forward_iterator_tag, T >
  {
  public:
    ForwardConstIterator();
    ~ForwardConstIterator() = default;
    ForwardConstIterator(const ForwardConstIterator< T >&) = default;
    ForwardConstIterator(const ForwardIterator< T >& rhs);

    ForwardConstIterator< T >& operator=(const ForwardConstIterator< T >&) = default;
    ForwardConstIterator< T >& operator++();
    ForwardConstIterator< T > operator++(int);

    T& operator*() const;
    T* operator->() const;

    bool operator!=(const ForwardConstIterator< T >& rhs) const;
    bool operator==(const ForwardConstIterator< T >& rhs) const;

  private:
    template< typename U >
    friend class ForwardList;
    template< typename K, typename V, typename C >
    friend class Dictionary;
    list_t< T >* node;
    ForwardConstIterator(list_t< T >* rhs);
  };
}

template< class T >
mashkin::ForwardConstIterator< T >::ForwardConstIterator():
  node(nullptr)
{
}

template< class T >
mashkin::ForwardConstIterator< T >::ForwardConstIterator(list_t< T >* lhs)
{
  node = lhs;
}

template< class T >
mashkin::ForwardConstIterator< T >::ForwardConstIterator(const mashkin::ForwardIterator< T >& rhs):
  node(rhs.node)
{
}

template< class T >
mashkin::ForwardConstIterator< T >& mashkin::ForwardConstIterator< T >::operator++()
{
  assert(node != nullptr);
  node = node->next;
  return *this;
}

template< class T >
mashkin::ForwardConstIterator< T > mashkin::ForwardConstIterator< T >::operator++(int)
{
  assert(node != nullptr);
  ForwardConstIterator< T > res(*this);
  ++(*this);
  return res;
}

template< class T >
bool mashkin::ForwardConstIterator< T >::operator==(const ForwardConstIterator< T >& rhs) const
{
  return node == rhs.node;
}

template< class T >
bool mashkin::ForwardConstIterator< T >::operator!=(const ForwardConstIterator< T >& rhs) const
{
  return !(rhs == *this);
}

template< class T >
T& mashkin::ForwardConstIterator< T >::operator*() const
{
  assert(node != nullptr);
  return node->data;
}

template< class T >
T* mashkin::ForwardConstIterator< T >::operator->() const
{
  assert(node != nullptr);
  return std::addressof(node->data);
}
#endif
