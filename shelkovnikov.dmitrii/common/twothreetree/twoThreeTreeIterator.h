#ifndef SPBSPU_LABS_2023_AADS_904_A_TWOTHREETREEITERATOR_H
#define SPBSPU_LABS_2023_AADS_904_A_TWOTHREETREEITERATOR_H
#include "twoThreeTree.h"
#include "nodeOfTwoThreeTree.h"
namespace dimkashelk
{
  template< typename Key, typename Value, typename Compare >
  class TwoThreeTree;
  template< typename Key, typename Value, typename Compare >
  class TwoThreeTreeReverseIterator;
  template< typename Key, typename Value, typename Compare >
  class TwoThreeTreeIterator: public std::iterator< std::bidirectional_iterator_tag, std::pair< const Key, Value > >
  {
  friend class TwoThreeTree< Key, Value, Compare >;
  friend class TwoThreeTreeReverseIterator< Key, Value, Compare >;
  using node_type = details::NodeOfTwoThreeTree< Key, Value >;
  public:
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = std::pair< const Key, Value >;
    using pointer = std::pair< const Key, Value >*;
    using reference = std::pair< const Key, Value >&;
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
    TwoThreeTreeIterator &operator--()
    {
      prev();
      return *this;
    }
    TwoThreeTreeIterator operator--(int)
    {
      TwoThreeTreeIterator< Key, Value, Compare > result(*this);
      prev();
      return result;
    }
    reference operator*()
    {
      return node_->getData(ind_);
    }
    pointer operator->()
    {
      return std::addressof(node_->getData(ind_));
    }
    bool operator==(const TwoThreeTreeIterator &other) const
    {
      return node_ == other.node_;
    }
    bool operator!=(const TwoThreeTreeIterator &other) const
    {
      return node_ != other.node_;
    }
  private:
    size_t ind_;
    node_type *node_;
    node_type *prev_;
    const dimkashelk::TwoThreeTree< Key, Value, Compare > *parent_;
    TwoThreeTreeIterator(node_type *node, const dimkashelk::TwoThreeTree< Key, Value, Compare > *parent):
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
      if (node_->getLastChild() == nullptr)
      {
        if (node_->getSize() == 1)
        {
          node_type *new_node = goUp(node_);
          if (new_node->getParent() == nullptr)
          {
            node_ = nullptr;
            return;
          }
          node_ = new_node->getParent();
          prev_ = new_node;
          if (prev_ == node_->getFirstChild())
          {
            ind_ = 0;
          }
          else if (prev_ == node_->getSecondChild() && node_->getSize() == 2)
          {
            ind_ = 1;
          }
        }
        else
        {
          if (ind_ == 1)
          {
            prev_ = goUp(node_);
            node_ = prev_->getParent();
            if (node_ == nullptr)
            {
              return;
            }
            if (node_->getFirstChild() == prev_)
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
        if (node_->getFirstChild() == prev_)
        {
          node_ = goDown(node_->getSecondChild());
        }
        else if (node_->getSecondChild() == prev_ && node_->getSize() == 2)
        {
          node_ = goDown(node_->getThirdChild());
        }
        prev_ = node_->getParent();
        ind_ = 0;
      }
    }
    void updateNodeUpBack()
    {
      node_type *new_node = goUpBack(node_);
      if (new_node->getParent() == nullptr)
      {
        node_ = nullptr;
        return;
      }
      node_ = new_node->getParent();
      prev_ = new_node;
      if (prev_ == node_->getFirstChild())
      {
        ind_ = 1;
      }
      else
      {
        ind_ = 0;
      }
    }
    void updateNodeDownBack(node_type *node)
    {
      node_ = goDownBack(node);
      prev_ = node_->getParent();
      if (node_->getSize() == 2)
      {
        ind_ = 1;
      }
      else
      {
        ind_ = 0;
      }
    }
    void prev()
    {
      if (ind_ == 1)
      {
        if (node_->getFirstChild() == nullptr)
        {
          ind_ = 0;
        }
        else
        {
          updateNodeDownBack(node_->getSecondChild());
        }
      }
      else
      {
        if (node_->getLastChildren() == nullptr)
        {
          updateNodeUpBack();
        }
        else
        {
          updateNodeDownBack(node_->getFirstChild());
        }
      }
    }
    node_type *goUp(node_type *node)
    {
      node_type *parent = node->getParent();
      while (parent && parent->getLastChild() == node)
      {
        node = parent;
        parent = parent->getParent();
      }
      return node;
    }
    static node_type *goDown(node_type *node)
    {
      if (node == nullptr)
      {
        return nullptr;
      }
      while (node->getFirstChild())
      {
        node = node->getFirstChild();
      }
      return node;
    }
    node_type *goUpBack(node_type *node)
    {
      node_type *p = node->getParent();
      while (p && ((p->getFirstChild() == node && p->getSize() == 1) || (p->getSecondChild() == node && p->getSize() == 2)))
      {
        node = p;
        p = p->getParent();
      }
      return node;
    }
    static node_type *goDownBack(node_type *node)
    {
      if (node == nullptr)
      {
        return nullptr;
      }
      while (node->getLastChild())
      {
        node = node->getLastChild();
      }
      return node;
    }
  };
}
#endif
