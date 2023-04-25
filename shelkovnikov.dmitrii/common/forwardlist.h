#ifndef SPBSPU_LABS_2023_AADS_904_A_FORWARDLIST_H
#define SPBSPU_LABS_2023_AADS_904_A_FORWARDLIST_H
#include <cstddef>
#include <cassert>
#include <iterator>
#include <cstdarg>
#include "forwardlistiterator.h"
#include "forwardlistiteratorconst.h"
#include "nodeOneWayList.h"
namespace dimkashelk
{
  template< typename T >
  class ForwardList
  {
  using iterator = dimkashelk::ForwardListIterator< T >;
  using const_iterator = dimkashelk::ForwardListIteratorConst< T >;
  using reference = T&;
  using const_reference = const T&;
  public:
    ForwardList():
      fakeNode_(static_cast< details::NodeOneWayList< T >* >(::operator new (sizeof(details::NodeOneWayList< T >)))),
      begin_(nullptr),
      end_(nullptr),
      size_(0)
    {}
    ForwardList(const ForwardList< T > &forwardList):
      fakeNode_(static_cast< details::NodeOneWayList< T >* >(::operator new (sizeof(details::NodeOneWayList< T >)))),
      begin_(nullptr),
      end_(nullptr),
      size_(0)
    {
      copy(forwardList);
    }
    ForwardList(ForwardList< T > &&forwardList):
      fakeNode_(forwardList.fakeNode_),
      begin_(forwardList.begin_),
      end_(forwardList.end_),
      size_(forwardList.size_)
    {
      forwardList.fakeNode_ = nullptr;
      forwardList.begin_ = forwardList.fakeNode_;
      forwardList.end_ = forwardList.fakeNode_;
    }
    ForwardList(std::initializer_list< T > &l):
      fakeNode_(static_cast< details::NodeOneWayList< T >* >(::operator new (sizeof(details::NodeOneWayList< T >)))),
      begin_(nullptr),
      end_(nullptr),
      size_(0)
    {
      for (auto i: l)
      {
        pushBack(i);
      }
    }
    ~ForwardList()
    {
      clear();
      delete fakeNode_;
    }
    ForwardList &operator=(const ForwardList< T > &forwardList)
    {
      if (std::addressof(forwardList) == this)
      {
        return *this;
      }
      clear();
      copy(forwardList);
      return *this;
    }
    ForwardList &operator=(ForwardList< T > &&forwardList)
    {
      if (std::addressof(forwardList) == this)
      {
        return *this;
      }
      clear();
      begin_ = forwardList.begin_;
      end_ = forwardList.end_;
      size_ = forwardList.size_;
      forwardList.begin_ = forwardList.fakeNode_;
      forwardList.end_ = forwardList.fakeNode_;
      return *this;
    }
    reference front()
    {
      return begin_->data;
    }
    const_reference front() const
    {
      return begin_->data;
    }
    iterator beforeBegin() const
    {
      return iterator(fakeNode_);
    }
    iterator begin() const
    {
      return iterator(begin_);
    }
    iterator end() const
    {
      return iterator(nullptr);
    }
    const_iterator cbeforeBegin() const
    {
      return const_iterator(fakeNode_);
    }
    const_iterator cbegin() const
    {
      return const_iterator(begin_);
    }
    const_iterator cend() const
    {
      return const_iterator(nullptr);
    }
    bool empty()
    {
      return begin_ == nullptr;
    }
    void clear() noexcept
    {
      while (begin_)
      {
        details::NodeOneWayList< T > *node = begin_;
        begin_ = begin_->next;
        delete node;
      }
      begin_ = nullptr;
      end_ = nullptr;
      size_ = 0;
    }
    iterator insertAfter(const_iterator it, const T &data)
    {
      auto *newNode = new details::NodeOneWayList< T >(data);
      newNode->next = it.ptr_->next;
      it.ptr_->next = newNode;
      if (it.ptr_ == fakeNode_)
      {
        if (begin_ && !end_)
        {
          end_ = begin_;
        }
        else
        {
          begin_ = newNode;
        }
      }
      else if (!newNode->next)
      {
        end_ = newNode;
      }
      return iterator(it.ptr_->next);
    }
    template < typename ... Args >
    iterator emplaceAfter(const_iterator pos, Args&&... args)
    {
      return insertAfter(pos, T(args...));
    }
    iterator eraseAfter(const_iterator it)
    {
      auto next = it.ptr_->next;
      if (next)
      {
        it.ptr_->next = next->next;
      }
      if (it.ptr_ == fakeNode_)
      {
        begin_ = it.ptr_->next;
      }
      if (next)
      {
        delete next;
      }
      size_--;
      if (size_ == 1)
      {
        end_ = nullptr;
      }
      else if (size_ == 0)
      {
        begin_ = nullptr;
        fakeNode_->next = nullptr;
      }
      return iterator(it.ptr_->next);
    }
    iterator eraseAfter(const_iterator first, const_iterator second)
    {
      auto start = first;
      while (first != second)
      {
        first = eraseAfter(start);
      }
      return iterator(second.ptr_);
    }
    void pushFront(const T &data)
    {
      auto *node = new details::NodeOneWayList< T >(data);
      if (begin_)
      {
        node->next = begin_;
        if (!end_)
        {
          end_ = begin_;
        }
        begin_ = node;
      }
      else
      {
        begin_ = node;
      }
      fakeNode_->next = begin_;
      size_++;
    }
    template< class ... Args >
    void emplaceFront(Args&&... args)
    {
      pushFront(T(args...));
    }
    void popFront()
    {
      eraseAfter(beforeBegin());
    }
    void resize(size_t count)
    {
      if (count < size_)
      {
        auto b = std::next(begin(), count);
        eraseAfter(b, end());
      }
      else if (count > size_)
      {
        for (; size_ < count; size_++)
        {
          pushBack(T());
        }
      }
    }
    void resize(size_t count, const T &data)
    {
      if (count < size_)
      {
        auto b = std::next(begin(), count);
        eraseAfter(b, end());
      }
      else if (count > size_)
      {
        for (; size_ < count; size_++)
        {
          pushBack(data);
        }
      }
    }
    void swap(ForwardList< T > &forwardList)
    {
      std::swap(forwardList.fakeNode_, fakeNode_);
      std::swap(forwardList.begin_, begin_);
      std::swap(forwardList.end_, end_);
      std::swap(forwardList.size_, size_);
    }
    void spliceAfter(const_iterator pos, ForwardList< T > &other)
    {
      spliceAfter(pos, other, other.beforeBegin());
    }
    void spliceAfter(const_iterator pos, ForwardList< T > &other, const_iterator it)
    {
      auto next = pos.ptr_->next;
      pos.ptr_->next = it.ptr_->next;
      other.end_->next = next;
      for (; it != other.end(); it++)
      {
        size_++;
      }
      other.begin_ = nullptr;
      other.end_ = nullptr;
    }
    void spliceAfter(const_iterator pos, ForwardList< T > &other, const_iterator first, const_iterator last)
    {
      auto next = pos.ptr_->next;
      pos.ptr_->next = first.ptr_->next;
      auto start = first;
      while (first != last)
      {
        start = first;
        first++;
      }
      first.ptr_->next = last.ptr_;
      start.ptr_->next = next;
    }
    void remove(const T &data)
    {
      remove(data, beforeBegin());
    }
    template< class Predicate >
    void removeIf(Predicate p)
    {
      auto prev = beforeBegin();
      auto start = begin();
      for (; start != end(); start++)
      {
        if (p(start.ptr_->data))
        {
          remove(start.ptr_->data, prev);
        }
        prev = start;
      }
    }
    void reverse()
    {
      reverse(begin_);
      std::swap(begin_, end_);
    }
    friend bool operator==(const ForwardList< T > &lhr, const ForwardList< T > &rhs)
    {
      auto lhr_begin = lhr.begin();
      auto rhs_begin = rhs.begin();
      while (lhr_begin != lhr.end() && rhs_begin != rhs.end())
      {
        if (*lhr_begin != *rhs_begin)
        {
          return false;
        }
        lhr_begin++;
        rhs_begin++;
      }
      return lhr_begin == lhr.end() && rhs_begin == rhs.end();
    }
    friend bool operator!=(const ForwardList< T > &lhr, const ForwardList< T > &rhs)
    {
      return !(lhr == rhs);
    }
  private:
    details::NodeOneWayList< T > *fakeNode_;
    details::NodeOneWayList< T > *begin_;
    details::NodeOneWayList< T > *end_;
    size_t size_;
    void copy(const ForwardList< T > &forwardList)
    {
      auto iter = forwardList.cbegin();
      while (iter != forwardList.cend())
      {
        pushBack((*iter));
        iter++;
      }
      size_ = forwardList.size_;
    }
    void remove(const T &data, const_iterator it)
    {
      auto i = it;
      while (i != end())
      {
        if (i.ptr_ && i.ptr_->next->data == data)
        {
          eraseAfter(i);
        }
        else
        {
          i++;
        }
      }
    }
    void reverse(details::NodeOneWayList< T > *node)
    {
      if (node->next == nullptr)
      {
        return;
      }
      reverse(node->next);
      node->next->next = node;
      node->next = nullptr;
    }
  };
}
#endif
