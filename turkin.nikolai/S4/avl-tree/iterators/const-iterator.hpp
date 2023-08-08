#ifndef DIRECT_CONST_ITERATOR_HPP
#define DIRECT_CONST_ITERATOR_HPP

#include <utility>
#include <cassert>
#include "../tree-node.hpp"

namespace turkin
{
  template< typename K, typename V, typename C >
  class AVLtree;
  template< typename K, typename V, typename C >
  class Iterator;
  template< typename K, typename V, typename C >
  class ConstIterator
  {
    friend class AVLtree< K, V, C >;
    friend class Iterator< K, V, C >;
    using it = Iterator< K, V, C >;
    using cit = ConstIterator< K, V, C >;
    using tree_t = std::pair< K, V >;
    using node_t = TreeNode< tree_t > *;
    public:
      ConstIterator();
      explicit ConstIterator(node_t rhs);
      explicit ConstIterator(const it & rhs);
      cit & operator=(const cit & rhs) = default;
      ~ConstIterator() = default;
      cit & operator++();
      cit operator++(int);
      cit & operator--();
      cit operator--(int);
      const tree_t & operator*() const;
      const tree_t * operator->() const;
      bool operator==(const cit & rhs) const;
      bool operator!=(const cit & rhs) const;
    private:
      node_t cur_;
  };
}

template< typename K, typename V, typename C >
turkin::ConstIterator< K, V, C >::ConstIterator():
  cur_(nullptr)
{}

template< typename K, typename V, typename C >
turkin::ConstIterator< K, V, C >::ConstIterator(node_t rhs):
  cur_(rhs)
{}

template< typename K, typename V, typename C >
turkin::ConstIterator< K, V, C >::ConstIterator(const it & rhs):
  cur_(rhs.cur_)
{}

template< typename K, typename V, typename C >
turkin::ConstIterator< K, V, C > & turkin::ConstIterator< K, V, C >::operator++()
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
turkin::ConstIterator< K, V, C > turkin::ConstIterator< K, V, C >::operator++(int)
{
  assert(cur_ != nullptr);
  auto result(*this);
  ++(*this);
  return result;
}

template< typename K, typename V, typename C >
turkin::ConstIterator< K, V, C > & turkin::ConstIterator< K, V, C >::operator--()
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
turkin::ConstIterator< K, V, C > turkin::ConstIterator< K, V, C >::operator--(int)
{
  assert(cur_ != nullptr);
  auto result(*this);
  --(*this);
  return result;
}

template< typename K, typename V, typename C >
const std::pair< K, V > & turkin::ConstIterator< K, V, C >::operator*() const
{
  assert(cur_ != nullptr);
  return cur_->data;
}

template< typename K, typename V, typename C >
const std::pair< K, V > * turkin::ConstIterator< K, V, C >::operator->() const
{
  assert(cur_ != nullptr);
  return std::addressof(cur_->data);
}

template< typename K, typename V, typename C >
bool turkin::ConstIterator< K, V, C >::operator==(const ConstIterator< K, V, C > & rhs) const
{
  return cur_ == rhs.cur_;
}

template< typename K, typename V, typename C >
bool turkin::ConstIterator< K, V, C >::operator!=(const ConstIterator< K, V, C > & rhs) const
{
  return !(rhs == *this);
}

#endif
