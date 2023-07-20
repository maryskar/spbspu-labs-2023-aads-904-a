#ifndef S4_AVL_REVERSE_ITER_H
#define S4_AVL_REVERSE_ITER_H
#include <cassert>
#include <functional>
#include <iterator>
#include <memory>
#include <utility>
#include "const_AVL_reverse_iter.h"
#include "tree.h"

namespace mashkin
{
  template< class Key, class Value, class Comp = std::less< Key > >
  class ReverseAVLMapIter: public std::iterator< std::bidirectional_iterator_tag, std::pair< Key, Value > >
  {
  public:
    using riter = ReverseAVLMapIter< Key, Value, Comp >;
    using v_type = std::pair< Key, Value >;
    using tree = Tree< v_type >;
    ReverseAVLMapIter();
    ~ReverseAVLMapIter() = default;
    ReverseAVLMapIter(const riter&) = default;
    explicit ReverseAVLMapIter(tree* rhs);

    riter& operator=(const riter&) = default;
    riter& operator++();
    riter operator++(int);
    riter& operator--();
    riter operator--(int);

    v_type& operator*();
    v_type* operator->();

    bool operator!=(const riter& rhs) const;
    bool operator==(const riter& rhs) const;

  private:
    template< class K, class V, class C >
    friend class ConstReverseAVLMapIter;
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

  template< class Key, class Value, class Comp >
  ReverseAVLMapIter< Key, Value, Comp >::ReverseAVLMapIter(tree* rhs):
    fake_(getFake(rhs)),
    node_(rhs),
    comp_()
  {
  }

  template< class Key, class Value, class Comp >
  ReverseAVLMapIter< Key, Value, Comp >::ReverseAVLMapIter():
    fake_(nullptr),
    node_(nullptr),
    comp_()
  {
  }

  template< class K, class V, class C >
  typename ReverseAVLMapIter< K, V, C >::tree* ReverseAVLMapIter< K, V, C >::getFake(tree* rhs)
  {
    auto fake = rhs->parent_;
    while (fake->left_ || fake->right_)
    {
      fake = fake->parent_;
    }
    return fake;
  }

  template< class K, class V, class C >
  bool ReverseAVLMapIter< K, V, C >::operator==(const riter& rhs) const
  {
    return node_ == rhs.node_;
  }

  template< class K, class V, class C >
  bool ReverseAVLMapIter< K, V, C >::operator!=(const riter& rhs) const
  {
    return !(rhs == *this);
  }

  template< class K, class V, class C >
  ReverseAVLMapIter< K, V, C > ReverseAVLMapIter< K, V, C >::operator--(int)
  {
    assert(node_ != nullptr);
    auto res(*this);
    --(*this);
    return res;
  }

  template< class K, class V, class C >
  typename ReverseAVLMapIter< K, V, C >::v_type* ReverseAVLMapIter< K, V, C >::operator->()
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data);
  }

  template< class K, class V, class C >
  typename ReverseAVLMapIter< K, V, C >::v_type& ReverseAVLMapIter< K, V, C >::operator*()
  {
    assert(node_ != nullptr);
    return node_->data;
  }

  template< class K, class V, class C >
  void ReverseAVLMapIter< K, V, C >::doParentForMinus()
  {
    auto newNode = node_->parent_;
    while (newNode != fake_ && !comp_(node_->data.first, newNode->data.first))
    {
      newNode = newNode->parent_;
    }
    node_ = newNode;
  }

  template< class K, class V, class C >
  void ReverseAVLMapIter< K, V, C >::doWhileRight()
  {
    auto newNode = node_->left_;
    while (newNode->right_)
    {
      newNode = newNode->right_;
    }
    node_ = newNode;
  }

  template< class K, class V, class C >
  ReverseAVLMapIter< K, V, C >& ReverseAVLMapIter< K, V, C >::operator--()
  {
    assert(node_ != nullptr);
    if (node_ == fake_)
    {
      node_ = node_->parent_;
      while (node_->left_)
      {
        node_ = node_->left_;
      }
    }
    else if (!node_->left_ && !node_->right_ && node_->parent_)
    {
      if (node_ == node_->parent_->left_)
      {
        node_ = node_->parent_;
      }
      else
      {
        doParentForMinus();
      }
    }
    else if (node_->left_ && node_->right_ && node_->parent_)
    {
      doWhileLeft();
    }
    else if (node_->left_ && !node_->right_ && node_->parent_)
    {
      doParentForMinus();
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

  template< class K, class V, class C >
  ReverseAVLMapIter< K, V, C > ReverseAVLMapIter< K, V, C >::operator++(int)
  {
    assert(node_ != nullptr);
    auto res(*this);
    ++(*this);
    return res;
  }

  template< class K, class V, class C >
  void ReverseAVLMapIter< K, V, C >::doWhileLeft()
  {
    auto newNode = node_->right_;
    while (newNode->left_)
    {
      newNode = newNode->left_;
    }
    node_ = newNode;
  }

  template< class K, class V, class C >
  void ReverseAVLMapIter< K, V, C >::doParentForPlus()
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
  ReverseAVLMapIter< K, V, C >& ReverseAVLMapIter< K, V, C >::operator++()
  {
    assert(node_ != nullptr);
    if (!node_->left_ && !node_->right_ && node_->parent_)
    {
      if (node_ == node_->parent_->left_)
      {
        doParentForPlus();
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
      doParentForPlus();
    }
    return *this;
  }
}
#endif
