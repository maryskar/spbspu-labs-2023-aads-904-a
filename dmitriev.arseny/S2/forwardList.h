#ifndef FORWARDLIST_H
#define FORWARDLIST_H

#include <list.h>
#include <iterator>

namespace
{
  template< typename T >
  dmitriev::List< T >* initFakeNode(dmitriev::List< T >* otherHead = nullptr)
  {
    dmitriev::List< T >* fakeNode = static_cast< dmitriev::List< T >* >(::operator new(sizeof(dmitriev::List< T >)));

    fakeNode->next = otherHead;
    return fakeNode;
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
    using constIterator = ConstForwardIterator< T >;

    ForwardIterator() noexcept:
      m_ptr(nullptr)
    {}
    explicit ForwardIterator(list* ptr) noexcept:
      m_ptr(ptr)
    {}

    ForwardIterator& operator++() noexcept
    {
      if (isEmpty(m_ptr))
      {
        return *this;
      }

      m_ptr = m_ptr->next;
      return *this;
    }
    ForwardIterator operator++(int) noexcept
    {
      if (isEmpty(m_ptr))
      {
        return *this;
      }

      ForwardIterator< T > currentIterator = *this;
      ++(*this);
      return currentIterator;
    }

    bool operator==(const ForwardIterator& other) const noexcept
    {
      return m_ptr == other.m_ptr;
    }
    bool operator!=(const ForwardIterator& other) const noexcept
    {
      return !(*this == other);
    }

    T& operator*()
    {
      return m_ptr->data;
    }
    T* operator->()
    {
      return std::addressof(m_ptr->data);
    }

  private:
    list* m_ptr;

    ForwardIterator(const constIterator& other):
      m_ptr(const_cast< list* >(other.m_ptr))
    {}
    ForwardIterator(constIterator&& other):
      m_ptr(const_cast< list* >(other.m_ptr))
    {}
  };

  template< typename T >
  class ConstForwardIterator: public std::iterator< std::forward_iterator_tag, const T >
  {
  public:
    friend ForwardList< T >;
    friend ForwardIterator< T >;

    using list = List< T >;
    using iterator = ForwardIterator< T >;

    ConstForwardIterator() noexcept:
      m_ptr(nullptr)
    {}
    explicit ConstForwardIterator(const list* ptr) noexcept:
      m_ptr(ptr)
    {}

    ConstForwardIterator(const iterator& other) noexcept:
      m_ptr(other.m_ptr)
    {}
    ConstForwardIterator(iterator&& other) noexcept:
      m_ptr(other.m_ptr)
    {}

    ConstForwardIterator& operator++() noexcept
    {
      if (isEmpty(m_ptr))
      {
        return *this;
      }

      m_ptr = m_ptr->next;
      return *this;
    }
    ConstForwardIterator operator++(int) noexcept
    {
      if (isEmpty(m_ptr))
      {
        return *this;
      }

      ConstForwardIterator< T > currPtr(*this);
      ++(*this);
      return currPtr;
    }

    bool operator==(const ConstForwardIterator& other) const noexcept
    {
      return m_ptr == other.m_ptr;
    }
    bool operator!=(const ConstForwardIterator& other) const noexcept
    {
      return !(*this == other);
    }

    const T& operator*() const
    {
      return m_ptr->data;
    }
    const T* operator->() const
    {
      return std::addressof(m_ptr->data);
    }

  private:
    const list* m_ptr;

  };

  template< typename T >
  class ForwardList
  {
  public:
    using list = List< T >;
    using iterator = ForwardIterator< T >;
    using constIterator = ConstForwardIterator< T >;

    ForwardList():
      m_beforeHead(::initFakeNode< T >())
    {}
    ForwardList(const ForwardList& other):
      m_beforeHead(::initFakeNode(dmitriev::copy(other.m_beforeHead->next).first))
    {}
    ForwardList(ForwardList&& other) noexcept:
      m_beforeHead(::initFakeNode(other.m_beforeHead->next))
    {
      other.m_beforeHead->next = nullptr;
    }
    ForwardList(std::initializer_list< T > iList):
      ForwardList()
    {
      insertAfter(constBeforeBegin(), iList);
    }
    ~ForwardList()
    {
      clear();
      ::operator delete(reinterpret_cast< void* >(m_beforeHead), sizeof(list));
    }

    ForwardList& operator=(const ForwardList& other)
    {
      if (this == std::addressof(other))
      {
        return *this;
      }
      ForwardList< T > newForwardList(other);
      *this = std::move(newForwardList);
      return *this;
    }
    ForwardList& operator=(ForwardList&& other)
    {
      if (this == std::addressof(other))
      {
        return *this;
      }
      clear();
      swap(other);
      return *this;
    }

    bool operator==(const ForwardList& other) const
    {
      if (std::addressof(m_beforeHead->next) == std::addressof(other.m_beforeHead->next))
      {
        return true;
      }

      constIterator thisIt = constBegin();
      constIterator otherIt = other.constBegin();

      for (; !dmitriev::isEmpty(thisIt.m_ptr) && !dmitriev::isEmpty(otherIt.m_ptr); thisIt++, otherIt++)
      {
        if (*thisIt != *otherIt)
        {
          return false;
        }
      }
      if (thisIt != otherIt)
      {
        return false;
      }
      else
      {
        return true;
      }

    }
    bool operator!=(const ForwardList& other) const
    {
      return !(*this == other);
    }

    size_t remove(const T& value)
    {
      size_t count = 0;

      for (iterator it = beforeBegin(); it.m_ptr->next != nullptr; it++)
      {
        if (it.m_ptr->next->data == value)
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

      for (iterator it = beforeBegin(); it.m_ptr->next != nullptr; it++)
      {
        if (p(it.m_ptr->next->data))
        {
          eraseAfter(it);
          count++;
        }
      }

      return count;
    }

    void popFront()
    {
      eraseAfter(constBeforeBegin());
    }

    iterator eraseAfter(constIterator pos)
    {
      throwIfIteratorEmpty(pos);
      throwIfIteratorEmpty(pos.m_ptr->next);

      iterator notConstPos(pos);
      iterator tail(notConstPos.m_ptr->next->next);
      delete notConstPos.m_ptr->next;
      notConstPos.m_ptr->next = tail.m_ptr;

      return tail;
    }
    iterator eraseAfter(constIterator first, constIterator last)
    {
      while (first.m_ptr->next != last.m_ptr)
      {
        eraseAfter(first);
      }

      return iterator(last);
    }

    void spliceAfter(constIterator pos, ForwardList& other)
    {
      if (this == std::addressof(other))
      {
        return;
      }
      throwIfIteratorEmpty(pos);

      iterator head(pos);
      iterator tail(head);

      tail++;
      head.m_ptr->next = other.m_beforeHead->next;
      while (!dmitriev::isEmpty(head.m_ptr->next))
      {
        head++;
      }

      head.m_ptr->next = tail.m_ptr;
      other.m_beforeHead->next = nullptr;
    }
    void spliceAfter(constIterator pos, ForwardList&& other)
    {
      spliceAfter(pos, other);
    }
    void spliceAfter(constIterator pos, ForwardList& other, constIterator it)
    {
      if (this == std::addressof(other))
      {
        return;
      }
      throwIfIteratorEmpty(pos);
      throwIfIteratorEmpty(it);
      if (pos == it || pos.m_ptr == it.m_ptr->next)
      {
        return;
      }

      iterator notConstPos(pos);
      iterator notConstIt(it);

      list* tail1 = notConstPos.m_ptr->next;
      list* tail2 = notConstIt.m_ptr->next->next;

      notConstPos.m_ptr->next = notConstIt.m_ptr->next;

      notConstPos.m_ptr->next->next = tail1;
      notConstIt.m_ptr->next = tail2;
    }
    void spliceAfter(constIterator pos, ForwardList&& other, constIterator it)
    {
      spliceAfter(pos, other, it);
    }
    void spliceAfter(constIterator pos, ForwardList& other, constIterator first, constIterator last)
    {
      throwIfIteratorEmpty(pos);
      throwIfIteratorEmpty(first);
      throwIfIteratorEmpty(last);

      iterator notConstPos(pos);
      iterator notConstFirst(first);
      iterator notConstLast(last);

      list* tail1 = notConstPos.m_ptr->next;
      list* tail2 = notConstLast.m_ptr->next;

      notConstPos.m_ptr->next = notConstFirst.m_ptr->next;

      notConstFirst.m_ptr->next = tail2;
      notConstLast.m_ptr->next = tail1;
    }
    void spliceAfter(constIterator pos, ForwardList&& other, constIterator first, constIterator last)
    {
      spliceAfter(pos, other, first, last);
    }

    template< typename... Args >
    iterator emplaceFront(Args&&... args)
    {
      return insertAfter(constBeforeBegin(), {std::forward< Args >(args)...});
    }

    template< typename... Args >
    iterator emplaceAfter(constIterator pos, Args&&... args)
    {
      return insertAfter(pos, {std::forward< Args >(args)...});
    }

    void pushFront(const T& data)
    {
      insertAfter(constBeforeBegin(), data);
    }
    void pushFront(T&& data)
    {
      insertAfter(constBeforeBegin(), std::move(data));
    }

    iterator insertAfter(constIterator pos, const T& data)
    {
      throwIfIteratorEmpty(pos);

      iterator notConstPos(pos);
      notConstPos.m_ptr->next = new list{data, notConstPos.m_ptr->next};
      return ++notConstPos;
    }
    iterator insertAfter(constIterator pos, T&& data)
    {
      throwIfIteratorEmpty(pos);

      iterator notConstPos(pos);
      notConstPos.m_ptr->next = new list{std::move(data), notConstPos.m_ptr->next};
      return ++notConstPos;
    }
    iterator insertAfter(constIterator pos, size_t count, const T& data)
    {
      throwIfIteratorEmpty(pos);
      iterator notConstPos(pos);

      for (size_t i = 0; i < count; i++)
      {
        notConstPos = insertAfter(notConstPos, data);
      }

      return notConstPos;
    }
    template< typename inputIterator >
    iterator insertAfter(constIterator pos, inputIterator first, inputIterator last)
    {
      throwIfIteratorEmpty(pos);
      iterator notConstPos(pos);

      while (first != last)
      {
        notConstPos = insertAfter(notConstPos, *first++);
      }

      return notConstPos;
    }
    iterator insertAfter(constIterator pos, std::initializer_list< T > iList)
    {
      throwIfIteratorEmpty(pos);

      return insertAfter(pos, iList.begin(), iList.end());
    }

    const T& front() const
    {
      throwIfIteratorEmpty(begin());

      return m_beforeHead->next->data;
    }
    T&& front()
    {
      throwIfIteratorEmpty(begin());

      return m_beforeHead->next->data;
    }

    iterator beforeBegin() noexcept
    {
      return iterator(m_beforeHead);
    }
    iterator begin() noexcept
    {
      return iterator(m_beforeHead->next);
    }
    iterator end() noexcept
    {
      return iterator();
    }

    constIterator constBeforeBegin() const noexcept
    {
      return constIterator(m_beforeHead);
    }
    constIterator constBegin() const noexcept
    {
      return constIterator(m_beforeHead->next);
    }
    constIterator constEnd() const noexcept
    {
      return constIterator();
    }

    void reverse() noexcept
    {
      if (isEmpty())
      {
        return;
      }

      list* top = m_beforeHead->next;
      list* tail = top;
      list* val = nullptr;

      while (tail->next != nullptr)
      {
        m_beforeHead->next = tail->next;
        val = tail->next->next;
        tail->next->next = top;
        tail->next = val;

        top = m_beforeHead->next;
      }
    }
    bool isEmpty() const noexcept
    {
      return dmitriev::isEmpty(m_beforeHead->next);
    }
    void swap(ForwardList& other) noexcept
    {
      std::swap(m_beforeHead->next, other.m_beforeHead->next);
    }
    void clear() noexcept
    {
      dmitriev::clear(m_beforeHead->next);
      m_beforeHead->next = nullptr;
    }

  private:
    list* m_beforeHead;

    void throwIfIteratorEmpty(constIterator it)
    {
      if (dmitriev::isEmpty(it.m_ptr))
      {
        throw std::runtime_error("iterator is empty");
      }
    }
  };
}

#endif
