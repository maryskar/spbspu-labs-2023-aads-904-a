#ifndef SPBSPU_LABS_2023_AADS_904_A_FORWARDLIST_H
#define SPBSPU_LABS_2023_AADS_904_A_FORWARDLIST_H
#include <cstddef>
#include <cassert>
namespace details
{
  template< typename T >
  struct Node
  {
    T data;
    Node *next;
    Node *prev;
    explicit Node(const T &data):
      data(data),
      next(nullptr),
      prev(nullptr)
    {}
  };
}
namespace dimkashelk
{
  template < typename T >
  class ForwardList
  {
  public:
    class Iterator
    {
    friend class ForwardList< T >;
    public:
      explicit Iterator(details::Node< T > *ptr):
        ptr_(ptr)
      {}
      Iterator &operator++()
      {
        ptr_ = ptr_->next;
        return *this;
      }
      Iterator &operator++(int)
      {
        ptr_ = ptr_->next;
        return *this;
      }
      Iterator &operator--()
      {
        ptr_ = ptr_->prev;
        return *this;
      }
      Iterator &operator--(int)
      {
        ptr_ = ptr_->prev;
        return *this;
      }
      T &operator*() const
      {
        return ptr_->data;
      }
      bool operator==(const Iterator &other) const
      {
        return ptr_ == other.ptr_;
      }
      bool operator!=(const Iterator &other) const
      {
        return ptr_ != other.ptr_;
      }
    private:
      details::Node< T > *ptr_;
    };
    ForwardList():
      begin_(nullptr),
      end_(nullptr)
    {}
    ForwardList(const ForwardList< T > &forwardList):
      begin_(nullptr),
      end_(nullptr)
    {
      auto iter = forwardList.begin();
      pushFront(*iter);
      iter++;
      auto begin = this->begin();
      while (iter != forwardList.end())
      {
        insertAfter(begin, *iter);
        iter++;
        begin++;
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
      auto *node = new details::Node< T >(data);
      if (!begin_)
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
    void insertAfter(const Iterator& it, const T& data)
    {
      auto *newNode = new details::Node< T >(data);
      newNode->next = it.node->next;
      if (newNode->next)
      {
        newNode->next->prev = newNode;
      }
      it.node->next = newNode;
      newNode->prev = it.node;
      if (!newNode->next)
      {
        end_ = newNode;
      }
    }
    void free()
    {
      while (begin_)
      {
        details::Node< T > *node = begin_;
        begin_ = begin_->next;
        delete node;
      }
      end_ = nullptr;
    }
    bool empty()
    {
      return begin_ == nullptr;
    }
    Iterator begin() const
    {
      return Iterator(begin_);
    }
    Iterator end() const
    {
      return Iterator(nullptr);
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
    details::Node< T > *begin_;
    details::Node< T > *end_;
  };
}
#endif
