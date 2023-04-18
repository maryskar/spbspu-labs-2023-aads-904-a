#ifndef SPBSPU_LABS_2023_AADS_904_A_FORWARDLIST_H
#define SPBSPU_LABS_2023_AADS_904_A_FORWARDLIST_H
#include <cstddef>
#include <cassert>
#include <iterator>
#include "forwardlistiterator.h"
#include "forwardlistiteratorconst.h"
#include "nodeforwardlist.h"
namespace dimkashelk
{
  template< typename T >
  class ForwardList
  {
  using iterator = dimkashelk::ForwardListIterator< T >;
  using const_iterator = dimkashelk::ForwardListIteratorConst< T >;
  public:
    ForwardList():
      fakeNode_(new (buffer) details::NodeForwardList< T >()),
      begin_(fakeNode_),
      end_(fakeNode_)
    {}
    ForwardList(const ForwardList< T > &forwardList):
      fakeNode_(new (buffer) details::NodeForwardList< T >()),
      begin_(fakeNode_),
      end_(fakeNode_)
    {
      copy(forwardList);
    }
    ForwardList(ForwardList< T > &&forwardList):
      begin_(forwardList.begin_),
      end_(forwardList.end_)
    {
      forwardList.begin_ = forwardList.fakeNode_;
      forwardList.end_ = forwardList.fakeNode_;
    }
    ~ForwardList()
    {
      free();
    }
    ForwardList &operator=(const ForwardList< T > &forwardList)
    {
      if (std::addressof(forwardList) == this)
      {
        return *this;
      }
      free();
      copy(forwardList);
      return *this;
    }
    ForwardList &operator=(ForwardList< T > &&forwardList)
    {
      if (std::addressof(forwardList) == this)
      {
        return *this;
      }
      begin_ = forwardList.begin_;
      end_ = forwardList.end_;
      forwardList.begin_ = forwardList.fakeNode_;
      forwardList.end_ = forwardList.fakeNode_;
      return *this;
    }
    void pushFront(const T &data)
    {
      auto *node = new details::NodeForwardList< T >(data);
      if (begin_)
      {
        node->next = begin_;
        begin_->prev = node;
        begin_ = node;
      }
      else
      {
        begin_ = node;
      }
    }
    void pushBack(const T &data)
    {
      auto *node = new details::NodeForwardList< T >(data);
      if (end_)
      {
        node->prev = end_;
        end_->next = node;
        end_ = node;
      }
      else if (!begin_)
      {
        begin_ = node;
      }
      else
      {
        begin_->next = node;
        node->prev = begin_;
        end_ = node;
      }
    }
    void insertAfter(const iterator &it, const T &data)
    {
      auto *newNode = new details::NodeForwardList< T >(data);
      newNode->next = it.ptr_->next;
      if (newNode->next)
      {
        newNode->next->prev = newNode;
      }
      it.ptr_->next = newNode;
      newNode->prev = it.ptr_;
      if (!newNode->next)
      {
        end_ = newNode;
      }
    }
    void insertAfter(const const_iterator &it, const T &data)
    {
      insertAfter(iterator(it.ptr_), data);
    }
    void free()
    {
      while (begin_)
      {
        details::NodeForwardList< T > *node = begin_;
        begin_ = begin_->next;
        delete node;
      }
      begin_ = fakeNode_;
      end_ = fakeNode_;
    }
    bool empty()
    {
      return begin_ == nullptr;
    }
    iterator begin()
    {
      return iterator(begin_);
    }
    iterator end()
    {
      return iterator(fakeNode_);
    }
    const_iterator cbegin() const
    {
      return const_iterator(begin_);
    }
    const_iterator cend() const
    {
      return const_iterator(fakeNode_);
    }
  private:
    char buffer[sizeof(details::NodeForwardList< T >)];
    details::NodeForwardList< T > *fakeNode_;
    details::NodeForwardList< T > *begin_;
    details::NodeForwardList< T > *end_;
    void copy(const ForwardList< T > &forwardList)
    {
      auto iter = forwardList.cbegin();
      while (iter != forwardList.cend())
      {
        pushBack((*iter));
        iter++;
      }
    }
  };
}
#endif
