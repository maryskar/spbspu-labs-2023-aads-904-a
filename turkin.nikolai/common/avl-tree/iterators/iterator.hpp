#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <utility>
#include <cassert>
#include "avl-tree/tree-node.hpp"

namespace turkin
{
  template< typename K, typename V, typename C >
  class AVLtree;
  template< typename K, typename V, typename C >
  class Iterator
  {
    friend class AVLtree< K, V, C >;
    using it = Iterator< K, V, C >;
    using tree_t = std::pair< K, V >;
    using node_t = TreeNode< tree_t > *;
    public:
      Iterator();
      it & operator=(const it & rhs) = default;
      ~Iterator() = default;
      it & operator++();
      it operator++(int);
      it & operator--();
      it operator--(int);
      tree_t & operator*();
      tree_t * operator->();
      bool operator==(const it & rhs) const;
      bool operator!=(const it & rhs) const;
    private:
      explicit Iterator(node_t rhs, node_t end);
      node_t cur_;
      node_t end_;
  };
}

template< typename K, typename V, typename C >
turkin::Iterator< K, V, C >::Iterator():
  cur_(nullptr),
  end_(nullptr)
{}

template< typename K, typename V, typename C >
turkin::Iterator< K, V, C >::Iterator(node_t rhs, node_t end):
  cur_(rhs),
  end_(end)
{}

template< typename K, typename V, typename C >
turkin::Iterator< K, V, C > & turkin::Iterator< K, V, C >::operator++()
{
  assert(cur_ != nullptr);
  if (cur_->right != end_)
  {
    cur_ = cur_->right;
    while (cur_->left != end_)
    {
      cur_ = cur_->left;
    }
  }
  else
  {
    node_t parent = cur_->parent;
    while (parent != end_ && cur_ == parent->right)
    {
      cur_ = parent;
      parent = parent->parent;
    }
    cur_ = parent;
  }
  return * this;
}

template< typename K, typename V, typename C >
turkin::Iterator< K, V, C > turkin::Iterator< K, V, C >::operator++(int)
{
  assert(cur_ != nullptr);
  auto result(*this);
  ++(*this);
  return result;
}

template< typename K, typename V, typename C >
turkin::Iterator< K, V, C > & turkin::Iterator< K, V, C >::operator--()
{
  assert(cur_ != nullptr);
  if (cur_->left != end_)
  {
    cur_ = cur_->left;
    while (cur_->right != end_)
    {
      cur_ = cur_->right;
    }
  }
  else
  {
    node_t parent = cur_->parent;
    if (cur_ != end_)
    {
      while (parent != end_ && cur_ == parent->left)
      {
        cur_ = parent;
        parent = parent->parent;
      }
    }
    cur_ = parent;
  }
  return * this;
}

template< typename K, typename V, typename C >
turkin::Iterator< K, V, C > turkin::Iterator< K, V, C >::operator--(int)
{
  assert(cur_ != nullptr);
  auto result(*this);
  --(*this);
  return result;
}

template< typename K, typename V, typename C >
std::pair< K, V > & turkin::Iterator< K, V, C >::operator*()
{
  assert(cur_ != nullptr);
  return cur_->data;
}

template< typename K, typename V, typename C >
std::pair< K, V > * turkin::Iterator< K, V, C >::operator->()
{
  assert(cur_ != nullptr);
  return std::addressof(cur_->data);
}

template< typename K, typename V, typename C >
bool turkin::Iterator< K, V, C >::operator==(const Iterator< K, V, C > & rhs) const
{
  return cur_ == rhs.cur_;
}

template< typename K, typename V, typename C >
bool turkin::Iterator< K, V, C >::operator!=(const Iterator< K, V, C > & rhs) const
{
  return !(rhs == *this);
}

#endif
