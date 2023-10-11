#ifndef AVLTREEITERATOR_HPP
#define AVLTREEITERATOR_HPP

#include <utility>
#include <memory>

#include "tree.hpp"
namespace hrushchev
{
  template< typename T  >
  class Tree;

  template< typename Key, typename Value, typename Compare >
  class AVLTree;

  template< typename Key, typename Value, typename Compare >
  class AVLTreeConstIterator;

  template< typename Key, typename Value, typename Compare >
  class AVLTreeIterator
  {
    friend class AVLTree< Key, Value, Compare >;
    friend class AVLTreeConstIterator< Key, Value, Compare >;
    public:
      using data_t = std::pair< Key, Value >;
      AVLTreeIterator();
      explicit AVLTreeIterator(Tree< data_t >* rhs);
      AVLTreeIterator(const AVLTreeConstIterator< Key, Value, Compare >& rhs);
      AVLTreeIterator< Key, Value, Compare >& operator++();
      AVLTreeIterator< Key, Value, Compare > operator++(int);
      AVLTreeIterator< Key, Value, Compare >& operator--();
      AVLTreeIterator< Key, Value, Compare > operator--(int);
      data_t& operator*();
      data_t* operator->();
      bool operator==(const AVLTreeIterator< Key, Value, Compare >& rhs) const;
      bool operator!=(const AVLTreeIterator< Key, Value, Compare >& rhs) const;
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
  AVLTreeIterator< Key, Value, Compare >::AVLTreeIterator(const AVLTreeConstIterator< Key, Value, Compare >& rhs):
    ptr_(rhs.ptr_)
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
  AVLTreeIterator< Key, Value, Compare > AVLTreeIterator< Key, Value, Compare >::operator++(int)
  {
    AVLTreeIterator< Key, Value, Compare > temp(*this);
    ++(*this);
    return temp;
  }

  template< typename Key, typename Value, typename Compare >
  AVLTreeIterator< Key, Value, Compare >& AVLTreeIterator< Key, Value, Compare >::operator--()
  {
    if (ptr_->left_)
    {
      ptr_ = getMax(ptr_->left_);
    }
    else
    {
      Tree< data_t >* parent = ptr_->head_;
      while (parent && (ptr_ == parent->left_))
      {
        ptr_ = parent;
        parent = parent->head_;
      }
      ptr_ = parent;
    }
    return *this;
  }

  template< typename Key, typename Value, typename Compare >
  AVLTreeIterator< Key, Value, Compare > AVLTreeIterator< Key, Value, Compare >::operator--(int)
  {
    AVLTreeIterator< Key, Value, Compare > temp(*this);
    --(*this);
    return temp;
  }

  template< typename Key, typename Value, typename Compare >
  typename AVLTreeIterator< Key, Value, Compare >::data_t& AVLTreeIterator< Key, Value, Compare >::operator*()
  {
    return ptr_->data_;
  }

  template< typename Key, typename Value, typename Compare >
  typename AVLTreeIterator< Key, Value, Compare >::data_t* AVLTreeIterator< Key, Value, Compare >::operator->()
  {
    return std::addressof(ptr_->data_);
  }

  template< typename Key, typename Value, typename Compare >
  bool AVLTreeIterator< Key, Value, Compare >::operator==(const AVLTreeIterator< Key, Value, Compare >& rhs) const
  {
    return ptr_ == rhs.ptr_;
  }
  template< typename Key, typename Value, typename Compare >
  bool AVLTreeIterator< Key, Value, Compare >::operator!=(const AVLTreeIterator< Key, Value, Compare >& rhs) const
  {
    return ptr_ != rhs.ptr_;
  }
}

#endif
