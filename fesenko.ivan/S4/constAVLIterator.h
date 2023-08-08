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
}
#endif
