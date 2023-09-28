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

      void pushFront(constReference val);
      void pushFront(valueType &&val);

      void popFront();

      constIterator eraseAfter(constIterator pos);
      constIterator eraseAfter(constIterator first, constIterator last);

    private:
      listT< T > *fake_;
      listT< T > *tail_;
      void pushBack(constReference data);
      void copy(const ForwardList< T > &rhs);
  };

  template< typename T >
  ForwardList< T >::ForwardList()
  {
    fake_ = new listT< T >;
    tail_ = fake_;
  }

  template< typename T >
  ForwardList< T >::~ForwardList()
  {
    if (isEmpty())
    {
      return;
    }
    clear();
    delete fake_;
  }

  template< typename T >
  ForwardList< T >::ForwardList(const ForwardList< T > &val):
    ForwardList()
  {
    copy(val);
  }

  template< typename T >
  ForwardList< T >::ForwardList(ForwardList< T > &&val) noexcept:
    fake_(val.fake_),
    tail_(val.tail_)
  {
    val.tail_ = nullptr;
    val.fake_ = nullptr;
  }

  template< typename T >
  ForwardList< T > &ForwardList< T >::operator=(const ForwardList< T > &val)
  {
    if (this != std::addressof(val))
    {
      clear();
      copy(val);
    }
    return *this;
  }

  template< typename T >
  ForwardList< T > &ForwardList< T >::operator=(ForwardList< T > &&val) noexcept
  {
    if (this != std::addressof(val))
    {
      clear();
      fake_ = val.fake_;
      tail_ = val.tail_;
      val.fake_ = nullptr;
      val.tail_ = nullptr;
    }
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
    return fake_->next == nullptr;
  }

  template< typename T >
  void ForwardList< T >::clear() noexcept
  {
    while (!isEmpty())
    {
      listT< T > *temp = fake_->next;
      fake_->next = temp->next;
      delete temp;
    }
    tail_ = fake_;
  }

  template< typename T >
  void ForwardList< T >::swap(ForwardList< T > &val)
  {
    std::swap(this->fake_, val.fake_);
    std::swap(this->tail_, val.tail_);
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

  template < typename T >
  typename ForwardList< T >::constIterator ForwardList< T >::eraseAfter(constIterator pos)
  {
    if (!pos.node_ || !pos.node_->next)
    {
      throw std::logic_error("Invalid position");
    }
    constIterator nextNode = pos.node_->next;
    if (nextNode.node_ == tail_)
    {
      tail_ = pos.node_;
    }
    pos.node_->next = nextNode.node_->next;
    delete nextNode.node_;
    return constIterator(pos.node_->next);
  }

  template < typename T >
  typename ForwardList< T >::constIterator aksenov::ForwardList< T >::eraseAfter(constIterator first, constIterator last)
  {
    while (first != last) {
      first = erase_after(first);
    }
    return constIterator(last.node_->next);
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
  void ForwardList< T >::copy(const ForwardList< T > &rhs)
  {
    auto it = rhs.begin();
    while (it != rhs.end())
    {
      pushBack(*it);
      ++it;
    }
  }
}
#endif
