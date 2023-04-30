#ifndef SPBSPU_LABS_2023_AADS_904_A_TWOTHREETREEITERATOR_H
#define SPBSPU_LABS_2023_AADS_904_A_TWOTHREETREEITERATOR_H
#include "twoThreeTree.h"
#include "nodeOfTwoThreeTree.h"
namespace dimkashelk
{
  template< typename Key, typename Value, typename Compare >
  class TwoThreeTree;
  template< typename Key, typename Value, typename Compare >
  class TwoThreeTreeIterator: public std::iterator< std::forward_iterator_tag, Value >
  {
  friend class TwoThreeTree< Key, Value, Compare >;
  using node_type = details::NodeOfTwoThreeTree< Key, Value, Compare >;
  public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = std::pair< Key, Value >;
    using pointer = std::pair< Key, Value >*;
    using reference = std::pair< Key, Value >&;
    TwoThreeTreeIterator &operator++()
    {
      next();
      return *this;
    }
    TwoThreeTreeIterator operator++(int)
    {
      TwoThreeTreeIterator< Key, Value, Compare > result(*this);
      next();
      return result;
    }
    reference operator*()
    {
      return value_;
    }
    pointer operator->()
    {
      return std::addressof(value_);
    }
    bool operator==(const TwoThreeTreeIterator &other) const
    {
      return node_ == other.node_;
    }
    bool operator!=(const TwoThreeTreeIterator &other) const
    {
      return !(node_ == other.node_);
    }
  private:
    value_type value_;
    node_type *node_;
    node_type *prev_;
    explicit TwoThreeTreeIterator(node_type *node):
      value_{(node == nullptr) ? Key() : node->key[0], (node == nullptr) ? Value() : node->value[0]},
      node_(node),
      prev_(nullptr)
    {};
    void next()
    {
      if (node_->getLastChildren() == nullptr)
      {
        if (node_->size == 1)
        {
          node_type *new_node = goUp(node_);
          if (new_node->parent == nullptr)
          {
            node_ = nullptr;
            return;
          }
          node_ = new_node->parent;
          prev_ = new_node;
          if (prev_ == node_->first)
          {
            set(0);
          }
          else if (prev_ == node_->second && node_->size == 2)
          {
            set(1);
          }
        }
        else
        {
          if (value_.first == node_->key[1])
          {
            prev_ = goUp(node_);
            node_ = prev_->parent;
            if (node_ == nullptr)
            {
              return;
            }
            if (node_->first == prev_)
            {
              set(0);
            }
            else
            {
              set(1);
            }
          }
          else
          {
            set(1);
          }
        }
      }
      else
      {
        if (node_->first == prev_)
        {
          node_ = goDown(node_->second);
        }
        else if (node_->second == prev_ && node_->size == 2)
        {
          node_ = goDown(node_->third);
        }
        prev_ = node_->parent;
        set(0);
      }
    }
    node_type *goUp(node_type *node)
    {
      node_type *parent = node->parent;
      while (parent && parent->getLastChildren() == node)
      {
        node = parent;
        parent = parent->parent;
      }
      return node;
    }
    static node_type *goDown(node_type *node)
    {
      if (node == nullptr)
      {
        return nullptr;
      }
      while (node->first)
      {
        node = node->first;
      }
      return node;
    }
    void set(unsigned ind)
    {
      value_.first = node_->key[ind];
      value_.second = node_->value[ind];
    }
  };
}
#endif