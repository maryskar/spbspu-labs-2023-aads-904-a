#ifndef SPBSPU_LABS_2023_AADS_904_A_FORWARDLIST_H
#define SPBSPU_LABS_2023_AADS_904_A_FORWARDLIST_H
#include <cstddef>
namespace dimkashelk
{
  template < typename T >
  class ForwardList
  {
  public:
    struct Node
    {
      T data_;
      Node *next_;
      Node *prev_;
      explicit Node(T &data):
        data_(data),
        next_(nullptr),
        prev_(nullptr)
      {}
    };
    class Iterator
    {
    friend class ForwardList< T >;
    public:
      explicit Iterator(Node *ptr):
        ptr_(ptr)
      {}
      T &operator*() const
      {
        return ptr_->data_;
      }
      Iterator operator++()
      {
        ptr_ = ptr_->next_;
        return *this;
      }
      Iterator &operator++(int)
      {
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
      Node *ptr_;
    };
    ForwardList():
      begin_(nullptr),
      end_(nullptr)
    {}
    ~ForwardList()
    {
      while (begin_)
      {
        Node *node = begin_;
        begin_ = begin_->next_;
        delete node;
      }
    }
    void insertBefore(ForwardList< T >::Iterator iterator, T data)
    {
      Node *new_node = new Node(data);
      if (!begin_)
      {
        begin_ = new_node;
        iterator.ptr_ = new_node;
        return;
      }
      if (iterator.ptr_ == begin_)
      {
        if (begin_->next_)
        {
          begin_->prev_ = new_node;
          new_node->next_ = begin_;
          begin_ = new_node;
        }
        else
        {
          end_ = begin_;
          end_->prev_ = new_node;
          new_node->next_ = end_;
          begin_ = new_node;
        }
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

        }
      }
    }
    void remove(ForwardList< T >::Iterator iterator)
    {
      if (iterator.ptr_)
      {
        if (iterator.ptr_ == begin_)
        {
          end_->prev_ = nullptr;
          delete begin_;
          begin_ = end_;
          end_ = nullptr;
          iterator.ptr_ = begin_;
        }
        else if (iterator.ptr_ == end_)
        {
          end_->prev_->next_ = nullptr;
          Node *new_node = end_->prev_;
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
          Node *new_ptr_ = iterator.ptr_->next_;
          delete iterator.ptr_;
          iterator.ptr_ = new_ptr_;
        }
      }
    }
    Iterator begin()
    {
      return Iterator(begin_);
    }
    Iterator end()
    {
      return Iterator(nullptr);
    }
  private:
    Node *begin_;
    Node *end_;
  };
}
#endif
