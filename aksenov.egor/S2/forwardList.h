#ifndef FORWARDLIST_H
#define FORWARDLIST_H
#include <stdexcept>
#include "constForwardIterator.h"
#include "ForwardIterator.h"
#include "List.h"
namespace aksenov
{
  template< typename T >
  class ForwardList
  {
  public:
    using valueType = T;
    using reference = valueType &;
    using constReference = const valueType &;
    using sizeType = std::size_t;
    using iterator = ForwardIterator< T >;
    using constIterator = ConstForwardIterator< T >;

    ForwardList();
    ~ForwardList();
    ForwardList(const ForwardList< T > &val);
    ForwardList(ForwardList< T > &&val) noexcept;

    ForwardList< T > &operator=(const ForwardList< T > &val);
    ForwardList< T > &operator=(ForwardList< T > &&val) noexcept;

    iterator beforeBegin() noexcept;
    constIterator beforeBegin() const noexcept;
    constIterator cbeforeBegin() const noexcept;
    iterator begin() noexcept;
    constIterator begin() const noexcept;
    constIterator cbegin() const noexcept;
    iterator end() noexcept;
    constIterator end() const noexcept;
    constIterator cend() const noexcept;
    iterator last() noexcept;
    constIterator last() const noexcept;
    constIterator clast() const noexcept;

    bool isEmpty() const noexcept;
    void clear() noexcept;
    void swap(ForwardList< T > &val);

    reference front();
    constReference front() const;

    iterator insertAfter(constIterator pos, constReference val);
    iterator insertAfter(constIterator pos, valueType &&val);
    iterator insertAfter(constIterator pos, sizeType count, constReference val);
    template< typename InpIter >
    iterator insertAfter(constIterator pos, InpIter first, InpIter last);

    void pushFront(constReference val);
    void pushFront(valueType &&val);

    void popFront();

    iterator eraseAfter(constIterator pos);
    iterator eraseAfter(constIterator first, constIterator last);

  private:
    listT< T > *fake_;
    listT< T > *tail_;
    listT< T > *head_;
    void copy(const ForwardList< T > &rhs);
  };

  template< typename T >
  ForwardList< T >::ForwardList():
    fake_(static_cast< listT< T > * >(::operator new (sizeof(listT< T >)))),
    tail_(nullptr),
    head_(nullptr)
  {
    fake_->next = head_;
  }

  template< typename T >
  ForwardList< T >::~ForwardList()
  {
    clear();
    ::operator delete(fake_);
  }

  template< typename T >
  ForwardList< T >::ForwardList(const ForwardList< T > &val):
    ForwardList()
  {
    copy(val);
  }

  template< typename T >
  ForwardList< T >::ForwardList(ForwardList< T > &&val) noexcept:
    ForwardList()
  {
    swap(val);
    val.fake_ = nullptr;
    val.tail_ = nullptr;
    val.head_ = nullptr;
  }

  template< typename T >
  ForwardList< T > &ForwardList< T >::operator=(const ForwardList< T > &val)
  {
    if (this == std::addressof(val))
    {
      return *this;
    }
    clear();
    copy(val);
    return *this;
  }

  template< typename T >
  ForwardList< T > &ForwardList< T >::operator=(ForwardList< T > &&val) noexcept
  {
    if (this == std::addressof(val))
    {
      return *this;
    }
    clear();
    head_ = val.head_;
    tail_ = val.tail_;
    fake_->next = head_;
    val.head_ = nullptr;
    val.tail_ = nullptr;
    return *this;
  }

  template< typename T >
  typename ForwardList< T >::iterator ForwardList< T >::beforeBegin() noexcept
  {
    return iterator(fake_);
  }

  template< typename T >
  typename ForwardList< T >::constIterator ForwardList< T >::beforeBegin() const noexcept
  {
    return cbeforeBegin();
  }

  template< typename T >
  typename ForwardList< T >::constIterator ForwardList< T >::cbeforeBegin() const noexcept
  {
    return constIterator(fake_);
  }

  template< typename T >
  typename ForwardList< T >::iterator ForwardList< T >::begin() noexcept
  {
    return iterator(fake_->next);
  }

  template< typename T >
  typename ForwardList< T >::constIterator ForwardList< T >::begin() const noexcept
  {
    return cbegin();
  }

  template< typename T >
  typename ForwardList< T >::constIterator ForwardList< T >::cbegin() const noexcept
  {
    return constIterator(fake_->next);
  }

  template< typename T >
  typename ForwardList< T >::iterator ForwardList< T >::end() noexcept
  {
    return iterator(tail_);
  }

  template< typename T >
  typename ForwardList< T >::constIterator ForwardList< T >::end() const noexcept
  {
    return cend();
  }

  template< typename T >
  typename ForwardList< T >::constIterator ForwardList< T >::cend() const noexcept
  {
    return constIterator(tail_);
  }

  template< typename T >
  typename ForwardList< T >::iterator ForwardList< T >::last() noexcept
  {
    return tail_;
  }

  template< typename T >
  typename ForwardList< T >::constIterator ForwardList< T >::last() const noexcept
  {
    return clast();
  }

  template< typename T >
  typename ForwardList< T >::constIterator ForwardList< T >::clast() const noexcept
  {
    return constIterator(tail_);
  }

  template< typename T >
  bool ForwardList< T >::isEmpty() const noexcept
  {
    return head_ == nullptr;
  }

  template <typename T>
  void ForwardList<T>::clear() noexcept
  {
    free(head_);
    head_ = nullptr;
    tail_ = nullptr;
  }

  template< typename T >
  void ForwardList< T >::swap(ForwardList< T > &val)
  {
    std::swap(fake_, val.fake_);
    std::swap(tail_, val.tail_);
    std::swap(head_, val.head_);
  }

  template< typename T >
  typename ForwardList< T >::reference ForwardList< T >::front()
  {
    return head_->data;
  }

  template< typename T >
  typename ForwardList< T >::constReference ForwardList< T >::front() const
  {
    return head_->data;
  }

  template< typename T >
  typename ForwardList< T >::iterator ForwardList< T >::insertAfter(constIterator pos, constReference val)
  {
    auto *newNode = new listT< T >{val, nullptr};
    newNode->next = pos.node_->next;
    pos.node_->next = newNode;
    if (pos.node_ == fake_)
    {
      if (!tail_)
      {
        tail_ = head_;
      }
      head_ = newNode;
    }
    if (newNode->next == nullptr)
    {
      tail_ = newNode;
    }
    return iterator(newNode->next);
  }

  template< typename T >
  typename ForwardList< T >::iterator ForwardList< T >::insertAfter(constIterator pos, valueType &&val)
  {
    return insertAfter(pos, val);
  }

  template< typename T >
  typename ForwardList< T >::iterator ForwardList< T >::insertAfter(constIterator pos, sizeType count, constReference val)
  {
    for (ssize_t i = 0; i < count; ++i)
    {
      pos = insertAfter(pos, val);
    }
    return iterator(pos.node_);
  }

  template< class T >
  template< class InpIter >
  typename ForwardList< T >::iterator ForwardList< T >::insertAfter(constIterator pos, InpIter first, InpIter last)
  {
    while (first != last)
    {
      pos = insertAfter(pos, *first);
    }
    return iterator(pos.node_);
  }


  template< typename T >
  void ForwardList< T >::pushFront(constReference val)
  {
    insertAfter(cbeforeBegin(), val);
  }

  template< typename T >
  void ForwardList< T >::pushFront(valueType &&val)
  {
    insertAfter(cbeforeBegin(), std::move(val));
  }

  template< typename T >
  void ForwardList< T >::popFront()
  {

  }

  template < typename T >
  typename ForwardList< T >::iterator ForwardList< T >::eraseAfter(constIterator pos)
  {
    if (pos.node_ == nullptr || pos.node_->next == nullptr)
    {
      return end();
    }
    listT< T > *todel = pos.node_->next;
    pos.node_->next = todel->next;
    if (todel == tail_)
    {
      tail_ = pos.node_;
    }
    delete todel;
    return iterator(pos.node_->next);
  }

  template < typename T >
  typename ForwardList< T >::iterator aksenov::ForwardList< T >::eraseAfter(constIterator first, constIterator last)
  {
    if (first == last || first.node_ == nullptr)
    {
      return end();
    }
    constIterator cur = first;
    while (cur.node_->next != last.node_->next)
    {
      eraseAfter(cur);
    }
    return iterator(last.node_->next);
  }

  template< typename T >
  void ForwardList< T >::copy(const ForwardList< T > &rhs)
  {
    auto copied = copyLst(rhs.head_);
    head_ = copied.first;
    tail_ = copied.second;
    fake_->next = head_;
  }
}
#endif
