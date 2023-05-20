#ifndef FORWARDLIST_H
#define FORWARDLIST_H
#include <stdexcept>
#include "constIterator.h"
#include "iterator.h"
#include "nodeList.h"



namespace mashkin
{
  template< class T >
  class ConstIterator;
  template< class T >
  class ForwardList
  {
  public:
    using iter = mashkin::Iterator< T >;
    using citer = mashkin::ConstIterator< T >;
    ForwardList();
    ForwardList(const ForwardList< T >& lhs);
    ForwardList(ForwardList< T >&& rhs) noexcept;

    Iterator< T > begin() noexcept;
    Iterator< T > end() noexcept;

    ConstIterator< T > cbegin() noexcept;
    ConstIterator< T > cend() noexcept;

    T& front();
    void push_front(const T& value);
    void pop_front();

    Iterator< T > erase_after(citer pos);
    Iterator< T > erase_after(citer pos, citer last);

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
mashkin::ForwardList< T >::ForwardList(ForwardList< T >&& rhs) noexcept:
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
    auto var = new NodeList< T >{value, head};
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
  if (empty())
  {
    return iter(head);
  }
  return iter(tail->next);
}

template< class T >
mashkin::ConstIterator< T > mashkin::ForwardList< T >::cbegin() noexcept
{
  return begin();
}

template< class T >
mashkin::ConstIterator< T > mashkin::ForwardList< T >::cend() noexcept
{
  return end();
}

template< class T >
T& mashkin::ForwardList< T >::front()
{
  return *this->begin();
}

template< class T >
void mashkin::ForwardList< T >::pop_front()
{
  if (empty())
  {
    throw std::out_of_range("You got the end of list");
  }
  auto toDel = head;
  head = head->next;
  delete toDel;
}

template< class T >
mashkin::Iterator< T >  mashkin::ForwardList< T >::erase_after(citer pos)
{
  if (pos == cend())
  {
    return iter(pos.node);
  }
  auto toDel = pos.node->next;
  pos.node->next = pos.node->next->next;
  delete toDel;
  return iter(pos.node->next);
}

template< class T >
mashkin::Iterator< T > mashkin::ForwardList< T >::erase_after(citer pos, citer last)
{
  while (pos.node->next != last.node)
  {
    erase_after(pos);
  }
  return iter(pos.node->next);
}
#endif
