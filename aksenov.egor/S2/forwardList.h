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
    void pushBack(constReference data);
    void copy(const ForwardList< T > &rhs);
  };

  template< typename T >
  ForwardList< T >::ForwardList():
          fake_(static_cast< listT< T >* >(::operator new(sizeof(listT< T >)))),
          tail_(nullptr),
          head_(nullptr)
  {
    fake_->next = nullptr;
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
    fake_ = val.fake_;
    tail_ = val.tail_;
    head_ = val.head_;
  }

  template< typename T >
  ForwardList< T >::ForwardList(ForwardList< T > &&val) noexcept:
          fake_(val.fake_),
          tail_(val.tail_),
          head_(val.head_)
  {
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
    fake_ = val.fake_;
    tail_ = val.tail_;
    head_ = val.head_;
    val.fake_ = nullptr;
    val.tail_ = nullptr;
    val.head_ = nullptr;
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
    deleteList(head_);
    tail_ = nullptr;
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
    auto *newNode = new listT< T >{val, pos.node_->next};
    pos.node_->next = newNode;
    if (pos.node_ == fake_) {
      head_ = newNode;
      if (!tail_) {
        tail_ = head_;
      }
      head_ = newNode;
    } else if (!newNode->next) {
      tail_ = newNode;
    }
    return iterator(pos.node_->next);

  }

  template< typename T >
  typename ForwardList< T >::iterator ForwardList< T >::insertAfter(constIterator pos, valueType &&val)
  {
    auto newNode = new listT< T >{std::move(val), pos.node_->next};
    pos.node_->next = newNode;
    ++pos;
    return iterator(pos.node_);
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

  template< class T >
  template< class InpIter >
  typename ForwardList< T >::iterator ForwardList< T >::insertAfter(constIterator pos, InpIter first, InpIter last)
  {
    ForwardIterator< T > var = pos.node;
    while (first != last)
    {
      var = insert_after(var, *first);
      first++;
    }
    return var;
  }


  template< typename T >
  void ForwardList< T >::pushFront(constReference val)
  {
    /*listT< T > *newNode = new listT< T >{val, nullptr};
    if (!fake_ || !fake_->next)
    {
      tail_ = fake_->next;
      fake_->next = newNode;
      return;
    }
    newNode->next = fake_->next;
    fake_->next = newNode;*/
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
    if(fake_->next == tail_)
    {
      throw std::out_of_range("end of list");
    }
    auto todel = fake_->next;
    fake_->next = fake_->next->next;
    delete todel;
  }

  template < typename T >
  typename ForwardList< T >::iterator ForwardList< T >::eraseAfter(constIterator pos)
  {
    auto next = pos.node_->next;
    if (next) {
      pos.node_->next = next->next;
    }
    if (pos.node_ == fake_) {
      head_ = pos.node_->next;
    }
    if (next) {
      delete next;
    }
    if (head_->next == nullptr) {
      head_ = tail_;
    } else if ( !head_) {
      head_ = nullptr;
      tail_ = nullptr;
      fake_->next = nullptr;
    }
    return iterator(pos.node_->next);


  }

  template < typename T >
  typename ForwardList< T >::iterator aksenov::ForwardList< T >::eraseAfter(constIterator first, constIterator last)
  {
    while (first != last)
    {
      eraseAfter(first);
    }
    return iterator(last.node_);
  }

  template< typename T >
  void ForwardList< T >::pushBack(constReference data)
  {
    listT< T > *newNode = new listT< T >{data, nullptr};

    if (!fake_ || !fake_->next)
    {
      fake_->next = newNode;
      tail_ = newNode;
    }
    else
    {
      tail_->next = newNode;
      tail_ = newNode;
    }
  }

  template< typename T >
  void ForwardList< T >::copy(const ForwardList< T > &rhs)
  {
    auto res = copyList(rhs.head_);
    head_ = res.first;
    tail_ = res.second;
    fake_->next = head_;

  }
}
#endif
