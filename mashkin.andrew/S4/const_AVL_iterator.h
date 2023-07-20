#ifndef S4_CONST_AVL_ITERATOR_H
#define S4_CONST_AVL_ITERATOR_H
#include <cassert>
#include <functional>
#include <iterator>
#include <memory>
#include <AVL.h>
#include "AVL_iterator.h"
#include "tree.h"

namespace mashkin
{
  template< class K, class V, class C >
  class AVLMapIter;

  template< class Key, class Value, class Comp = std::less< Key > >
  class ConstAVLMapIter: public std::iterator< std::bidirectional_iterator_tag, std::pair< Key, Value > >
  {
  public:
    using const_iter = ConstAVLMapIter< Key, Value, Comp >;
    using v_type = std::pair< Key, Value >;
    using tree = Tree< v_type >;
    ConstAVLMapIter();
    ~ConstAVLMapIter() = default;
    ConstAVLMapIter(const const_iter&) = default;
    explicit ConstAVLMapIter(const AVLMapIter< Key, Value, Comp >& rhs);
    explicit ConstAVLMapIter(tree* rhs);

    const_iter& operator=(const const_iter&) = default;
    const_iter& operator++();
    const_iter operator++(int);
    const_iter& operator--();
    const_iter operator--(int);

    const v_type& operator*() const;
    const v_type* operator->() const;

    bool operator!=(const const_iter& rhs) const;
    bool operator==(const const_iter& rhs) const;

  private:
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
  };

  template< class K, class V, class C >
  ConstAVLMapIter< K, V, C >::ConstAVLMapIter(const AVLMapIter< K, V, C >& rhs):
    fake_(rhs.fake_),
    node_(rhs.node_),
    comp_(rhs.comp_)
  {
  }

  template< class Key, class Value, class Comp >
  ConstAVLMapIter< Key, Value, Comp >::ConstAVLMapIter(tree* rhs):
    fake_(getFake(rhs)),
    node_(rhs),
    comp_()
  {
  }

  template< class Key, class Value, class Comp >
  ConstAVLMapIter< Key, Value, Comp >::ConstAVLMapIter():
    fake_(nullptr),
    node_(nullptr),
    comp_()
  {
  }

  template< class K, class V, class C >
  typename ConstAVLMapIter< K, V, C >::tree* ConstAVLMapIter< K, V, C >::getFake(tree* rhs)
  {
    auto fake = rhs;
    while (fake != fake->parent_->parent_)
    {
      fake = fake->parent_;
    }
    return fake;
  }

  template< class K, class V, class C >
  bool ConstAVLMapIter< K, V, C >::operator==(const const_iter& rhs) const
  {
    return node_ == rhs.node_;
  }

  template< class K, class V, class C >
  bool ConstAVLMapIter< K, V, C >::operator!=(const const_iter& rhs) const
  {
    return !(rhs == *this);
  }

  template< class K, class V, class C >
  ConstAVLMapIter< K, V, C > ConstAVLMapIter< K, V, C >::operator--(int)
  {
    assert(node_ != nullptr);
    auto res(*this);
    --(*this);
    return res;
  }

  template< class K, class V, class C >
  const typename ConstAVLMapIter< K, V, C >::v_type* ConstAVLMapIter< K, V, C >::operator->() const
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data);
  }

  template< class K, class V, class C >
  const typename ConstAVLMapIter< K, V, C >::v_type& ConstAVLMapIter< K, V, C >::operator*() const
  {
    assert(node_ != nullptr);
    return node_->data;
  }

  template< class K, class V, class C >
  void ConstAVLMapIter< K, V, C >::doParentForMinus()
  {
    auto newNode = node_->parent_;
    while (newNode != fake_ && comp_(node_->data.first, newNode->data.first))
    {
      newNode = newNode->parent_;
    }
    if (newNode == fake_)
    {
      node_ = node_->left_;
    }
    else
    {
      node_ = newNode;
    }
  }

  template< class K, class V, class C >
  void ConstAVLMapIter< K, V, C >::doWhileRight()
  {
    auto newNode = node_->left_;
    while (newNode->right_)
    {
      newNode = newNode->right_;
    }
    node_ = newNode;
  }

  template< class K, class V, class C >
  ConstAVLMapIter< K, V, C >& ConstAVLMapIter< K, V, C >::operator--()
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
  ConstAVLMapIter< K, V, C > ConstAVLMapIter< K, V, C >::operator++(int)
  {
    assert(node_ != nullptr);
    auto res(*this);
    ++(*this);
    return res;
  }

  template< class K, class V, class C >
  void ConstAVLMapIter< K, V, C >::doWhileLeft()
  {
    auto newNode = node_->right_;
    while (newNode->left_)
    {
      newNode = newNode->left_;
    }
    node_ = newNode;
  }

  template< class K, class V, class C >
  void ConstAVLMapIter< K, V, C >::doParentForPlus()
  {
    auto newNode = node_->parent_;
    while (newNode != fake_ && !comp_(node_->data.first, newNode->data.first))
    {
      newNode = newNode->parent_;
    }
    node_ = newNode;
  }

  template< class K, class V, class C >
  ConstAVLMapIter< K, V, C >& ConstAVLMapIter< K, V, C >::operator++()
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
