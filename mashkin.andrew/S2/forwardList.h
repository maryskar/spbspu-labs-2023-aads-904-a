#ifndef FORWARDLIST_H
#define FORWARDLIST_H
#include "iterator.h"
#include "constIterator.h"
#include "nodeList.h"

namespace mashkin
{
  template< class T >
  class ForwardList
  {
  public:
    using iter = mashkin::Iterator< T >;
    using citer = mashkin::ConstIterator< T >;
    ForwardList();
    ForwardList(const ForwardList< T >& lhs);
    ForwardList(ForwardList< T >&& rhs);

    Iterator< T > begin() noexcept;
    Iterator< T > end() noexcept;

    ConstIterator< T > cbegin() noexcept;
    ConstIterator< T > cend() noexcept;

    void push_front(const T& value);
    T pop();

    bool empty() const noexcept;

  private:
    NodeList< T >* head;
    NodeList< T >* tail;
  };
}

template< class T >
mashkin::ForwardList< T >::ForwardList():
  head(nullptr),
  tail(nullptr)
{
}

template< class T >
mashkin::ForwardList< T >::ForwardList(const ForwardList< T >& lhs):
  head(lhs.head),
  tail(lhs.tail)
{
}

template< class T >
void mashkin::ForwardList< T >::push_front(const T& value)
{
  if (empty())
  {
    head = new NodeList< T >{value, nullptr};
    tail = head;
  }
  else
  {
    tail->next = new NodeList< T >{value, nullptr};
    tail = tail->next;
  }
}

template< class T >
bool mashkin::ForwardList< T >::empty() const noexcept
{
  return !head;
}

template< class T >
mashkin::Iterator< T > mashkin::ForwardList< T >::begin() noexcept
{
  return iter(head);
}

template< class T >
mashkin::Iterator< T > mashkin::ForwardList< T >::end() noexcept
{
  iter it(tail);
  return ++it;
}

template< class T >
mashkin::ConstIterator< T > mashkin::ForwardList< T >::cbegin() noexcept
{
  return citer(head);
}
#endif
