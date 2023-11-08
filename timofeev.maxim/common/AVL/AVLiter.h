#ifndef SPBSPU_LABS_2023_AADS_904_A_AVLITER_H
#define SPBSPU_LABS_2023_AADS_904_A_AVLITER_H
#include <cassert>
#include <functional>
#include <iterator>
#include <memory>
#include "AVLConstIter.h"
#include <Trees/Tree.h>
namespace timofeev
{
  template< typename K, typename V, typename C >
  class AVLConstIter;
  template< typename Key, typename Value, typename Compare = std::less< Key > >
  class AVLIterator: public std::iterator<
    std::bidirectional_iterator_tag, std::pair< Key, Value > >
  {
    template< typename K, typename V, typename C >
    friend class AVL;
  public:
    using iter = AVLIterator< Key, Value, Compare >;
    using constIter = AVLConstIter< Key, Value, Compare >;
    using pairType = std::pair< Key, Value >;
    using tree = Tree< pairType >;
    AVLIterator();
    explicit AVLIterator(const constIter& rhs);
    AVLIterator(const iter &) = default;
    AVLIterator(tree* rhs);
    ~AVLIterator() = default;
    iter& operator=(const iter &) = default;

    iter& operator++();
    iter operator++(int);

    iter& operator--();
    iter operator--(int);

    pairType& operator*() const;
    pairType* operator->() const;

    bool operator!=(const iter& rhs) const;
    bool operator==(const iter& rhs) const;

  private:
    tree* node_;
  };

  template< typename Key, typename Value, typename Compare >
  AVLIterator< Key, Value, Compare > &AVLIterator<Key, Value, Compare>::operator--()
  {
    assert(node_ != nullptr);
    if (node_->left_ != nullptr)
    {
      node_ = node_->left_;
      while (node_->right_ != nullptr)
      {
        node_ = node_->right_;
      }
    }
    else
    {
      tree* tempNode = node_;
      node_ = node_->parent_;
      while (node_ && tempNode == node_->left_)
      {
        tempNode = node_;
        if (node_->parent_)
        {
          node_ = node_->parent_;
        }
        else
        {
          break;
        }
      }
    }
    return *this;
  }

  template< typename Key, typename Value, typename Compare >
  AVLIterator< Key, Value, Compare > &AVLIterator< Key, Value, Compare >::operator++()
  {
    assert(node_ != nullptr);
    if (node_->right_ != nullptr)
    {
      node_ = node_->right_;
      while (node_->left_ != nullptr)
      {
        node_ = node_->left_;
      }
    }
    else
    {
      while (node_->parent_ != nullptr && node_ == node_->parent_->right_)
      {
        node_ = node_->parent_;
      }
      node_ = node_->parent_;
    }
    return *this;
  }
  template< typename Key, typename Value, typename Compare >
  std::pair< Key, Value > *AVLIterator< Key, Value, Compare >::operator->() const
  {
    assert(node_ != nullptr);
    return &(node_->data);
  }

  template< typename Key, typename Value, typename Compare >
  std::pair< Key, Value > &AVLIterator< Key, Value, Compare >::operator*() const
  {
    assert(node_ != nullptr);
    return node_->data;
  }

  template< typename Key, typename Value, typename Compare >
  bool AVLIterator< Key, Value, Compare >::operator==(const iter& rhs) const
  {
    return node_ == rhs.node_;
  }

  template< typename Key, typename Value, typename Compare >
  bool AVLIterator< Key, Value, Compare >::operator!=(const iter& rhs) const
  {
    return !(*this == rhs);
  }

  template< typename Key, typename Value, typename Compare >
  AVLIterator< Key, Value, Compare > AVLIterator< Key, Value, Compare >::operator--(int)
  {
    assert(node_ != nullptr);
    auto res(*this);
    --(*this);
    return res;
  }

  template< typename Key, typename Value, typename Compare >
  AVLIterator< Key, Value, Compare > AVLIterator< Key, Value, Compare >::operator++(int)
  {
    assert(node_ != nullptr);
    auto res(*this);
    ++(*this);
    return res;
  }

  template< typename Key, typename Value, typename Compare >
  AVLIterator< Key, Value, Compare >::AVLIterator(tree* rhs):
    node_(rhs)
  {}

  template< typename Key, typename Value, typename Compare >
  AVLIterator< Key, Value, Compare >::AVLIterator(const constIter& rhs):
    node_(rhs.node_)
  {}

  template< typename Key, typename Value, typename Compare >
  AVLIterator< Key, Value, Compare >::AVLIterator():
    node_(nullptr)
  {}

}
#endif
