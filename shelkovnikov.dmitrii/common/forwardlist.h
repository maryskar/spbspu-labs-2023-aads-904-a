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
      fakeNode_((details::NodeOneWayList< T >*) ::operator new (sizeof(details::NodeOneWayList< T >))),
      begin_(nullptr),
      end_(nullptr),
      size(0)
    {}
    ForwardList(const ForwardList< T > &forwardList):
      fakeNode_((details::NodeOneWayList< T >*) ::operator new (sizeof(details::NodeOneWayList< T >))),
      begin_(nullptr),
      end_(nullptr),
      size(0)
    {
      copy(forwardList);
    }
    ForwardList(ForwardList< T > &&forwardList):
      fakeNode_(forwardList.fakeNode_),
      begin_(forwardList.begin_),
      end_(forwardList.end_),
      size(forwardList.size)
    {
      forwardList.fakeNode_ = nullptr;
      forwardList.begin_ = forwardList.fakeNode_;
      forwardList.end_ = forwardList.fakeNode_;
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
      size = forwardList.size;
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
      size = 0;
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
      it.ptr_->next = next->next;
      if (it.ptr_ == fakeNode_)
      {
        if (it.ptr_->next == end_)
        {
          end_ = nullptr;
        }
        begin_ = it.ptr_->next;
      }
      delete next;
      size--;
      return iterator(it.ptr_->next);
    }
    iterator eraseAfter(const_iterator first, const_iterator second)
    {
      while (first != second)
      {
        first = eraseAfter(first);
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
      size++;
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
      if (count < size)
      {
        auto b = std::next(begin(), count);
        eraseAfter(b, end());
      }
    }
  private:
    details::NodeOneWayList< T > *fakeNode_;
    details::NodeOneWayList< T > *begin_;
    details::NodeOneWayList< T > *end_;
    size_t size;
    void copy(const ForwardList< T > &forwardList)
    {
      auto iter = forwardList.cbegin();
      while (iter != forwardList.cend())
      {
        pushBack((*iter));
        iter++;
      }
      size = forwardList.size;
    }
  };
}
#endif
