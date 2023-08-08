#ifndef AVLITERATOR
#define AVLITERATOR
#include "AVL.h"
#include <functional>

namespace fesenko
{
  template< typename Key, typename Value, typename Compare >
  class AVL;

  template< typename Key, typename Value, typename Compare = std::less< Key > >
  class AVLIterator
  {
    friend class AVL< Key, Value, Compare >;
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
    using this_t = AVLIterator< Key, Value, Compare >;
    AVLIterator();
    AVLIterator(const this_t &) = default;
    ~AVLIterator() = default;
    this_t &operator=(const this_t &) = default;
    this_t &operator++();
    this_t operator++(int);
    this_t &operator--();
    this_t operator--(int);
    value_type &operator*();
    const value_type &operator*() const;
    value_type *operator->();
    const value_type *operator->() const;
    bool operator!=(const this_t &) const;
    bool operator==(const this_t &) const;
   private:
    explicit AVLIterator(tree *);
    tree *fake_;
    tree *node_;
    Compare comp_;
  };

  template< typename Key, typename Value, typename Compare >
  AVLIterator< Key, Value, Compare >::AVLIterator():
    fake_(nullptr),
    node_(nullptr),
    comp_()
  {}

  template< typename Key, typename Value, typename Compare >
  AVLIterator< Key, Value, Compare >::AVLIterator(tree *rhs):
    node_(nullptr),
    comp_()
  {
    auto temp = rhs->parent;
    while (temp->left || temp->right) {
      temp = temp->parent;
    }
    fake_ = temp;
  }

  template< typename Key, typename Value, typename Compare >
  AVLIterator< Key, Value, Compare> &AVLIterator< Key, Value, Compare >::operator++()
  {
    assert(node_ != nullptr);
    if (node_->right) {
      node_ = node_->right;
      while (node_->left) {
        node_ = node_->left;
      }
    } else {
      tree *prev;
      do {
        prev = node_;
        node_ = node_->parent;
      } while (node_ && prev == node_->right);
    }
    return *this;
  }

  template< typename Key, typename Value, typename Compare >
  AVLIterator< Key, Value, Compare > AVLIterator< Key, Value, Compare >::operator++(int)
  {
    assert(node_ != nullptr);
    auto res(*this);
    ++(*this);
    return res;
  }

  template< typename Key, typename Value, typename Compare >
  bool AVLIterator< Key, Value, Compare >::operator==(const this_t &rhs) const
  {
    return node_ == rhs.node_;
  }

  template< typename Key, typename Value, typename Compare >
  bool AVLIterator< Key, Value, Compare >::operator!=(const this_t &rhs) const
  {
    return !(rhs == *this);
  }
}
#endif
