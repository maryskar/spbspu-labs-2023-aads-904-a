#ifndef AVLCONSTITER_H
#define AVLCONSTITER_H
#include <cassert>
#include <functional>
#include <iterator>
#include <memory>
#include "AVLiter.h"
#include <Trees/Tree.h>
namespace timofeev
{
  template< typename K, typename V, typename C >
  class AVLIterator;
  template< typename Key, typename Value, typename Compare >
  class AVLConstIter: public std::iterator<
    std::bidirectional_iterator_tag, std::pair< Key, Value > >
  {
    template< typename K, typename V, typename C >
    friend class AVL;
  public:
    using constIter = AVLConstIter< Key, Value, Compare >;
    using iter = AVLIterator< Key, Value, Compare >;
    using pairType = std::pair< Key, Value >;
    using tree = Tree< pairType >;
    AVLConstIter();
    explicit AVLConstIter(const iter& rhs);
    explicit AVLConstIter(tree* rhs);
    AVLConstIter(const constIter &) = default;
    ~AVLConstIter() = default;
    constIter& operator=(const constIter &) = default;

    constIter& operator++();
    constIter operator++(int);

    constIter& operator--();
    constIter operator--(int);

    const pairType& operator*() const;
    const pairType* operator->() const;

    bool operator!=(const constIter& rhs) const;
    bool operator==(const constIter& rhs) const;
  private:
    tree* node_;
  };

  template<typename Key, typename Value, typename Compare>
  AVLConstIter<Key, Value, Compare>::AVLConstIter():
    node_(nullptr)
  {}

  template< typename Key, typename Value, typename Compare >
  AVLConstIter< Key, Value, Compare >::AVLConstIter(tree *rhs):
    node_(rhs)
  {}

  template< typename Key, typename Value, typename Compare >
  AVLConstIter< Key, Value, Compare > &AVLConstIter< Key, Value, Compare >::operator--()
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
  AVLConstIter< Key, Value, Compare > &AVLConstIter< Key, Value, Compare >::operator++()
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
  const std::pair< Key, Value > *AVLConstIter< Key, Value, Compare >::operator->() const
  {
    assert(node_ != nullptr);
    return &(node_->data);
  }

  template< typename Key, typename Value, typename Compare >
  const std::pair< Key, Value > &AVLConstIter< Key, Value, Compare >::operator*() const
  {
    assert(node_ != nullptr);
    return node_->data;
  }

  template< typename Key, typename Value, typename Compare >
  bool AVLConstIter< Key, Value, Compare >::operator==(const constIter& rhs) const
  {
    return node_ == rhs.node_;
  }

  template< typename Key, typename Value, typename Compare >
  bool AVLConstIter< Key, Value, Compare >::operator!=(const constIter& rhs) const
  {
    return !(*this == rhs);
  }

  template< typename Key, typename Value, typename Compare >
  AVLConstIter< Key, Value, Compare > AVLConstIter< Key, Value, Compare >::operator--(int)
  {
    assert(node_ != nullptr);
    auto res(*this);
    --(*this);
    return res;
  }

  template< typename Key, typename Value, typename Compare >
  AVLConstIter< Key, Value, Compare > AVLConstIter< Key, Value, Compare >::operator++(int)
  {
    assert(node_ != nullptr);
    auto res(*this);
    ++(*this);
    return res;
  }

  template< typename Key, typename Value, typename Compare >
  AVLConstIter< Key, Value, Compare >::AVLConstIter(const iter& rhs):
    node_(rhs.node_)
  {}

}
#endif
