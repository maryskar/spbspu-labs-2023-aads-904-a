#ifndef SPBSPU_LABS_2023_AADS_904_A_FORWARDLIST_H
#define SPBSPU_LABS_2023_AADS_904_A_FORWARDLIST_H
#include <cstddef>
#include <cassert>
#include <iterator>
#include <cstdarg>
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
  using reference = T&;
  using const_reference = const T&;
  public:
    ForwardList():
      fakeNode_((details::NodeForwardList< T >*) ::operator new (sizeof(details::NodeForwardList< T >))),
      begin_(nullptr),
      end_(nullptr)
    {}
    ForwardList(const ForwardList< T > &forwardList):
      fakeNode_((details::NodeForwardList< T >*) ::operator new (sizeof(details::NodeForwardList< T >))),
      begin_(nullptr),
      end_(nullptr)
    {
      copy(forwardList);
    }
    ForwardList(ForwardList< T > &&forwardList):
      fakeNode_(forwardList.fakeNode_),
      begin_(forwardList.begin_),
      end_(forwardList.end_)
    {
      forwardList.fakeNode_ = nullptr;
      forwardList.begin_ = forwardList.fakeNode_;
      forwardList.end_ = forwardList.fakeNode_;
    }
    ~ForwardList()
    {
      free();
      delete fakeNode_;
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
      return iterator(fakeNode_);
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
      return const_iterator(fakeNode_);
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
      fakeNode_->next = begin_;
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
        fakeNode_->next = begin_;
      }
      else
      {
        begin_->next = node;
        node->prev = begin_;
        end_ = node;
      }
    }
    iterator insertAfter(const_iterator it, const T &data)
    {
      auto *newNode = new details::NodeForwardList< T >(data);
      newNode->next = it.ptr_->next;
      if (newNode->next)
      {
        newNode->next->prev = newNode;
      }
      it.ptr_->next = newNode;
      newNode->prev = it.ptr_;
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
    iterator eraseAfter(const const_iterator it)
    {
      auto next = it.ptr_->next;
      it.ptr_->next = next->next;
      delete next;
      return iterator(it.ptr_->next);
    }
    iterator eraseAfter(const const_iterator first, const const_iterator second)
    {
      while (first != second)
      {
        first = eraseAfter(first);
      }
      return second;
    }
    template < typename ... Args >
    iterator emplaceAfter(const_iterator pos, Args&&... args)
    {
      return insertAfter(pos, T(args...));
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
  private:
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
