#ifndef SPBSPU_LABS_2023_AADS_904_A_FORWARDLIST_H
#define SPBSPU_LABS_2023_AADS_904_A_FORWARDLIST_H
#include <cstddef>
#include <iterator>
namespace dimkashelk
{
  template < typename Key, typename Value, typename Compare >
  class ForwardList
  {
  public:
    struct Node
    {
      Key key_;
      Value data_;
      Node *next_;
      Node *prev_;
      Node(Key key, Value value):
        key_(key),
        data_(value),
        next_(nullptr),
        prev_(nullptr)
      {}
    };
    struct Iterator
    {
    public:
      explicit Iterator(Node *ptr):
        ptr_(ptr)
      {}
      std::pair< Key, Value > &operator*() const
      {
        auto *pair = new std::pair< Key, Value >(ptr_->key_, ptr_->data_);
        return *pair;
      }
      Iterator operator++()
      {
        ptr_ = ptr_->next_;
        return *this;
      }
      Iterator &operator++(Key)
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
    ForwardList() :
      begin_(nullptr),
      end_(nullptr),
      compare_(std::less< Key >())
    {}
    void insert(Key key, Value value)
    {
      Node *new_node = new Node(key, value);
      if (!begin_)
      {
        begin_ = new_node;
      }
      else if (!end_)
      {
        if (compare_(begin_->key_, new_node->key_))
        {
          end_ = begin_;
          begin_ = new_node;
          begin_->next_ = end_;
          end_->prev_ = begin_;
        }
        else
        {
          end_ = new_node;
          begin_->next_ = end_;
          end_->prev_ = begin_;
        }
      }
      else
      {
        Node *cur = begin_;
        while (cur)
        {
          if (compare_(cur->key_, new_node->key_))
          {
            new_node->next_ = cur;
            new_node->prev_ = cur->prev_;
            if (cur->prev_)
            {
              cur->prev_->next_ = new_node;
            }
            if (cur->next_)
            {
              cur->next_->prev_ = new_node;
            }
            break;
          }
          cur = cur->next_;
        }
      }
    }
    Iterator begin()
    {
      return Iterator(std::addressof(*begin_));
    }
    Iterator end()
    {
      return Iterator(std::addressof(*end_->next_));
    }
  private:
    Node *begin_;
    Node *end_;
    Compare compare_;
  };
}
#endif
