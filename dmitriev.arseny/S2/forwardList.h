#ifndef FORWARDLSIT_H
#define FORWARDLSIT_H

#include "forwardIterator.h"

namespace dmitriev
{
  template< typename T >
  class ForwardList
  {
  public:
    ForwardList();
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
dmitriev::ForwardList< T >::~ForwardList()
{
  clear(m_FakeNode->otherList);
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

#endif
