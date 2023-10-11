#ifndef AVLTREECONSTITERATOR
#define AVLTREECONSTITERATOR

#include <utility>
#include <memory>

#include "tree.hpp"
namespace hrushchev
{
  template< typename T >
  class Tree;

  template< typename Key, typename Value, typename Compare >
  class AVLTree;

  template< typename Key, typename Value, typename Compare >
  class AVLTreeIterator;

  template< typename Key, typename Value, typename Compare >
  class AVLTreeConstIterator
  {
    friend class AVLTree< Key, Value, Compare >;
    friend class AVLTreeIterator< Key, Value, Compare >;
    public:
      using data_t = std::pair< Key, Value >;
      AVLTreeConstIterator();
      explicit AVLTreeConstIterator(Tree< data_t >* rhs);
      AVLTreeConstIterator(const AVLTreeIterator< Key, Value, Compare >& rhs);
      AVLTreeConstIterator< Key, Value, Compare >& operator++();
      AVLTreeConstIterator< Key, Value, Compare > operator++(int);
      AVLTreeConstIterator< Key, Value, Compare >& operator--();
      AVLTreeConstIterator< Key, Value, Compare > operator--(int);
      const data_t& operator*();
      const data_t* operator->();
      bool operator==(const AVLTreeConstIterator< Key, Value, Compare >& rhs) const;
      bool operator!=(const AVLTreeConstIterator< Key, Value, Compare >& rhs) const;
      ~AVLTreeConstIterator() = default;
    private:
      Tree< data_t >* ptr_;
  };

  template< typename Key, typename Value, typename Compare >
  AVLTreeConstIterator< Key, Value, Compare >::AVLTreeConstIterator():
    ptr_(nullptr)
  {
  }

  template< typename Key, typename Value, typename Compare >
  AVLTreeConstIterator< Key, Value, Compare >::AVLTreeConstIterator(Tree< data_t >* rhs):
    ptr_(rhs)
  {
  }

  template< typename Key, typename Value, typename Compare >
  AVLTreeConstIterator< Key, Value, Compare >::AVLTreeConstIterator(const AVLTreeIterator< Key, Value, Compare >& rhs):
    ptr_(rhs.ptr_)
  {
  }

  template< typename Key, typename Value, typename Compare >
  AVLTreeConstIterator< Key, Value, Compare >& AVLTreeConstIterator< Key, Value, Compare >::operator++()
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
  AVLTreeConstIterator< Key, Value, Compare > AVLTreeConstIterator< Key, Value, Compare >::operator++(int)
  {
    AVLTreeConstIterator< Key, Value, Compare > temp(*this);
    ++(*this);
    return temp;
  }

  template< typename Key, typename Value, typename Compare >
  AVLTreeConstIterator< Key, Value, Compare >& AVLTreeConstIterator< Key, Value, Compare >::operator--()
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
  AVLTreeConstIterator< Key, Value, Compare > AVLTreeConstIterator< Key, Value, Compare >::operator--(int)
  {
    AVLTreeIterator< Key, Value, Compare > temp(*this);
    --(*this);
    return temp;
  }

  template< typename Key, typename Value, typename Compare >
  const typename AVLTreeConstIterator< Key, Value, Compare >::data_t& AVLTreeConstIterator< Key, Value, Compare >::operator*()
  {
    return ptr_->data_;
  }

  template< typename Key, typename Value, typename Compare >
  const typename AVLTreeConstIterator< Key, Value, Compare >::data_t* AVLTreeConstIterator< Key, Value, Compare >::operator->()
  {
    return std::addressof(ptr_->data_);
  }

  template< typename Key, typename Value, typename Compare >
  bool AVLTreeConstIterator< Key, Value, Compare >::operator==(const AVLTreeConstIterator< Key, Value, Compare >& rhs) const
  {
    return ptr_ == rhs.ptr_;
  }
  template< typename Key, typename Value, typename Compare >
  bool AVLTreeConstIterator< Key, Value, Compare >::operator!=(const AVLTreeConstIterator< Key, Value, Compare >& rhs) const
  {
    return ptr_ != rhs.ptr_;
  }
}

#endif
