#ifndef S2_FORWARDCONSTITERATOR_H
#define S2_FORWARDCONSTITERATOR_H
#include <cassert>
#include <memory>
#include "dictionary.h"
#include "forwardIterator.h"
#include "forwardList.h"
#include "nodeList.h"

namespace mashkin
{
  template< class T >
  class forwardConstIterator: public std::iterator< std::forward_iterator_tag, T >
  {
  public:
    forwardConstIterator();
    ~forwardConstIterator() = default;
    forwardConstIterator(const forwardConstIterator< T >&) = default;
    forwardConstIterator(NodeList< T >* rhs);
    forwardConstIterator(const forwardIterator< T >& rhs);

    forwardConstIterator< T >& operator=(const forwardConstIterator< T >&) = default;
    forwardConstIterator< T >& operator++();
    forwardConstIterator< T > operator++(int);

    T& operator*() const;
    T* operator->() const;

    bool operator!=(const forwardConstIterator< T >& rhs) const;
    bool operator==(const forwardConstIterator< T >& rhs) const;

  private:
    template< typename U >
    friend class ForwardList;
    template< typename K, typename V, typename C >
    friend class Dictionary;
    NodeList< T >* node;
  };
}

template< class T >
mashkin::forwardConstIterator< T >::forwardConstIterator():
  node(nullptr)
{
}

template< class T >
mashkin::forwardConstIterator< T >::forwardConstIterator(NodeList< T >* lhs)
{
  node = lhs;
}

template< class T >
mashkin::forwardConstIterator< T >::forwardConstIterator(const mashkin::forwardIterator< T >& rhs):
  node(rhs.node)
{
}

template< class T >
mashkin::forwardConstIterator< T >& mashkin::forwardConstIterator< T >::operator++()
{
  assert(node != nullptr);
  node = node->next;
  return *this;
}

template< class T >
mashkin::forwardConstIterator< T > mashkin::forwardConstIterator< T >::operator++(int)
{
  assert(node != nullptr);
  forwardConstIterator< T > res(*this);
  ++(*this);
  return res;
}

template< class T >
bool mashkin::forwardConstIterator< T >::operator==(const forwardConstIterator< T >& rhs) const
{
  return node == rhs.node;
}

template< class T >
bool mashkin::forwardConstIterator< T >::operator!=(const forwardConstIterator< T >& rhs) const
{
  return !(rhs == *this);
}

template< class T >
T& mashkin::forwardConstIterator< T >::operator*() const
{
  assert(node != nullptr);
  return node->data;
}

template< class T >
T* mashkin::forwardConstIterator< T >::operator->() const
{
  assert(node != nullptr);
  return std::addressof(node->data);
}
#endif
