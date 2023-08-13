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
    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;
    mapped_type &operator[](const key_type &);
    mapped_type &operator[](key_type &&);
    mapped_type &at(const key_type &);
    const mapped_type &at(const key_type &) const;
    iterator find(const key_type &);
    const_iterator find(const key_type &) const;
    iterator lower_bound(const key_type &);
    const_iterator lower_bound(const key_type &) const;
    iterator upper_bound(const key_type &);
    const_iterator upper_bound(const key_type &) const;
    std::pair< iterator, bool > insert(const value_type &);
    template< typename P >
    std::pair< iterator, bool > insert(P &&);
    template< typename InputIterator >
    void insert(InputIterator, InputIterator);
    bool empty() const noexcept;
    void clear() noexcept;
    key_compare key_comp() const;
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
  typename AVL< Key, Value, Compare >::iterator AVL< Key, Value, Compare >::begin() noexcept
  {
    tree *ptr = root_;
    while (ptr->left) {
      ptr = ptr->left;
    }
    return iterator(ptr);
  }

  template< typename Key, typename Value, typename Compare >
  typename AVL< Key, Value, Compare >::const_iterator AVL< Key, Value, Compare >::begin() const noexcept
  {
    return cbegin();
  }

  template< typename Key, typename Value, typename Compare >
  typename AVL< Key, Value, Compare >::const_iterator AVL< Key, Value, Compare >::cbegin() const noexcept
  {
    tree *ptr = root_;
    while (ptr->left) {
      ptr = ptr->left;
    }
    return const_iterator(ptr);
  }

  template< typename Key, typename Value, typename Compare >
  typename AVL< Key, Value, Compare >::iterator AVL< Key, Value, Compare >::end() noexcept
  {
    tree *ptr = root_;
    while (ptr->right) {
      ptr = ptr->right;
    }
    return iterator(ptr);
  }

  template< typename Key, typename Value, typename Compare >
  typename AVL< Key, Value, Compare >::const_iterator AVL< Key, Value, Compare >::end() const noexcept
  {
    return cend();
  }

  template< typename Key, typename Value, typename Compare >
  typename AVL< Key, Value, Compare >::const_iterator AVL< Key, Value, Compare >::cend() const noexcept
  {
    tree *ptr = root_;
    while (ptr->right) {
      ptr = ptr->right;
    }
    return const_iterator(ptr);
  }

  template< typename Key, typename Value, typename Compare >
  const Value &AVL< Key, Value, Compare >::at(const key_type &key) const
  {
    const_iterator cit = find(key);
    if (cit == cend()) {
      throw std::out_of_range("There is no such key");
    }
    return cit->second;
  }

  template< typename Key, typename Value, typename Compare >
  Value &AVL< Key, Value, Compare >::at(const key_type &key)
  {
    return const_cast< Value & >((static_cast< const this_t & >(*this)).at(key));
  }

  template< typename Key, typename Value, typename Compare >
  Value &AVL< Key, Value, Compare >::operator[](const key_type &key)
  {
    try {
      return at(key);
    } catch (const std::out_of_range &e) {
    }
    return (*((this->insert(std::make_pair(key, mapped_type()))).first));
  }

  template< typename Key, typename Value, typename Compare >
  Value &AVL< Key, Value, Compare >::operator[](key_type &&key)
  {
    return (*this)[key];
  }

  template< typename Key, typename Value, typename Compare >
  typename AVL< Key, Value, Compare >::iterator AVL< Key, Value, Compare >::find(const key_type &key)
  {
    const_iterator cit = static_cast< const this_t & >(*this).find(key);
    return iterator(cit.node_);
  }

  template< typename Key, typename Value, typename Compare >
  typename AVL< Key, Value, Compare >::const_iterator AVL< Key, Value, Compare >::find(const key_type &key) const
  {
    const_iterator cur = lower_bound();
    if (!comp_(key, cur->first)) {
      return cur;
    }
    return cend();
  }

  template< typename Key, typename Value, typename Compare >
  typename AVL< Key, Value, Compare >::iterator AVL< Key, Value, Compare >::lower_bound(const key_type &key)
  {
    const_iterator cit = static_cast< const this_t & >(*this).lower_bound(key);
    return iterator(cit.node_);
  }

  template< typename Key, typename Value, typename Compare >
  typename AVL< Key, Value, Compare >::const_iterator AVL< Key, Value, Compare >::lower_bound(const key_type &key) const
  {
    const_iterator cur = cbegin();
    while (comp_(cur->first, key)) {
      cur++;
    }
    return cur;
  }

  template< typename Key, typename Value, typename Compare >
  typename AVL< Key, Value, Compare >::iterator AVL< Key, Value, Compare >::upper_bound(const key_type &key)
  {
    const_iterator cit = static_cast< const this_t & >(*this).upper_bound(key);
    return iterator(cit.node_);
  }

  template< typename Key, typename Value, typename Compare >
  typename AVL< Key, Value, Compare >::const_iterator AVL< Key, Value, Compare >::upper_bound(const key_type &key) const  {
    const_iterator cur = lower_bound(key);
    if (!comp_(key, cur->first)) {
      cur++;
    }
    return cur;
  }

  template< typename Key, typename Value, typename Compare >
  std::pair< typename AVL< Key, Value, Compare >::iterator, bool > AVL< Key, Value, Compare >::insert(const value_type &value)  {
    auto *newTree = new tree{value, nullptr, nullptr, nullptr};
    if (empty()) {
      root_ = newTree;
      return {iterator(root_), true};
    } else {
      iterator cur = begin();
      while (comp_(cur->first, value.first)) {
        cur++;
      }
      if (!comp_(value.first, cur->first)) {
        return {end(), false};
      } else {
        iterator prev = cur;
        prev--;
        if (cur->left == nullptr) {
          cur->left = newTree;
          newTree->parent = cur;
        } else if (prev->right == nullptr) {
          prev->right = newTree;
          newTree->parent = prev;
        } else if (cur->parent == prev) {
          newTree->right = prev->right;
          prev->right = newTree;
          newTree->right->parent = newTree;
          newTree->parent = prev;
        } else if (cur->left = prev) {
          newTree->parent = prev->parent;
          prev->parent = newTree;
          newTree->left = prev;
          cur->left = newTree;
        }
        return {iterator(newTree), true};
      }
    }
  }

  template< typename Key, typename Value, typename Compare >
  template< typename P >
  std::pair< typename AVL< Key, Value, Compare >::iterator, bool > AVL< Key, Value, Compare >::insert(P &&value)
  {
    static_assert(std::is_constructible< value_type, P && >::value, "Can`t construct value type");
    const value_type temp(std::forward< P >(value));
    return insert(temp);
  }

  template< typename Key, typename Value, typename Compare >
  template< typename InputIterator >
  void AVL< Key, Value, Compare >::insert(InputIterator first, InputIterator last)
  {
    for (; first != last; first++) {
      insert(*first);
    }
  }

  template< typename Key, typename Value, typename Compare >
  bool AVL< Key, Value, Compare >::empty() const noexcept
  {
    return root_ == nullptr;
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

  template< typename Key, typename Value, typename Compare >
  typename AVL< Key, Value, Compare >::key_compare AVL< Key, Value, Compare >::key_comp() const
  {
    return comp_;
  }
}
#endif
