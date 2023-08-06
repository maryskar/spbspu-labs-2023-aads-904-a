#ifndef FORWARDLSIT_H
#define FORWARDLSIT_H

#include <iostream>//временно
#include <iterator>
#include <C:\Users\BlackEvery\source\repos\spbspu-labs-2023-aads-904-a\dmitriev.arseny\common\list.h>//шакалаки со средой разработки

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
  class ForwardList;

  template< typename T >
  class ConstForwardIterator;

  template< typename T >
  class ForwardIterator: public std::iterator< std::forward_iterator_tag, T >
  {
  public:
    friend ForwardList< T >;
    friend ConstForwardIterator< T >;

    using list = List< T >;

    ForwardIterator():
      m_ptr(nullptr)
    {}
    ForwardIterator(list* ptr) noexcept:
      m_ptr(ptr)
    {}

    ForwardIterator& operator++()
    {
      if (isEmpty())
      {
        throw std::logic_error("inc nullptr");
      }
      m_ptr = m_ptr->otherList;

      return *this;
    }
    ForwardIterator& operator++(int)
    {
      if (isEmpty())
      {
        throw std::logic_error("inc nullptr");
      }
      ForwardIterator< T > currentIterator = *this;
      ++(*this);
      return currentIterator;
    }

    bool operator==(const ForwardIterator& other) const
    {
      return m_ptr == other.m_ptr;
    }
    bool operator!=(const ForwardIterator& other) const
    {
      return !(*this == other);
    }

    T& operator*()
    {
      if (isEmpty())
      {
        throw std::logic_error("inc nullptr");
      }
      return m_ptr->data;
    }
    T* operator->()
    {
      if (isEmpty())
      {
        throw std::logic_error("inc nullptr");
      }
      return std::addressof(m_ptr->data);
    }

    bool isEmpty()
    {
      return m_ptr == nullptr;
    }

  private:
    list* m_ptr;

  };

  template< typename T >
  class ConstForwardIterator: public std::iterator< std::forward_iterator_tag, const T >
  {
  public:
    friend ForwardList< T >;

    using list = List< T >;
    using iterator = ForwardIterator< T >;

    ConstForwardIterator():
      m_ptr(nullptr)
    {}
    ConstForwardIterator(const list* ptr):
      m_ptr(ptr)
    {}

    ConstForwardIterator(const iterator& other):
      m_ptr(other.m_ptr)
    {}
    ConstForwardIterator(iterator&& other):
      m_ptr(other.m_ptr)
    {}

    ConstForwardIterator& operator++()
    {
      if (isEmpty())
      {
        throw std::logic_error("inc nullptr");
      }
      m_ptr = m_ptr->otherList;
      return *this;
    }
    ConstForwardIterator& operator++(int)
    {
      if (isEmpty())
      {
        throw std::logic_error("inc nullptr");
      }
      ConstForwardIterator< T > currPtr = *this;
      m_ptr = m_ptr->otherList;
      return currPtr;
    }

    bool operator==(const ConstForwardIterator& other) const
    {
      return m_ptr == other.m_ptr;
    }
    bool operator!=(const ConstForwardIterator& other) const
    {
      return !(*this == other);
    }

    const T& operator*() const
    {
      if (isEmpty())
      {
        throw std::logic_error("inc nullptr");
      }
      return m_ptr->data;
    }
    const T* operator->() const
    {
      if (isEmpty())
      {
        throw std::logic_error("inc nullptr");
      }
      return std::addressof(m_ptr->data);
    }

    bool isEmpty()
    {
      return m_ptr == nullptr;
    }

  private:
    const list* m_ptr;

  };


  template< typename T >
  class ForwardList
  {
  public:
    using list = dmitriev::List< T >;
    using iterator = ForwardIterator< T >;
    using constIterator = ConstForwardIterator< T >;

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
      if (isEmtpy())
      {
        throw std::logic_error("try to get data from empty list");
      }
      return m_beforeHead->otherList->data;
    }
    T& front()
    {
      if (isEmtpy())
      {
        throw std::logic_error("try to get data from empty list");
      }
      return m_beforeHead->otherList->data;
    }

    void popFront()
    {
      if (isEmtpy())
      {
        throw std::logic_error("try to pop data from empty list");
      }
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

    iterator beforeBegin()
    {
      return iterator(m_beforeHead);
    }
    iterator begin()
    {
      return iterator(m_beforeHead->otherList);
    }
    iterator end()
    {
      return iterator();
    }

    constIterator constBeforeBegin()
    {
      return constIterator(m_beforeHead);
    }
    constIterator constBegin()
    {
      return constIterator(m_beforeHead->otherList);
    }
    constIterator constEnd()
    {
      return constIterator();
    }

    iterator insertAfter(constIterator pos, const T& data)
    {
      if (pos.isEmpty())
      {
        throw std::logic_error("empty iter");
      }
      list* changeablePos = const_cast< list* >(pos.m_ptr);
      list* newList = new list{data, changeablePos->otherList};
      changeablePos->otherList = newList;

      return iterator(changeablePos->otherList);
    }
    iterator insertAfter(constIterator pos, T&& data)
    {
      if (pos.isEmpty())
      {
        throw std::logic_error("empty iter");
      }
      list* changeablePos = const_cast< list* >(pos.m_ptr);
      list* newList = new list{std::move(data), changeablePos->otherList};
      changeablePos->otherList = newList;

      return iterator(changeablePos->otherList);
    }
    iterator insertAfter(constIterator pos, size_t count, const T& data)
    {
      if (pos.isEmpty())
      {
        throw std::logic_error("empty iter");
      }
      iterator changeablePos(const_cast< list* >(pos.m_ptr));

      for (size_t i = 0; i < count; i++)
      {
        changeablePos = insertAfter(changeablePos, data);
      }

      return changeablePos;
    }
    template< class inputIterator >
    iterator insertAfter(constIterator pos, inputIterator first, inputIterator last)
    {
      if (pos.isEmpty())
      {
        throw std::logic_error("empty iter");
      }
      iterator changeablePos(const_cast< list* >(pos.m_ptr));

      for (; first != last; ++first)
      {
        changeablePos = insertAfter(changeablePos, *first);
      }

      return changeablePos;
    }
    iterator insertAfter(constIterator pos, std::initializer_list< T > ilist)
    {
      if (pos.m_ptr == nullptr)
      {
        throw std::logic_error("null iter");
      }

      return insertAfter(pos, ilist.begin(), ilist.end());
    }

    iterator eraseAfter(constIterator pos)
    {
      if (pos.m_ptr == nullptr)
      {
        throw std::logic_error("null iter");
      }

      list* changeablePos = const_cast< list* >(pos.m_ptr);
      list* current = const_cast< list* >(changeablePos->otherList);

      changeablePos->otherList = current->otherList;
      delete current;

      return iterator(changeablePos->otherList);
    }
    iterator eraseAfter(constIterator beforeFirst, constIterator last)
    {
      while(beforeFirst.m_ptr->otherList != last.m_ptr)
      {
        eraseAfter(beforeFirst);
      }

      return iterator(const_cast< list* >(beforeFirst.m_ptr));
    }

    template< class... Args >
    iterator emplaceAfter(constIterator pos, Args&&... args)
    {
      if (pos.m_ptr == nullptr)
      {
        throw std::logic_error("null iter");
      }

      return insertAfter(pos, {std::forward< Args >(args)...});
    }
    template< class... Args >
    void emplaceFront(Args&&... args)
    {
      insertAfter(beforeBegin(), {std::forward< Args >(args)...});
    }

    void swap(ForwardList& other)
    {
      std::swap(m_beforeHead->otherList, other.m_beforeHead->otherList);
    }
    
    void spliceAfter(constIterator pos, ForwardList& other)
    {
      if (pos.m_ptr == nullptr)
      {
        throw std::logic_error("null iter");
      }
      if (this == std::addressof(other))
      {
        return;
      }

      iterator changablePos = const_cast< list* >(pos.m_ptr);
      list* current = changablePos.m_ptr->otherList;

      changablePos.m_ptr->otherList = other.m_beforeHead->otherList;

      while (changablePos.m_ptr->otherList)
      {
        changablePos++;
      }

      changablePos.m_ptr->otherList = current;
      other.m_beforeHead->otherList = nullptr;
    }
    void spliceAfter(constIterator pos, ForwardList&& other)
    {
      spliceAfter(pos, other);
    }
    void spliceAfter(constIterator pos, ForwardList& other, constIterator it)
    {
      if (pos.m_ptr == nullptr)
      {
        throw std::logic_error("null iter");
      }
      if (pos == it || pos.m_ptr == it.m_ptr->otherList)
      {
        return;
      }

      iterator changablePos = const_cast< list* >(pos.m_ptr);
      iterator changableIt = const_cast< list* >(it.m_ptr);

      list* tail1 = changablePos.m_ptr->otherList;
      list* tail2 = changableIt.m_ptr->otherList->otherList;

      changablePos.m_ptr->otherList = changableIt.m_ptr->otherList;

      changablePos.m_ptr->otherList->otherList = tail1;
      changableIt.m_ptr->otherList = tail2;
    }
    void spliceAfter(constIterator pos, ForwardList&& other, constIterator it)
    {
      spliceAfter(pos, other, it);
    }
    void spliceAfter(constIterator pos, ForwardList& other, constIterator beforeFirst, constIterator last)
    {
      if (pos.m_ptr == nullptr)
      {
        throw std::logic_error("null iter");
      }


      iterator changablePos = const_cast< list* >(pos.m_ptr);
      iterator changableFirst = const_cast< list* >(beforeFirst.m_ptr);
      iterator changableLast = const_cast< list* >(last.m_ptr);

      list* tail1 = changablePos.m_ptr->otherList;
      list* tail2 = changableLast.m_ptr->otherList;

      changablePos.m_ptr->otherList = changableFirst.m_ptr->otherList;

      changableFirst.m_ptr->otherList = tail2;
      changableLast.m_ptr->otherList = tail1;
    }
    void spliceAfter(constIterator pos, ForwardList&& other, constIterator beforeFirst, constIterator last)
    {
      spliceAfter(pos, other, beforeFirst, last);
    }

    size_t remove(const T& value)
    {
      size_t count = 0;

      for (iterator it = beforeBegin(); it != end(); it++)
      {
        if (it.m_ptr->otherList->data == value)
        {
          eraseAfter(it);
          count++;
        }
      }

      return count;
    }
    template< class UnaryPredicate >
    size_t removeIf(UnaryPredicate p)
    {
      size_t count = 0;

      for (iterator it = beforeBegin(); it != end(); it++)
      {
        if (p(it.m_ptr->otherList->data))
        {
          eraseAfter(it);
          count++;
        }
      }

      return count;
    }

    void reverse() noexcept
    {
      list* top = m_beforeHead->otherList;
      list* tail = top;
      list* val = nullptr;

      while (tail->otherList != nullptr)
      {
        m_beforeHead->otherList = tail->otherList;
        val = tail->otherList->otherList;
        tail->otherList->otherList = top;
        tail->otherList = val;

        top = m_beforeHead->otherList;
      }
    }

  private:
    list* m_beforeHead;

  };
}

#endif
