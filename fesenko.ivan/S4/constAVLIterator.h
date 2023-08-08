#ifndef CONSTAVLITERATOR
#define CONSTAVLITERATOR
#include <functional>
#include "AVL.h"
#include "AVLIterator.h"

namespace fesenko
{
  template< typename Key, typename Value, typename Compare >
  class AVLIterator;

  template< typename Key, typename Value, typename Compare >
  class ConstAVLIterator
  {
   public:
    using key_type = Key;
    using mapped_type = Value;
    using value_type = std::pair< const key_type, mapped_type >;
    using key_compare = Compare;
    using reference = value_type &;
    using const_reference = const value_type &;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using tree = Tree< value_type >;
    using iterator = AVLIterator< Key, Value, Compare >;
    using this_t = ConstAVLIterator< Key, Value, Compare >;
    ConstAVLIterator();
    ConstAVLIterator(const this_t &) = default;
    explicit ConstAVLIterator(tree *);
    explicit ConstAVLIterator(const iterator &);
    ~ConstAVLIterator() = default;
    this_t &operator=(const this_t &) = default;
    this_t &operator++();
    this_t operator++(int);
    this_t &operator--();
    this_t operator--(int);
    const value_type &operator*() const;
    const value_type *operator->() const;
    bool operator!=(const this_t &) const;
    bool operator==(const this_t &) const;
   private:
    tree *fake_;
    tree *node_;
    Compare comp_;
  };

  template< typename Key, typename Value, typename Compare >
  ConstAVLIterator< Key, Value, Compare >::ConstAVLIterator():
    fake_(nullptr),
    node_(nullptr),
    comp_()
  {}

  template< typename Key, typename Value, typename Compare >
  ConstAVLIterator< Key, Value, Compare >::ConstAVLIterator(tree *rhs):
    node_(rhs),
    comp_()
  {
    auto temp = rhs->parent;
    while (temp->left || temp->right) {
      temp = temp->parent;
    }
    fake_ = temp;
  }

  template< typename Key, typename Value, typename Compare >
  ConstAVLIterator< Key, Value, Compare >::ConstAVLIterator(const iterator &other):
    fake_(other.fake_),
    node_(other.node_),
    comp_(other.comp_)
  {}

  template< typename Key, typename Value, typename Compare >
  ConstAVLIterator< Key, Value, Compare> &ConstAVLIterator< Key, Value, Compare >::operator++()
  {
    assert(node_ != nullptr);
    if (node_->right) {
      node_ = node_->right;
      while (node_->left) {
        node_ = node_->left;
      }
    } else {
      const tree *prev;
      do {
        prev = node_;
        node_ = node_->parent;
      } while (node_ && prev == node_->right);
    }
    return *this;
  }

  template< typename Key, typename Value, typename Compare >
  ConstAVLIterator< Key, Value, Compare > ConstAVLIterator< Key, Value, Compare >::operator++(int)
  {
    assert(node_ != nullptr);
    auto res(*this);
    ++(*this);
    return res;
  }

  template< typename Key, typename Value, typename Compare >
  ConstAVLIterator< Key, Value, Compare> &ConstAVLIterator< Key, Value, Compare >::operator--()
  {
    assert(node_ != nullptr);
    if (node_->left) {
      node_ = node_->left;
      while (node_->right) {
        node_ = node_->right;
      }
    } else {
      const tree *prev;
      do {
        prev = node_;
        node_ = node_->parent;
      } while (node_ && prev == node_->left);
    }
    return *this;
  }

  template< typename Key, typename Value, typename Compare >
  ConstAVLIterator< Key, Value, Compare > ConstAVLIterator< Key, Value, Compare >::operator--(int)
  {
    assert(node_ != nullptr);
    auto res(*this);
    --(*this);
    return res;
  }

  template< typename Key, typename Value, typename Compare >
  const typename ConstAVLIterator< Key, Value, Compare >::value_type &ConstAVLIterator< Key, Value, Compare >::operator*() const
  {
    assert(node_ != nullptr);
    return node_->data;
  }

  template< typename Key, typename Value, typename Compare >
  const typename ConstAVLIterator< Key, Value, Compare >::value_type *ConstAVLIterator< Key, Value, Compare >::operator->() const
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data);
  }
}
#endif
