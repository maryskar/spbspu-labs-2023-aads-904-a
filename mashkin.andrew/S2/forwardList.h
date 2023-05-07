#ifndef FORWARDLIST_H
#define FORWARDLIST_H
#include "iterator.h"
#include "nodeList.h"

namespace mashkin
{
  template< class T >
  class ForwardList
  {
  public:
    ForwardList();
    ForwardList(const ForwardList< T >& lhs);
    ForwardList(ForwardList< T >&& rhs);
    Iterator< T > begin() noexcept;
    Iterator< T > end() noexcept;
    void push_front(const T& value);
    T pop();

    bool empty() const noexcept;

  private:
    nodeList< T >* head;
    nodeList< T >* tail;
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
    head = new nodeList< T >{value, nullptr};
    tail = head;
  }
  else
  {
    tail->next = new nodeList< T >{value, nullptr};
    tail = tail->next;
  }
}

template< class T >
bool mashkin::ForwardList< T >::empty() const noexcept
{
  return !head;
}
#endif
