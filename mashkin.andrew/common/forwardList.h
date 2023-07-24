#ifndef FORWARDLIST_H
#define FORWARDLIST_H
#include <stdexcept>
#include <utility>
#include "forwardConstIterator.h"
#include "forwardIterator.h"
#include "nodeList.h"

namespace mashkin
{
  template< typename T >
  class forwardConstIterator;
  template< typename T >
  class forwardIterator;

  template< typename T >
  class ForwardList
  {
  public:
    using iter = forwardIterator< T >;
    using citer = forwardConstIterator< T >;
    ForwardList();
    ForwardList(const ForwardList< T >& lhs);
    ForwardList(ForwardList< T >&& rhs) noexcept;
    template< class InputIt >
    ForwardList(InputIt first, InputIt last);
    ~ForwardList();

    ForwardList< T >& operator=(const ForwardList< T >& rhs);
    ForwardList< T >& operator=(ForwardList< T >&& rhs);

    iter before_begin() noexcept;
    citer cbefore_begin() noexcept;
    iter begin() const noexcept;
    iter end() const noexcept;
    citer cbegin() const noexcept;
    citer cend() const noexcept;

    iter insert_after(citer position, const T& val);
    iter insert_after(citer position, T&& val);
    iter insert_after(citer position, size_t n, const T& val);
    template< class InputIterator >
    iter insert_after(citer position, InputIterator first, InputIterator last);


    T& front();
    void push_front(const T& value);
    void pop_front();

    iter erase_after(citer pos);
    iter erase_after(citer pos, citer last);
    void clear() noexcept;

    void swap(ForwardList< T >& list);
    void reverse() noexcept;

    void splice_after(citer pos, ForwardList< T >& other);
    void splice_after(citer pos, ForwardList< T >&& other);
    void splice_after(citer pos, ForwardList< T >& other, citer it);
    void splice_after(citer pos, ForwardList< T >&& other, citer it);
    void splice_after(citer pos, ForwardList< T >& other, citer first, citer last);
    void splice_after(citer pos, ForwardList< T >&& other, citer first, citer last);
    bool empty() const noexcept;

    void remove(const T& value);
    template< class UnaryPredicate >
    void remove_if(UnaryPredicate p);

  private:
    NodeList< T >* fake_;
    NodeList< T >* tail_;
  };

  template< class T >
  template< class InputIt >
  ForwardList< T >::ForwardList(InputIt first, InputIt last):
    ForwardList()
  {
    insert_after(before_begin(), first, last);
  }

  template< class T >
  ForwardList< T >::ForwardList():
    fake_(static_cast< NodeList< T >* >(::operator new(sizeof(NodeList< T >)))),
    tail_(nullptr)
  {
    fake_->next = tail_;
  }

  template< class T >
  ForwardList< T >::~ForwardList()
  {
    clear();
    ::operator delete(fake_);
  }

  template< class T >
  ForwardList< T >::ForwardList(const ForwardList< T >& lhs):
    ForwardList()
  {
    insert_after(before_begin(), lhs.cbegin(), lhs.cend());
  }

  template< class T >
  ForwardList< T >::ForwardList(ForwardList< T >&& rhs) noexcept:
    fake_(rhs.fake_),
    tail_(rhs.tail_)
  {
  }

  template< class T >
  ForwardList< T >& ForwardList< T >::operator=(ForwardList< T >&& rhs)
  {
    insert_after(before_begin(), rhs.begin(), rhs.end());
    return *this;
  }

  template< class T >
  ForwardList< T >& ForwardList< T >::operator=(const ForwardList< T >& rhs)
  {
    *this = std::move(rhs);
    return *this;
  }

  template< class T >
  void ForwardList< T >::push_front(const T& value)
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
  bool ForwardList< T >::empty() const noexcept
  {
    return fake_->next == tail_;
  }

  template< class T >
  forwardIterator< T > ForwardList< T >::before_begin() noexcept
  {
    return iter(fake_);
  }

  template< class T >
  forwardConstIterator< T > ForwardList< T >::cbefore_begin() noexcept
  {
    return before_begin();
  }

  template< class T >
  forwardIterator< T > ForwardList< T >::begin() const noexcept
  {
    return iter(fake_->next);
  }

  template< class T >
  forwardIterator< T > ForwardList< T >::end() const noexcept
  {
    return iter(tail_);
  }

  template< class T >
  forwardConstIterator< T > ForwardList< T >::cbegin() const noexcept
  {
    return begin();
  }

  template< class T >
  forwardConstIterator< T > ForwardList< T >::cend() const noexcept
  {
    return end();
  }

  template< class T >
  forwardIterator< T > ForwardList< T >::insert_after(citer position, T&& val)
  {
    return insert_after(position, val);
  }

  template< class T >
  forwardIterator< T > ForwardList< T >::insert_after(citer position, const T& val)
  {
    position.node->next = new NodeList< T >{val, position.node->next};
    ++position;
    return iter(position.node);
  }

  template< class T >
  forwardIterator< T > ForwardList< T >::insert_after(citer position, size_t n, const T& val)
  {
    forwardIterator< T > res = position.node;
    for (auto i = 0; i < n; i++)
    {
      res = insert_after(res, val);
    }
  }

  template< class T >
  template< class InpIter >
  forwardIterator< T > ForwardList< T >::insert_after(citer position, InpIter first, InpIter last)
  {
    forwardIterator< T > var = position.node;
    while (first != last)
    {
      var = insert_after(var, *first);
      first++;
    }
    return var;
  }

  template< class T >
  T& ForwardList< T >::front()
  {
    return *this->begin();
  }

  template< class T >
  void ForwardList< T >::pop_front()
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
  forwardIterator< T > ForwardList< T >::erase_after(citer pos)
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
  forwardIterator< T > ForwardList< T >::erase_after(citer pos, citer last)
  {
    while (pos.node->next != last.node)
    {
      erase_after(pos);
    }
    return iter(pos.node->next);
  }

  template< class T >
  void ForwardList< T >::clear() noexcept
  {
    while (!empty())
    {
      pop_front();
    }
  }

  template< class T >
  void ForwardList< T >::swap(ForwardList< T >& list)
  {
    ForwardList< T > var;
    var.insert_after(var.before_begin(), list.begin(), list.end());
    list.clear();
    list.insert_after(list.before_begin(), begin(), end());
    clear();
    isert_after(before_begin(), var.begin(), var.end());
  }

  template< class T >
  void ForwardList< T >::reverse() noexcept
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
          } while (var3 != nullptr);
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

  template< class T >
  void ForwardList< T >::splice_after(citer pos, ForwardList< T >& other)
  {
    forwardConstIterator< T > end(pos.node->next);
    auto first = other.begin();
    auto last = other.end();
    pos.node->next = first.node;
    while (first.node->next != last.node)
    {
      first++;
    }
    first.node->next = end.node;
    other.fake_->next = other.fake_;
  }

  template< class T >
  void ForwardList< T >::splice_after(citer pos, ForwardList< T >&& other)
  {
    splice_after(pos, other);
  }

  template< class T >
  void ForwardList< T >::splice_after(citer pos, ForwardList< T >& other, citer it)
  {
    if (it.node->next == other.fake_->next)
    {
      splice_after(pos, other);
    }
    else
    {
      forwardConstIterator< T > end(pos.node->next);
      auto last = other.end();
      pos.node->next = it.node->next;
      auto otherEnd = it;
      it++;
      otherEnd.node->next = nullptr;
      while (it.node->next != last.node)
      {
        it++;
      }
      it.node->next = end.node;
    }
  }

  template< class T >
  void ForwardList< T >::splice_after(citer pos, ForwardList< T >&& other, citer it)
  {
    splice_after(pos, other, it);
  }

  template< class T >
  void ForwardList< T >::splice_after(citer pos, ForwardList< T >& other, citer first, citer last)
  {
    forwardConstIterator< T > end(pos.node->next);
    pos.node->next = first.node->next;
    first.node->next = last.node->next;
    last.node->next = end.node;
  }

  template< class T >
  void ForwardList< T >::splice_after(citer pos, ForwardList< T >&& other, citer first, citer last)
  {
    splice_after(pos, other, first, last);
  }

  template< class T >
  void ForwardList< T >::remove(const T& value)
  {
    auto first = before_begin();
    auto last = end();
    while (first.node->next != last.node)
    {
      if (first.node->next->data == value)
      {
        auto toDel = first.node->next;
        first.node->next = first.node->next->next;
        delete toDel;
      }
      ++first;
    }
  }

  template< class T>
  template< class UnaryPredicate >
  void ForwardList< T >::remove_if(UnaryPredicate p)
  {
    auto first = before_begin();
    auto last = end();
    while (first.node->next != last.node)
    {
      if (p(first.node->next->data))
      {
        auto toDel = first.node->next;
        first.node->next = first.node->next->next;
        delete toDel;
      }
      ++first;
    }
  }
}
#endif
