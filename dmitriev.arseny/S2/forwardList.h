#ifndef FORWARDLSIT_H
#define FORWARDLSIT_H

#include "forwardIterator.h"

namespace
{
  template< typename T >
  dmitriev::List< T >* headInit(dmitriev::List< T >* otherHead)
  {
    dmitriev::List< T >* newBeforeHead = static_cast< dmitriev::List< T >* >(::operator new (sizeof(dmitriev::List< T >)));
    newBeforeHead->otherList = otherHead;

    return newBeforeHead;
  }

  template< typename T >
  dmitriev::List< T >* copyForwardList(dmitriev::List< T >* otherHead)
  {
    std::pair< dmitriev::List< T >*, dmitriev::List< T >* > headTail;
    headTail = dmitriev::copy(otherHead);

    return headInit(headTail.first);
  }
}

namespace dmitriev
{
  template< typename T >
  class ForwardList
  {
  public:
    using list = dmitriev::List< T >;

    ForwardList():
      m_beforeHead(static_cast< list* >(::operator new (sizeof(list))))
    {
      m_beforeHead->otherList = nullptr;
    }
    ForwardList(const ForwardList< T >& other):
      m_beforeHead(copyForwardList(other.m_beforeHead->otherList))
    {}
    ForwardList(ForwardList< T >&& other):
      m_beforeHead(headInit(other.m_beforeHead->otherList))
    {
      other.m_beforeHead->otherList = nullptr;
    }

    ForwardList< T >& operator=(const ForwardList< T >& other)
    {
      if (this == std::addressof(other))
      {
        return *this;
      }
      ForwardList < T > newForwardList = other;
      *this = std::move(newForwardList);

      return *this;
    }
    ForwardList< T >& operator=(ForwardList< T >&& other)
    {
      if (this == std::addressof(other))
      {
        return *this;
      }
      clear(m_beforeHead->otherList);
      m_beforeHead->otherList = other.m_beforeHead->otherList;
      other.m_beforeHead->otherList = nullptr;

      return *this;
    }

    ~ForwardList()
    {
      dmitriev::clear(m_beforeHead);
    }

    void pushFront(const T& data)
    {
      list* newHead = new list{data, m_beforeHead->otherList};
      m_beforeHead->otherList = newHead;
    }
    void pushFront(T&& data)
    {
      list* newHead = new list{std::move(data), m_beforeHead->otherList};
      m_beforeHead->otherList = newHead;
    }

    const T& front() const
    {
      return m_beforeHead->otherList->data;
    }
    T& front()
    {
      return m_beforeHead->otherList->data;
    }

    void popFront()
    {
      list* newHead = m_beforeHead->otherList->otherList;
      delete m_beforeHead->otherList;

      m_beforeHead->otherList = newHead;
    }

    bool isEmtpy()
    {
      return m_beforeHead->otherList == nullptr;
    }
    void clear()
    {
      dmitriev::clear(m_beforeHead->otherList);
    }

  private:
    list* m_beforeHead;

  };
}



#endif
