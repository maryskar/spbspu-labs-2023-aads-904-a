#ifndef FORWARDLSIT_H
#define FORWARDLSIT_H

#include "forwardIterator.h"

namespace
{
  template< typename T >
  dmitriev::List< T >* copyForwardList(dmitriev::List< T >* otherFakeNode)
  {
    std::pair< dmitriev::List< T >*, dmitriev::List< T >* > headTail;
    headTail = dmitriev::copy(otherFakeNode);

    return headTail.first;
  }
}

namespace dmitriev
{
  template< typename T >
  class ForwardList
  {
  public:
    ForwardList();
    ForwardList(ForwardList< T >&& other);
    ForwardList(const ForwardList< T >& other);

    ForwardList< T >& operator=(ForwardList< T >&& other);
    ForwardList< T >& operator=(const ForwardList< T >& other);

    ~ForwardList();

    void pushFront(const T& data);
    void pushFront(T&& data);

    const T& front() const;
    T& front();

    void popFront();

    ForwardIterator< T > beforBegin();
    ForwardIterator< T > begin();
    ForwardIterator< T > end();

    ConstForwardIterator< T > beforBeginConst();
    ConstForwardIterator< T > beginConst();
    ConstForwardIterator< T > endConst();

    bool isEmtpy();

    void clear();
    //insertAfter();
    //emplaceAfter();
    //eraceAfter();
    //emplaceFront();
    //resize();
    //swap();

    //spliceAfter();
    //remove();
    //removeIf();
    //revrese();

    //operator==();
    //operator!=();

    //std::swap(ForwardList)//?

  private:
    dmitriev::List< T >* m_FakeNode;
    //  size_t size;

  };
}

template< typename T >
dmitriev::ForwardList< T >::ForwardList():
  m_FakeNode(new dmitriev::List< T >{T(), nullptr})//может не быть деф констр
{}

template< typename T >
dmitriev::ForwardList< T >::ForwardList(ForwardList< T >&& other):
  m_FakeNode(other.m_FakeNode)
{
  other.m_FakeNode = nullptr;
}

template< typename T >
dmitriev::ForwardList< T >::ForwardList(const ForwardList< T >& other):
  m_FakeNode(copyForwardList(other.m_FakeNode))
{}

template< typename T >
dmitriev::ForwardList< T >& dmitriev::ForwardList< T >::operator=(ForwardList< T >&& other)
{
  if (this == std::addressof(other))
  {
    return *this;
  }
  clear(m_FakeNode->otherList);
  m_FakeNode->otherList = other.m_FakeNode->otherList;
  other.m_FakeNode->otherList = nullptr;

  return *this;
}

template< typename T >
dmitriev::ForwardList< T >& dmitriev::ForwardList< T >::operator=(const ForwardList< T >& other)
{
  if (this == std::addressof(other))
  {
    return *this;
  }
  ForwardList < T > newForwardList = other;
  *this = std::move(newForwardList);

  return *this;
}

template< typename T >
dmitriev::ForwardList< T >::~ForwardList()
{
  dmitriev::clear(m_FakeNode);
}

template< typename T >
void dmitriev::ForwardList< T >::pushFront(const T& data)
{
  dmitriev::List< T >* newHead = new dmitriev::List< T >{data, m_FakeNode->otherList};
  m_FakeNode->otherList = newHead;
}

template< typename T >
void dmitriev::ForwardList< T >::pushFront(T&& data)
{
  dmitriev::List< T >* newHead = new dmitriev::List< T >{std::move(data), m_FakeNode->otherList};
  m_FakeNode->otherList = newHead;
}

template< typename T >
const T& dmitriev::ForwardList< T >::front() const
{
  return m_FakeNode->otherList->data;
}

template< typename T >
T& dmitriev::ForwardList< T >::front()
{
  return m_FakeNode->otherList->data;
}

template< typename T >
void dmitriev::ForwardList< T >::popFront()
{
  dmitriev::List< T >* newHead = m_FakeNode->otherList->otherList;
  delete m_FakeNode->otherList;

  m_FakeNode->otherList = newHead;
}

template< typename T >
dmitriev::ForwardIterator< T > dmitriev::ForwardList< T >::beforBegin()
{
  return ForwardIterator< T >(m_FakeNode);
}

template< typename T >
dmitriev::ForwardIterator< T > dmitriev::ForwardList< T >::begin()
{
  return ForwardIterator< T >(m_FakeNode->otherList);
}

template< typename T >
dmitriev::ForwardIterator< T > dmitriev::ForwardList< T >::end()
{
  return ForwardIterator< T >(nullptr);
}

template< typename T >
dmitriev::ConstForwardIterator< T > dmitriev::ForwardList< T >::beforBeginConst()
{
  return ConstForwardIterator< T >(m_FakeNode);
}

template< typename T >
dmitriev::ConstForwardIterator< T > dmitriev::ForwardList< T >::beginConst()
{
  return ConstForwardIterator< T >(m_FakeNode->otherList);
}

template< typename T >
dmitriev::ConstForwardIterator< T > dmitriev::ForwardList< T >::endConst()
{
  return ConstForwardIterator< T >(nullptr);
}

template< typename T >
bool dmitriev::ForwardList< T >::isEmtpy()
{
  return m_FakeNode->otherList == nullptr;
}

template< typename T >
void dmitriev::ForwardList< T >::clear()
{
  dmitriev::clear(m_FakeNode->otherList);
}



#endif
