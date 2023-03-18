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
  template < class T >
  class ForwardList
  {
  public:
    class Iterator
    {
    public:
      explicit Iterator(details::Node< T > *ptr):
        node(ptr)
      {}
      Iterator &operator++()
      {
        node = node->next;
        return *this;
      }
      Iterator &operator++(int)
      {
        node = node->next;
        return *this;
      }
      T &operator*() const
      {
        return node->data;
      }
      bool operator==(const Iterator &other) const
      {
        return node == other.node;
      }
      bool operator!=(const Iterator &other) const
      {
        return node != other.node;
      }
    private:
      details::Node< T > *node;
    };
    ForwardList():
      begin_(nullptr),
      end_(nullptr)
    {}
    ForwardList(const ForwardList< T > &forwardList):
      begin_(nullptr),
      end_(nullptr)
    {
      details::Node< T > *start = forwardList.begin_;
      while (start)
      {
        pushBack(start->data);
        start = start->next;
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
    void pushBack(const T &data)
    {
      insertBefore(end(), data);
    }
    void insertBefore(ForwardList< T >::Iterator iterator, const T &data)
    {
      auto *new_node = new details::Node< T >(data);
      if (!begin_)
      {
        begin_ = new_node;
        iterator.ptr_ = new_node;
        return;
      }
      if (iterator.ptr_ == begin_)
      {
        begin_->prev = new_node;
        new_node->next = begin_;
        if (!end_)
        {
          end_ = begin_;
        }
        begin_ = new_node;
        return;
      }
      if (iterator.ptr_ != end().ptr_)
      {
        new_node->next = iterator.ptr_;
        new_node->prev = iterator.ptr_->prev;
        iterator.ptr_->prev->next = new_node;
        iterator.ptr_->prev = new_node;
      }
      else
      {
        if (end_)
        {
          end_->next = new_node;
          new_node->prev = end_;
          end_ = new_node;
        }
        else
        {
          begin_->next = new_node;
          new_node->prev = begin_;
          end_ = new_node;
        }
      }
    }
    void remove(ForwardList< T >::Iterator &iterator)
    {
      if (iterator.ptr_)
      {
        if (iterator.ptr_ == begin_)
        {
          details::Node< T > *node = begin_->next;
          delete begin_;
          begin_ = node;
          if (begin_)
          {
            begin_->prev = nullptr;
          }
          iterator.ptr_ = begin_;
        }
        else if (iterator.ptr_ == end_)
        {
          end_->prev->next = nullptr;
          details::Node< T > *new_node = end_->prev;
          delete end_;
          if (new_node != begin_)
          {
            end_ = new_node;
          }
          else
          {
            end_ = nullptr;
          }
          iterator.ptr_ = nullptr;
        }
        else
        {
          iterator.ptr_->prev->next = iterator.ptr_->next;
          iterator.ptr_->next->prev = iterator.ptr_->prev;
          details::Node< T > *new_ptr_ = iterator.ptr_->next;
          delete iterator.ptr_;
          iterator.ptr_ = new_ptr_;
        }
      }
    }
    void free()
    {
      while (begin_)
      {
        auto iter = begin();
        remove(iter);
      }
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
      auto first_end = first.end();
      auto second_start = second.begin();
      auto second_end = second.end();
      while (first_start != first_end && second_start != second_end && (*first_start) == (*second_start))
      {
        first_start++;
        second_start++;
      }
      if (first_start != first_end)
      {
        if (second_start != second_end)
        {
          return (*first_start) > (*second_start);
        }
        return true;
      }
      return second_start != second_end;
    }
  private:
    details::Node< T > *begin_;
    details::Node< T > *end_;
  };
}
#endif
