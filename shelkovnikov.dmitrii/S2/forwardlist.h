#ifndef SPBSPU_LABS_2023_AADS_904_A_FORWARDLIST_H
#define SPBSPU_LABS_2023_AADS_904_A_FORWARDLIST_H
#include <cstddef>
#include <cassert>
namespace details
{
  template< typename T >
  struct Node
  {
    T data_;
    Node *next_;
    Node *prev_;
    explicit Node(const T &data):
      data_(data),
      next_(nullptr),
      prev_(nullptr)
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
    friend class ForwardList< T >;
    public:
      explicit Iterator(details::Node< T > *ptr):
        ptr_(ptr)
      {}
      T &operator*() const
      {
        return ptr_->data_;
      }
      Iterator &operator++()
      {
        assert(ptr_ != nullptr);
        ptr_ = ptr_->next_;
        return *this;
      }
      Iterator &operator++(int)
      {
        assert(ptr_ != nullptr);
        ptr_ = ptr_->next_;
        return *this;
      }
      friend bool operator==(const Iterator &a, const Iterator &b)
      {
        return a.ptr_ == b.ptr_;
      };
      friend bool operator!=(const Iterator &a, const Iterator &b)
      {
        return a.ptr_ != b.ptr_;
      };
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
      details::Node< T > *start = forwardList.begin_;
      while (start)
      {
        pushBack(start->data_);
        start = start->next_;
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
    void pushBack(T &data)
    {
      insertBefore(end(), data);
    }
    void insertBefore(ForwardList< T >::Iterator iterator, T data)
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
        begin_->prev_ = new_node;
        new_node->next_ = begin_;
        if (!end_)
        {
          end_ = begin_;
        }
        begin_ = new_node;
        return;
      }
      if (iterator.ptr_)
      {
        new_node->next_ = iterator.ptr_;
        new_node->prev_ = iterator.ptr_->prev_;
        iterator.ptr_->prev_->next_ = new_node;
        iterator.ptr_->prev_ = new_node;
      }
      else
      {
        if (end_)
        {
          end_->next_ = new_node;
          new_node->prev_ = end_;
          end_ = new_node;
        }
        else
        {
          begin_->next_ = new_node;
          new_node->prev_ = begin_;
          end_ = new_node;
        }
      }
    }
    void remove(ForwardList< T >::Iterator iterator)
    {
      if (iterator.ptr_)
      {
        if (iterator.ptr_ == begin_)
        {
          details::Node< T > *node = begin_->next_;
          delete begin_;
          begin_ = node;
          if (begin_)
          {
            begin_->prev_ = nullptr;
          }
          iterator.ptr_ = begin_;
        }
        else if (iterator.ptr_ == end_)
        {
          end_->prev_->next_ = nullptr;
          details::Node< T > *new_node = end_->prev_;
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
          iterator.ptr_->prev_->next_ = iterator.ptr_->next_;
          iterator.ptr_->next_->prev_ = iterator.ptr_->prev_;
          details::Node< T > *new_ptr_ = iterator.ptr_->next_;
          delete iterator.ptr_;
          iterator.ptr_ = new_ptr_;
        }
      }
    }
    void free()
    {
      while (begin_)
      {
        remove(begin());
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
