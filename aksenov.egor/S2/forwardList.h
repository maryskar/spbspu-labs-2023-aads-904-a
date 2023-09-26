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

    bool isEmpty() const noexcept;
    void clear() noexcept;
    void swap(ForwardList< T > &val);

    reference front();
    constReference front() const;

    iterator insertAfter(constIterator pos, constReference val);
    iterator insertAfter(constIterator pos, valueType &&val);
    iterator insertAfter(constIterator pos, sizeType count, constReference val);

    void pushFront(constReference val);
    void pushFront(valueType &&val);

    void popFront();

    iterator eraseAfter(constIterator pos);
    iterator eraseAfter(constIterator first, constIterator last);

  private:
    listT< T > *fake_;
    listT< T > *tail_;
    void pushBack(constReference data);
  };

  template< typename T >
  ForwardList< T >::ForwardList():
          fake_(static_cast< listT< T > * >(::operator new (sizeof(listT< T >)))),
          tail_(nullptr)
  {
    fake_->next = tail_;
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
  typename ForwardList< T >::reference ForwardList< T >::front()
  {
    return fake_->next->data;
  }

  template< typename T >
  typename ForwardList< T >::constReference ForwardList< T >::front() const
  {
    return fake_->next->data;
  }

  template< typename T >
  void ForwardList< T >::swap(ForwardList< T > &val)
  {
    std::swap(this->fake_, val.fake_);
    std::swap(this->tail_, val.tail_);
  }

  template< typename T >
  ForwardList< T >::ForwardList(ForwardList< T > &&val) noexcept:
    fake_(val.fake_),
    tail_(val.tail_)
  {
    val.fake_ = nullptr;
    val.fake_ = nullptr;
  }

  template< typename T >
  ForwardList< T > &ForwardList< T >::operator=(ForwardList< T > &&val) noexcept
  {
  if (this != std::addressof(val))
  {
    ForwardList< T > temp(std::move(val));
    swap(temp);
  }
  return *this;
  }

  template< typename T >
  bool ForwardList< T >::isEmpty() const noexcept
  {
    return fake_->next == nullptr;
  }

  template< typename T >
  void ForwardList< T >::clear() noexcept
  {
    while (!isEmpty())
    {
      popFront();
    }
  }

  template< typename T >
  void ForwardList< T >::popFront()
  {
    if(fake_->next == tail_)
    {
      return;
    }
    auto todel = fake_->next;
    fake_->next = fake_->next->next;
    delete todel;
  }

  template< typename T >
  ForwardList< T >::~ForwardList()
  {
    if (isEmpty())
    {
      return;
    }
    clear();
    fake_ = tail_ = nullptr;
  }

  template< typename T >
  void ForwardList< T >::pushFront(constReference val)
  {
    listT< T > *newNode = new listT< T >{val, nullptr};
    if (!fake_ || !fake_->next)
    {
      tail_ = fake_->next;
      fake_->next = newNode;
      return;
    }
    newNode->next = fake_->next;
    fake_->next = newNode;
  }

  template< typename T >
  void ForwardList< T >::pushFront(valueType &&val)
  {
    insertAfter(cbeforeBegin(), std::move(val));
  }

  template< typename T >
  void ForwardList< T >::pushBack(constReference data)
  {
    if (!fake_ || !fake_->next)
    {
      pushFront(data);
      return;
    }
    listT< T > *newNode = new listT< T >{data, nullptr};
    tail_->next = newNode;
    tail_ = newNode;
  }

  template< typename T >
  typename ForwardList< T >::iterator ForwardList< T >::insertAfter(constIterator pos, constReference val)
  {
    if (!fake_ || !fake_->next)
    {
      pushFront(val);
      return iterator(pos.node_->next);
    }
    if (pos == tail_)
    {
      pushBack(val);
      return iterator(pos.node_->next);
    }
    listT< T > *newNode = new listT< T >{val, nullptr};
    listT< T > *prev = pos.node_;
    newNode->next = prev->next;
    prev->next = newNode;
    return iterator(pos.node_->next);
  }

  template< typename T >
  typename ForwardList< T >::iterator ForwardList< T >::insertAfter(constIterator pos, valueType &&val)
  {
    return insertAfter(pos, val);
  }

  template< typename T >
  typename ForwardList< T >::iterator ForwardList< T >::insertAfter(constIterator pos, sizeType count, constReference val)
  {
    for (auto i = 0; i < count; ++i)
    {
      insertAfter(pos, val);
      ++pos;
    }
    return iterator(pos.node_);
  }
}
#endif
