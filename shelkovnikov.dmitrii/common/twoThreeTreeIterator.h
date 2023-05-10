#ifndef SPBSPU_LABS_2023_AADS_904_A_TWOTHREETREEITERATOR_H
#define SPBSPU_LABS_2023_AADS_904_A_TWOTHREETREEITERATOR_H
#include "twoThreeTree.h"
#include "nodeOfTwoThreeTree.h"
namespace dimkashelk
{
  template< typename Key, typename Value, typename Compare >
  class TwoThreeTree;
  template< typename Key, typename Value, typename Compare >
  class TwoThreeTreeIterator: public std::iterator< std::forward_iterator_tag, std::pair< Key, Value > >
  {
  friend class TwoThreeTree< Key, Value, Compare >;
  using node_type = details::NodeOfTwoThreeTree< Key, Value, Compare >;
  using tree_type = TwoThreeTree< Key, Value, Compare >;
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
      return node_->data[ind_];
    }
    pointer operator->()
    {
      return std::addressof(node_->data[ind_]);
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
    size_t ind_;
    node_type *node_;
    node_type *prev_;
    tree_type *parent_;
    explicit TwoThreeTreeIterator(node_type *node, tree_type *parent):
      ind_(0),
      node_(node),
      prev_(nullptr),
      parent_(parent)
    {};
    void next()
    {
      if (node_ == parent_->fakeNode_)
      {
        node_ = goDown(parent_->root_);
        return;
      }
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
            ind_ = 0;
          }
          else if (prev_ == node_->second && node_->size == 2)
          {
            ind_ = 1;
          }
        }
        else
        {
          if (node_->data[ind_].second == node_->key[1])
          {
            prev_ = goUp(node_);
            node_ = prev_->parent;
            if (node_ == nullptr)
            {
              return;
            }
            if (node_->first == prev_)
            {
              ind_ = 0;
            }
            else
            {
              ind_ = 1;
            }
          }
          else
          {
            ind_ = 1;
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
        ind_ = 0;
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
  };
}
#endif