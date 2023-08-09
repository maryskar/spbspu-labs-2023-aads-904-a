#ifndef AVL_H
#define AVL_H
#include <utility>
#include <functional>
#include "tree.h"
#include "AVLIterator.h"
#include "constAVLIterator.h"

namespace fesenko
{

  template< typename Key, typename Value, typename Compare >
  class AVLIterator;

  template< typename Key, typename Value, typename Compare >
  class ConstAVLIterator;

  template< typename Key, typename Value, typename Compare >
  class AVL
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
    using const_iterator = ConstAVLIterator< Key, Value, Compare >;
    using this_t = AVL< Key, Value, Compare >;
    AVL();
    AVL(const this_t &);
    AVL(this_t &&);
    ~AVL();
    this_t &operator=(const this_t &);
    this_t &operator=(this_t &&);
    void clear() noexcept;
   private:
    tree *root_;
    Compare comp_;
    void deleteNode(tree *) noexcept;
    tree *copy(const tree *);
  };

  template< typename Key, typename Value, typename Compare >
  AVL< Key, Value, Compare >::AVL():
    root_(nullptr),
    comp_()
  {}

  template< typename Key, typename Value, typename Compare >
  AVL< Key, Value, Compare >::AVL(const this_t &other):
    root_(copy(other.root_)),
    comp_(other.comp)
  {}

  template< typename Key, typename Value, typename Compare >
  AVL< Key, Value, Compare >::AVL(this_t &&other):
    root_(std::move(other.root_)),
    comp_(std::move(other.comp_))
  {}

  template< typename Key, typename Value, typename Compare >
  AVL< Key, Value, Compare > &AVL< Key, Value, Compare >::operator=(const this_t &other)
  {
    root_ = copy(other.root_);
    return *this;
  }

  template< typename Key, typename Value, typename Compare >
  AVL< Key, Value, Compare > &AVL< Key, Value, Compare >::operator=(this_t &&other)
  {
    if (std::addressof(other) != this) {
      root_ = std::move(other.root_);
      comp_ = std::move(other.comp_);
    }
    return *this;
  }

  template< typename Key, typename Value, typename Compare >
  AVL< Key, Value, Compare >::~AVL()
  {
    clear();
  }

  template< typename Key, typename Value, typename Compare >
  void AVL< Key, Value, Compare >::clear() noexcept
  {
    if (!root_) {
      return;
    }
    deleteNode(root_);
  }

  template< typename Key, typename Value, typename Compare >
  void AVL< Key, Value, Compare >::deleteNode(tree *node) noexcept
  {
    if (node->left) {
      deleteNode(node->left);
    }
    if (node->right) {
      deleteNode(node->right);
    }
    delete node;
  }

  template< typename Key, typename Value, typename Compare >
  typename AVL< Key, Value, Compare >::tree *AVL< Key, Value, Compare >::copy(const tree *node)
  {
    tree *newNode = node;
    if (node->left) {
      newNode->left = copy(node->left);
      newNode->left->parent = newNode;
    }
    if (node->right) {
      newNode->right = copy(node->right);
      newNode->right->parent = newNode;
    }
    return newNode;
  }
}
#endif
