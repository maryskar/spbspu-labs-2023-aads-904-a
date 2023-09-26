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
}
#endif
