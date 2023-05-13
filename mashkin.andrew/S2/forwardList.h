#ifndef FORWARDLIST_H
#define FORWARDLIST_H
#include <stdexcept>
#include "constIterator.h"
#include "iterator.h"
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

    T& front();
    void push_front(const T& value);
    void pop_front();

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
mashkin::ForwardList< T >::ForwardList(ForwardList< T >&& rhs):
  head(rhs.head),
  tail(rhs.tail)
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
    NodeList< T >* var = new NodeList< T >{value, head};
    head = var;
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
  return iter(tail->next);
}

template< class T >
mashkin::ConstIterator< T > mashkin::ForwardList< T >::cbegin() noexcept
{
  return citer(head);
}

template< class T >
mashkin::ConstIterator< T > mashkin::ForwardList< T >::cend() noexcept
{
  return citer(tail->next);
}

template< class T >
T& mashkin::ForwardList< T >::front()
{
  return *this->begin();
}

template< class T >
void mashkin::ForwardList< T >::pop_front()
{
  if (!head)
  {
    throw std::out_of_range("You got the end of list");
  }
  NodeList< T >* toDel = head;
  head = head->next;
  delete toDel;
}

#endif
