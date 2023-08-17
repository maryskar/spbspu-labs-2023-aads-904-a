#ifndef AVLTREEITERATOR_HPP
#define AVLTREEITERATOR_HPP

#include <utility>

#include "tree.hpp"

template< typename T  >
class Tree;

template< typename Key, typename Value, typename Compare >
class AVLTree;

template< typename Key, typename Value, typename Compare >
class AVLTreeIterator
{
  friend class AVLTree< Key, Value, Compare >;
  public:
    using data_t = std::pair< Key, Value >;
    AVLTreeIterator();
    explicit AVLTreeIterator(Tree< data_t >* rhs);
    AVLTreeIterator< Key, Value, Compare >& operator++();
    Value& operator*();
    ~AVLTreeIterator() = default;
  private:
    Tree< data_t >* ptr_;
};

template< typename Key, typename Value, typename Compare >
AVLTreeIterator< Key, Value, Compare >::AVLTreeIterator():
  ptr_(nullptr)
{
}

template< typename Key, typename Value, typename Compare >
AVLTreeIterator< Key, Value, Compare >::AVLTreeIterator(Tree< data_t >* rhs):
  ptr_(rhs)
{
}

template< typename Key, typename Value, typename Compare >
AVLTreeIterator< Key, Value, Compare >& AVLTreeIterator< Key, Value, Compare >::operator++()
{
  if (ptr_->right_)
  {
    ptr_ = getMin(ptr_->right_);
  }
  else
  {
    Tree< data_t >* parent = ptr_->head_;
    while (parent && (ptr_ == parent->right_))
    {
      ptr_ = parent;
      parent = parent->head_;
    }
    ptr_ = parent;
  }
  return *this;
}

template< typename Key, typename Value, typename Compare >
Value& AVLTreeIterator< Key, Value, Compare >::operator*()
{
  return ptr_->data_.second;
}

#endif
