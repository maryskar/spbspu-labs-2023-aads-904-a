#ifndef SPBSPU_LABS_2023_AADS_904_A_FORWARDLIST_H
#define SPBSPU_LABS_2023_AADS_904_A_FORWARDLIST_H
#include <cstddef>
#include <cassert>
#include <iterator>
#include "forwardlistiterator.h"
#include "nodeforwardlist.h"
namespace dimkashelk
{
  template< typename T >
  class ForwardList
  {
  using iterator = dimkashelk::ForwardListIterator< T >;
  public:
    ForwardList():
      begin_(nullptr),
      end_(nullptr)
    {}
    ForwardList(const ForwardList< T > &forwardList):
      begin_(nullptr),
      end_(nullptr)
    {
      auto iter = forwardList.begin();
      while (iter != forwardList.end())
      {
        pushBack((*iter));
        iter++;
      }
    }
    ForwardList(ForwardList< T > &&forwardList):
      begin_(forwardList.begin_),
      end_(forwardList.end_)
    {
      forwardList.begin_ = nullptr;
      forwardList.end_ = nullptr;
    }
    ~ForwardList()
    {
      free();
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
    void free()
    {
      while (begin_)
      {
        details::NodeForwardList< T > *node = begin_;
        begin_ = begin_->next;
        delete node;
      }
      end_ = nullptr;
    }
    bool empty()
    {
      return begin_ == nullptr;
    }
    iterator begin() const
    {
      return iterator(begin_);
    }
    iterator end() const
    {
      return iterator(nullptr);
    }
    friend bool operator>(const ForwardList< T > &first, const ForwardList< T > &second)
    {
      auto first_start = first.begin();
      auto second_start = second.begin();
      auto first_end = first.end();
      auto second_end = second.end();
      while (first_start != first_end && second_start != second_end)
      {
        if (*first_start != *second_start)
        {
          return *first_start > *second_start;
        }
        ++first_start;
        ++second_start;
      }
      if (first_start == first_end && second_start != second_end)
      {
        return true;
      }
      else if (first_start != first_end && second_start == second_end)
      {
        return false;
      }
      else
      {
        return false;
      }
    }
  private:
    details::NodeForwardList< T > *begin_;
    details::NodeForwardList< T > *end_;
  };
}
#endif
