#ifndef DIRECT_ITERATOR_HPP
#define DIRECT_ITERATOR_HPP

#include <utility>
#include <cassert>
#include "../tree-node.hpp"

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
      explicit Iterator(node_t rhs);
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
      node_t cur_;
  };
}

template< typename K, typename V, typename C >
turkin::Iterator< K, V, C >::Iterator():
  cur_(nullptr)
{}

template< typename K, typename V, typename C >
turkin::Iterator< K, V, C >::Iterator(node_t rhs):
  cur_(rhs)
{}

template< typename K, typename V, typename C >
turkin::Iterator< K, V, C > & turkin::Iterator< K, V, C >::operator++()
{
  assert(cur_ != nullptr);
  if (cur_->right != nullptr)
  {
    cur_ = cur_->right;
    while (cur_->left != nullptr)
    {
      cur_ = cur_->left;
    }
  }
  else
  {
    node_t parent = cur_->parent;
    while (parent != nullptr && cur_ == parent->right)
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
  if (cur_->left != nullptr)
  {
    cur_ = cur_->left;
    while (cur_->right != nullptr)
    {
      cur_ = cur_->right;
    }
  }
  else
  {
    node_t parent = cur_->parent;
    if (cur_ != nullptr)
    {
      while (parent != nullptr && cur_ == parent->left)
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
  