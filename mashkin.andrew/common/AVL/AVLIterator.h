#ifndef S4_AVL_ITERATOR_H
#define S4_AVL_ITERATOR_H
#include <cassert>
#include <functional>
#include <iterator>
#include <memory>
#include <utility>
#include "AVL.h"
#include "ConstAVLIterator.h"
#include "tree.h"

namespace mashkin
{
  template< class Key, class Value, class Comp = std::less< Key > >
  class AVLMapIter: public std::iterator< std::bidirectional_iterator_tag, std::pair< Key, Value > >
  {
  public:
    using iter = AVLMapIter< Key, Value, Comp >;
    using v_type = std::pair< Key, Value >;
    using tree = Tree< v_type >;
    AVLMapIter();
    ~AVLMapIter() = default;
    AVLMapIter(const iter&) = default;

    iter& operator=(const iter&) = default;
    iter& operator++();
    iter operator++(int);
    iter& operator--();
    iter operator--(int);

    v_type& operator*();
    v_type* operator->();

    bool operator!=(const iter& rhs) const;
    bool operator==(const iter& rhs) const;

  private:
    template< class K, class V, class C >
    friend class ConstAVLMapIter;
    template< class K, class V, class C >
    friend class AVL;
    tree* fake_;
    tree* node_;
    Comp comp_;

    tree* getFake(tree* rhs);
    void doParentForPlus();
    void doParentForMinus();
    void doWhileLeft();
    void doWhileRight();

    explicit AVLMapIter(tree* rhs);
  };

  template< class Key, class Value, class Comp >
  AVLMapIter< Key, Value, Comp >::AVLMapIter(tree* rhs):
    fake_(getFake(rhs)),
    node_(rhs),
    comp_()
  {
  }

  template< class Key, class Value, class Comp >
  AVLMapIter< Key, Value, Comp >::AVLMapIter():
    fake_(nullptr),
    node_(nullptr),
    comp_()
  {
  }

  template< class K, class V, class C >
  typename AVLMapIter< K, V, C >::tree* AVLMapIter< K, V, C >::getFake(tree* rhs)
  {
    auto fake = rhs->parent_;
    while (fake->left_ || fake->right_)
    {
      fake = fake->parent_;
    }
    return fake;
  }

  template< class K, class V, class C >
  bool AVLMapIter< K, V, C >::operator==(const iter& rhs) const
  {
    return node_ == rhs.node_;
  }

  template< class K, class V, class C >
  bool AVLMapIter< K, V, C >::operator!=(const iter& rhs) const
  {
    return !(rhs == *this);
  }

  template< class K, class V, class C >
  AVLMapIter< K, V, C > AVLMapIter< K, V, C >::operator--(int)
  {
    assert(node_ != nullptr);
    auto res(*this);
    --(*this);
    return res;
  }

  template< class K, class V, class C >
  typename AVLMapIter< K, V, C >::v_type* AVLMapIter< K, V, C >::operator->()
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data);
  }

  template< class K, class V, class C >
  typename AVLMapIter< K, V, C >::v_type& AVLMapIter< K, V, C >::operator*()
  {
    assert(node_ != nullptr);
    return node_->data;
  }

  template< class K, class V, class C >
  void AVLMapIter< K, V, C >::doParentForMinus()
  {
    auto parentNode = node_->parent_;
    auto childrenNode = node_;
    while (parentNode != fake_ && parentNode->right_ != childrenNode)
    {
      childrenNode = parentNode;
      parentNode = parentNode->parent_;
    }
    if (parentNode == fake_)
    {
      node_ = node_->left_;
    }
    else
    {
      node_ = parentNode;
    }
  }

  template< class K, class V, class C >
  void AVLMapIter< K, V, C >::doWhileRight()
  {
    auto newNode = node_->left_;
    while (newNode->right_)
    {
      newNode = newNode->right_;
    }
    node_ = newNode;
  }

  template< class K, class V, class C >
  AVLMapIter< K, V, C >& AVLMapIter< K, V, C >::operator--()
  {
    assert(node_ != nullptr);
    if (node_ == fake_)
    {
      node_ = node_->parent_;
      while (node_->right_)
      {
        node_ = node_->right_;
      }
    }
    else if (!node_->left_ && !node_->right_ && node_->parent_)
    {
      if (node_ == node_->parent_->left_)
      {
        doParentForMinus();
      }
      else
      {
        node_ = node_->parent_;
      }
    }
    else if (node_->left_ && node_->right_ && node_->parent_)
    {
      doWhileRight();
    }
    else if (node_->left_ && !node_->right_ && node_->parent_)
    {
      doWhileRight();
    }
    else if (!node_->parent_)
    {
      doWhileRight();
    }
    else if (!node_->left_ && node_->right_ && node_->parent_)
    {
      doParentForMinus();
    }
    return *this;
  }

  template< class K, class V, class C >
  AVLMapIter< K, V, C > AVLMapIter< K, V, C >::operator++(int)
  {
    assert(node_ != nullptr);
    auto res(*this);
    ++(*this);
    return res;
  }

  template< class K, class V, class C >
  void AVLMapIter< K, V, C >::doWhileLeft()
  {
    auto newNode = node_->right_;
    while (newNode->left_)
    {
      newNode = newNode->left_;
    }
    node_ = newNode;
  }

  template< class K, class V, class C >
  void AVLMapIter< K, V, C >::doParentForPlus()
  {
    auto parentNode = node_->parent_;
    auto childrenNode = node_;
    while (parentNode != fake_ && parentNode->right_ == childrenNode)
    {
      childrenNode = parentNode;
      parentNode = parentNode->parent_;
    }
    node_ = parentNode;
  }

  template< class K, class V, class C >
  AVLMapIter< K, V, C >& AVLMapIter< K, V, C >::operator++()
  {
    assert(node_ != nullptr);
    if (!node_->left_ && !node_->right_ && node_->parent_)
    {
      if (node_ == node_->parent_->left_)
      {
        node_ = node_->parent_;
      }
      else
      {
        doParentForPlus();
      }
    }
    else if (node_->left_ && node_->right_ && node_->parent_)
    {
      doWhileLeft();
    }
    else if (node_->left_ && !node_->right_ && node_->parent_)
    {
      doParentForPlus();
    }
    else if (!node_->parent_)
    {
      doWhileLeft();
    }
    else if (!node_->left_ && node_->right_ && node_->parent_)
    {
      doWhileLeft();
    }
    return *this;
  }
}
#endif
