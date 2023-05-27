#ifndef FORWARDLIST_H
#define FORWARDLIST_H
#include <stdexcept>
#include <utility>
#include "constIterator.h"
#include "iterator.h"
#include "nodeList.h"

namespace mashkin
{
  template< class T >
  class ConstIterator;

  template< class T >
  class ForwardList
  {
  public:
    using iter = mashkin::Iterator< T >;
    using citer = mashkin::ConstIterator< T >;
    ForwardList();
    ForwardList(const ForwardList< T >& lhs);
    ForwardList(ForwardList< T >&& rhs) noexcept;

    ForwardList< T >& operator=(const ForwardList< T >& rhs);
    ForwardList< T >& operator=(ForwardList< T >&& rhs);

    Iterator< T > before_begin() noexcept;
    ConstIterator< T > cbefore_begin() noexcept;

    Iterator< T > begin() const noexcept;
    Iterator< T > end() const noexcept;

    Iterator< T > insert_after(ConstIterator< T > position, const T& val);
    Iterator< T > insert_after(ConstIterator< T > position, T&& val);
    Iterator< T > insert_after(ConstIterator< T > position, size_t n, const T& val);
    template< class InputIterator >
    Iterator< T > insert_after(ConstIterator< T > position, InputIterator first, InputIterator last);

    ConstIterator< T > cbegin() const noexcept;
    ConstIterator< T > cend() const noexcept;

    T& front();
    void push_front(const T& value);
    void pop_front();

    Iterator< T > erase_after(citer pos);
    Iterator< T > erase_after(citer pos, citer last);
    void clear() noexcept;

    void swap(ForwardList< T >& list);
    void reverse() noexcept;

    bool empty() const noexcept;

  private:
    NodeList< T >* fake_;
    NodeList< T >* tail_;
  };
}

template< class T >
mashkin::ForwardList< T >::ForwardList():
  fake_(static_cast< NodeList< T >* >(::operator new(sizeof(NodeList< T >)))),
  tail_(nullptr)
{
  fake_->next = fake_;
}

template< class T >
mashkin::ForwardList< T >::ForwardList(const ForwardList< T >& lhs):
  ForwardList()
{
  fake_->next = tail_;
  insert_after(before_begin(), lhs.cbegin(), lhs.cend());
}

template< class T >
mashkin::ForwardList< T >::ForwardList(ForwardList< T >&& rhs) noexcept:
  fake_(rhs.fake_),
  tail_(rhs.tail)
{
}

template< class T >
mashkin::ForwardList< T >& mashkin::ForwardList< T >::operator=(ForwardList< T >&& rhs)
{
  insert_after(before_begin(), rhs.begin(), rhs.end());
  return *this;
}

template< class T >
mashkin::ForwardList< T >& mashkin::ForwardList< T >::operator=(const ForwardList< T >& rhs)
{
  *this = std::move(rhs);
  return *this;
}

template< class T >
void mashkin::ForwardList< T >::push_front(const T& value)
{
  if (empty())
  {
    fake_->next = new NodeList< T >{value, nullptr};
    tail_ = fake_->next->next;
  }
  else
  {
    auto var = new NodeList< T >{value, fake_->next};
    fake_->next = var;
  }
}

template< class T >
bool mashkin::ForwardList< T >::empty() const noexcept
{
  return fake_->next == fake_;
}

template< class T >
mashkin::Iterator< T > mashkin::ForwardList< T >::before_begin() noexcept
{
  return iter(fake_);
}

template< class T >
mashkin::ConstIterator< T > mashkin::ForwardList< T >::cbefore_begin() noexcept
{
  return before_begin();
}

template< class T >
mashkin::Iterator< T > mashkin::ForwardList< T >::begin() const noexcept
{
  return iter(fake_->next);
}

template< class T >
mashkin::Iterator< T > mashkin::ForwardList< T >::end() const noexcept
{
  return iter(tail_);
}

template< class T >
mashkin::ConstIterator< T > mashkin::ForwardList< T >::cbegin() const noexcept
{
  return begin();
}

template< class T >
mashkin::ConstIterator< T > mashkin::ForwardList< T >::cend() const noexcept
{
  return end();
}

template< class T >
mashkin::Iterator< T > mashkin::ForwardList< T >::insert_after(citer position, T&& val)
{
  return insert_after(position, std::move(val));
}

template< class T >
mashkin::Iterator< T > mashkin::ForwardList< T >::insert_after(citer position, const T& val)
{
  position.node->next = new NodeList< T >{val, position.node->next};
  ++position;
  return iter(position.node);
}

template< class T >
mashkin::Iterator< T > mashkin::ForwardList< T >::insert_after(citer position, size_t n, const T& val)
{
  Iterator< T > res = position.node;
  for (auto i = 0; i < n; i++)
  {
    res = insert_after(res, val);
  }
}

template< class T >
template< class InpIter >
mashkin::Iterator< T > mashkin::ForwardList< T >::insert_after(citer position, InpIter first, InpIter last)
{
  Iterator< T > var = position.node;
  while (first != last)
  {
    var = insert_after(var, *first);
    first++;
  }
}

template< class T >
T& mashkin::ForwardList< T >::front()
{
  return *this->begin();
}

template< class T >
void mashkin::ForwardList< T >::pop_front()
{
  if (fake_->next == tail_)
  {
    throw std::out_of_range("You got the end of list");
  }
  auto toDel = fake_->next;
  fake_->next = fake_->next->next;
  delete toDel;
}

template< class T >
mashkin::Iterator< T > mashkin::ForwardList< T >::erase_after(citer pos)
{
  if (pos == cend())
  {
    return iter(pos.node);
  }
  auto toDel = pos.node->next;
  pos.node->next = pos.node->next->next;
  delete toDel;
  return iter(pos.node->next);
}

template< class T >
mashkin::Iterator< T > mashkin::ForwardList< T >::erase_after(citer pos, citer last)
{
  while (pos.node->next != last.node)
  {
    erase_after(pos);
  }
  return iter(pos.node->next);
}

template< class T >
void mashkin::ForwardList< T >::clear() noexcept
{
  while (empty())
  {
    pop_front();
    if (!fake_->next)
    {
      fake_->next = fake_;
    }
  }
}

template< class T >
void mashkin::ForwardList< T >::swap(ForwardList< T >& list)
{
  ForwardList< T > var;
  var.insert_after(var.before_begin(), list.begin(), list.end());
  list.clear();
  list.insert_after(list.before_begin(), begin(), end());
  clear();
  isert_after(before_begin(), var.begin(), var.end());
}

template< class T >
void mashkin::ForwardList< T >::reverse() noexcept
{
  auto var1 = fake_->next;
  if (var1)
  {
    auto var2 = var1->next;
    if (var2)
    {
      if (var2->next)
      {
        var1->next = nullptr;
        auto var3 = var2->next;
        do
        {
          var2->next = var1;
          var1 = var2;
          var2 = var3;
          var3 = var3->next;
        }
        while (var3 != nullptr);
        var2->next = var1;
        var1 = var2;
        var2 = var3;
        fake_->next = var1;
      }
      else
      {
        fake_->next = var2;
        var2->next = var1;
      }
    }
  }
}
#endif
