#ifndef ROTATABLE_BINARY_SEARCH_TREE_H
#define ROTATABLE_BINARY_SEARCH_TREE_H
#include <utility>
#include <functional>
#include "binary_search_tree.h"
namespace romanovich
{
  template< typename TKey, typename Value, typename Compare >
  class RedBlackTree;
  template< typename Key, typename Value, typename Compare = std::less< Key >>
  class RotatableBinarySearchTree
  {
    friend class RedBlackTree< Key, Value, Compare >;
  public:
    using data_t = std::pair< Key, Value >;
    using iterator = BidirectionalIterator< Key, Value, Compare >;
    using const_iterator = ConstBidirectionalIterator< Key, Value, Compare >;
    using reverse_iterator = std::reverse_iterator< iterator >;
    using const_reverse_iterator = std::reverse_iterator< const_iterator >;
    RotatableBinarySearchTree();
    RotatableBinarySearchTree(const RotatableBinarySearchTree &other) = default;
    RotatableBinarySearchTree(RotatableBinarySearchTree &&other) noexcept;
    explicit RotatableBinarySearchTree(const Compare &compare);
    ~RotatableBinarySearchTree() = default;
    RotatableBinarySearchTree &operator=(const RotatableBinarySearchTree &other);
    RotatableBinarySearchTree &operator=(RotatableBinarySearchTree &&other) noexcept;
    RotatableBinarySearchTree &operator=(std::initializer_list< data_t > initializerList);
    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;
    reverse_iterator rbegin() noexcept;
    const_reverse_iterator rbegin() const noexcept;
    const_reverse_iterator crbegin() const noexcept;
    iterator last() noexcept;
    const_iterator last() const noexcept;
    const_iterator clast() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;
    reverse_iterator rend() noexcept;
    const_reverse_iterator rend() const noexcept;
    const_reverse_iterator crend() const noexcept;
    bool empty() const noexcept;
    size_t size() const noexcept;
    void clear() noexcept;
    std::pair< iterator, bool > insert(const data_t &data);
    template< typename P >
    std::pair< iterator, bool > insert(P &&data);
    iterator insert(const_iterator pos, const data_t &data);
    template< typename P >
    iterator insert(const_iterator pos, P &&data);
    template< typename InputIt >
    void insert(InputIt first, InputIt last);
    void insert(std::initializer_list< data_t > initializerList);
    template< typename... Args >
    std::pair< iterator, bool > emplace(Args &&... args);
    Value &at(const Key &key);
    const Value &at(const Key &key) const;
    Value &operator[](const Key &key);
    Value &operator[](Key &&key);
    iterator erase(iterator pos);
    iterator erase(const_iterator pos);
    iterator erase(const_iterator first, const_iterator last);
    size_t erase(const Key &key);
    void swap(RotatableBinarySearchTree &other);
    size_t count(const Key &key) const;
    iterator find(const Key &key);
    const_iterator find(const Key &key) const;
    iterator lower_bound(const Key &key);
    const_iterator lower_bound(const Key &key) const;
    iterator upper_bound(const Key &key);
    const_iterator upper_bound(const Key &key) const;
    Compare data_comp() const;
    bool equal(const RotatableBinarySearchTree &rhs) const;
    void rotateLeftLeft(TreeNode< data_t > *node);
    void rotateRightRight(TreeNode< data_t > *node);
    void printNode(const TreeNode< data_t > *node, bool isLeft, const std::string &prefix) const;
    BinarySearchTree< Key, Value, Compare > bst_;
  private:
  };
  template< typename Key, typename Value, typename Compare >
  typename RotatableBinarySearchTree< Key, Value, Compare >::const_reverse_iterator
  RotatableBinarySearchTree< Key, Value, Compare >::crend() const noexcept
  {
    return bst_.crend();
  }
  template< typename Key, typename Value, typename Compare >
  typename RotatableBinarySearchTree< Key, Value, Compare >::const_reverse_iterator
  RotatableBinarySearchTree< Key, Value, Compare >::rend() const noexcept
  {
    return bst_.rend();
  }
  template< typename Key, typename Value, typename Compare >
  typename RotatableBinarySearchTree< Key, Value, Compare >::reverse_iterator
  RotatableBinarySearchTree< Key, Value, Compare >::rend() noexcept
  {
    return bst_.rend();
  }
  template< typename Key, typename Value, typename Compare >
  typename RotatableBinarySearchTree< Key, Value, Compare >::const_reverse_iterator
  RotatableBinarySearchTree< Key, Value, Compare >::crbegin() const noexcept
  {
    return bst_.crbegin();
  }
  template< typename Key, typename Value, typename Compare >
  typename RotatableBinarySearchTree< Key, Value, Compare >::const_reverse_iterator
  RotatableBinarySearchTree< Key, Value, Compare >::rbegin() const noexcept
  {
    return bst_.rbegin();
  }
  template< typename Key, typename Value, typename Compare >
  typename RotatableBinarySearchTree< Key, Value, Compare >::reverse_iterator
  RotatableBinarySearchTree< Key, Value, Compare >::rbegin() noexcept
  {
    return bst_.rbegin();
  }
  template< typename Key, typename Value, typename Compare >
  RotatableBinarySearchTree< Key, Value, Compare >::RotatableBinarySearchTree(const Compare &compare):
    bst_(compare)
  {
  }
  template< typename Key, typename Value, typename Compare >
  void RotatableBinarySearchTree< Key, Value, Compare >::printNode(const TreeNode< data_t > *node, bool isLeft,
                                                                   const std::string &prefix) const
  {
    std::cout << prefix;
    if (!node)
    {
      std::cout << "NULL\n";
      return;
    }
    if (isLeft)
    {
      std::cout << "├── ";
    }
    else if (node == bst_.root_)
    {
      std::cout << "─── ";
    }
    else
    {
      std::cout << "└── ";
    }
    std::string color = static_cast<bool>(node->color == Color::C_RED) ? "◼" : "◻";
    std::cout << node->data.second << " " << color << "\n";
    std::string newPrefix = prefix + (isLeft ? "│   " : "    ");
    printNode(node->left, true, newPrefix);
    printNode(node->right, false, newPrefix);
  }
  template< typename Key, typename Value, typename Compare >
  void RotatableBinarySearchTree< Key, Value, Compare >::rotateLeftLeft(TreeNode< data_t > *node)
  {
    auto rightChild = node->right;
    if (!rightChild)
    {
      return;
    }
    node->right = rightChild->left;
    if (rightChild->left != nullptr)
    {
      rightChild->left->parent = node;
    }
    rightChild->parent = node->parent;
    if (node->parent == nullptr)
    {
      bst_.root_ = rightChild;
    }
    else if (node == node->parent->left)
    {
      node->parent->left = rightChild;
    }
    else
    {
      node->parent->right = rightChild;
    }
    rightChild->left = node;
    node->parent = rightChild;
  }
  template< typename Key, typename Value, typename Compare >
  void RotatableBinarySearchTree< Key, Value, Compare >::rotateRightRight(TreeNode< data_t > *node)
  {
    auto leftChild = node->left;
    node->left = leftChild->right;
    if (leftChild->right != nullptr)
    {
      leftChild->right->parent = node;
    }
    leftChild->parent = node->parent;
    if (node->parent == nullptr)
    {
      bst_.root_ = leftChild;
    }
    else if (node == node->parent->right)
    {
      node->parent->right = leftChild;
    }
    else
    {
      node->parent->left = leftChild;
    }
    leftChild->right = node;
    node->parent = leftChild;
  }
  template< typename Key, typename Value, typename Compare >
  Compare RotatableBinarySearchTree< Key, Value, Compare >::data_comp() const
  {
    return bst_.value_comp();
  }
  template< typename Key, typename Value, typename Compare >
  ConstBidirectionalIterator< Key, Value, Compare >
  RotatableBinarySearchTree< Key, Value, Compare >::upper_bound(const Key &key) const
  {
    return bst_.upper_bound(key);
  }
  template< typename Key, typename Value, typename Compare >
  BidirectionalIterator< Key, Value, Compare >
  RotatableBinarySearchTree< Key, Value, Compare >::upper_bound(const Key &key)
  {
    return bst_.upper_bound(key);
  }
  template< typename Key, typename Value, typename Compare >
  ConstBidirectionalIterator< Key, Value, Compare >
  RotatableBinarySearchTree< Key, Value, Compare >::lower_bound(const Key &key) const
  {
    return bst_.lower_bound(key);
  }
  template< typename Key, typename Value, typename Compare >
  BidirectionalIterator< Key, Value, Compare >
  RotatableBinarySearchTree< Key, Value, Compare >::lower_bound(const Key &key)
  {
    return bst_.lower_bound(key);
  }
  template< typename Key, typename Value, typename Compare >
  ConstBidirectionalIterator< Key, Value, Compare >
  RotatableBinarySearchTree< Key, Value, Compare >::find(const Key &key) const
  {
    return bst_.find(key);
  }
  template< typename Key, typename Value, typename Compare >
  BidirectionalIterator< Key, Value, Compare >
  RotatableBinarySearchTree< Key, Value, Compare >::find(const Key &key)
  {
    return bst_.find(key);
  }
  template< typename Key, typename Value, typename Compare >
  size_t RotatableBinarySearchTree< Key, Value, Compare >::count(const Key &key) const
  {
    return bst_.count(key);
  }
  template< typename Key, typename Value, typename Compare >
  void RotatableBinarySearchTree< Key, Value, Compare >::swap(RotatableBinarySearchTree &other)
  {
    bst_.swap(other.bst_);
  }
  template< typename Key, typename Value, typename Compare >
  size_t RotatableBinarySearchTree< Key, Value, Compare >::erase(const Key &key)
  {
    return bst_.erase(key);
  }
  template< typename Key, typename Value, typename Compare >
  BidirectionalIterator< Key, Value, Compare >
  RotatableBinarySearchTree< Key, Value, Compare >::erase(RotatableBinarySearchTree::const_iterator first,
                                                          RotatableBinarySearchTree::const_iterator last)
  {
    return bst_.erase(first, last);
  }
  template< typename Key, typename Value, typename Compare >
  BidirectionalIterator< Key, Value, Compare >
  RotatableBinarySearchTree< Key, Value, Compare >::erase(RotatableBinarySearchTree::const_iterator pos)
  {
    return bst_.erase(pos);
  }
  template< typename Key, typename Value, typename Compare >
  BidirectionalIterator< Key, Value, Compare >
  RotatableBinarySearchTree< Key, Value, Compare >::erase(RotatableBinarySearchTree::iterator pos)
  {
    return bst_.erase(pos);
  }
  template< typename Key, typename Value, typename Compare >
  Value &
  RotatableBinarySearchTree< Key, Value, Compare >::operator[](Key &&key)
  {
    return bst_[std::move(key)];
  }
  template< typename Key, typename Value, typename Compare >
  Value &
  RotatableBinarySearchTree< Key, Value, Compare >::operator[](const Key &key)
  {
    return bst_[key];
  }
  template< typename Key, typename Value, typename Compare >
  const Value &
  RotatableBinarySearchTree< Key, Value, Compare >::at(const Key &key) const
  {
    return bst_.at(key);
  }
  template< typename Key, typename Value, typename Compare >
  Value &
  RotatableBinarySearchTree< Key, Value, Compare >::at(const Key &key)
  {
    return bst_.at(key);
  }
  template< typename Key, typename Value, typename Compare >
  template< typename... Args >
  std::pair< BidirectionalIterator< Key, Value, Compare >, bool >
  RotatableBinarySearchTree< Key, Value, Compare >::emplace(Args &&... args)
  {
    return bst_.emplace(std::forward< Args >(args)...);
  }
  template< typename Key, typename Value, typename Compare >
  void RotatableBinarySearchTree< Key, Value, Compare >::insert(std::initializer_list< data_t > initializerList)
  {
    bst_.insert(initializerList);
  }
  template< typename Key, typename Value, typename Compare >
  template< typename InputIt >
  void RotatableBinarySearchTree< Key, Value, Compare >::insert(InputIt first, InputIt last)
  {
    bst_.insert(first, last);
  }
  template< typename Key, typename Value, typename Compare >
  template< typename P >
  BidirectionalIterator< Key, Value, Compare >
  RotatableBinarySearchTree< Key, Value, Compare >::insert(RotatableBinarySearchTree::const_iterator pos, P &&data)
  {
    return bst_.insert(pos, data);
  }
  template< typename Key, typename Value, typename Compare >
  BidirectionalIterator< Key, Value, Compare >
  RotatableBinarySearchTree< Key, Value, Compare >::insert(RotatableBinarySearchTree::const_iterator pos,
                                                           const data_t &data)
  {
    return bst_.insert(pos, data);
  }
  template< typename Key, typename Value, typename Compare >
  template< typename P >
  std::pair< BidirectionalIterator< Key, Value, Compare >, bool >
  RotatableBinarySearchTree< Key, Value, Compare >::insert(P &&data)
  {
    return bst_.insert(data);
  }
  template< typename Key, typename Value, typename Compare >
  std::pair< BidirectionalIterator< Key, Value, Compare >, bool >
  RotatableBinarySearchTree< Key, Value, Compare >::insert(const data_t &data)
  {
    return bst_.insert(data);
  }
  template< typename Key, typename Value, typename Compare >
  void RotatableBinarySearchTree< Key, Value, Compare >::clear() noexcept
  {
    bst_.clear();
  }
  template< typename Key, typename Value, typename Compare >
  size_t RotatableBinarySearchTree< Key, Value, Compare >::size() const noexcept
  {
    return bst_.size();
  }
  template< typename Key, typename Value, typename Compare >
  bool RotatableBinarySearchTree< Key, Value, Compare >::empty() const noexcept
  {
    return bst_.empty();
  }
  template< typename Key, typename Value, typename Compare >
  ConstBidirectionalIterator< Key, Value, Compare >
  RotatableBinarySearchTree< Key, Value, Compare >::cend() const noexcept
  {
    return bst_.cend();
  }
  template< typename Key, typename Value, typename Compare >
  ConstBidirectionalIterator< Key, Value, Compare >
  RotatableBinarySearchTree< Key, Value, Compare >::end() const noexcept
  {
    return cend();
  }
  template< typename Key, typename Value, typename Compare >
  BidirectionalIterator< Key, Value, Compare > RotatableBinarySearchTree< Key, Value, Compare >::end() noexcept
  {
    return bst_.end();
  }
  template< typename Key, typename Value, typename Compare >
  ConstBidirectionalIterator< Key, Value, Compare >
  RotatableBinarySearchTree< Key, Value, Compare >::clast() const noexcept
  {
    return bst_.clast();
  }
  template< typename Key, typename Value, typename Compare >
  ConstBidirectionalIterator< Key, Value, Compare >
  RotatableBinarySearchTree< Key, Value, Compare >::last() const noexcept
  {
    return clast();
  }
  template< typename Key, typename Value, typename Compare >
  BidirectionalIterator< Key, Value, Compare > RotatableBinarySearchTree< Key, Value, Compare >::last() noexcept
  {
    return bst_.last();
  }
  template< typename Key, typename Value, typename Compare >
  ConstBidirectionalIterator< Key, Value, Compare >
  RotatableBinarySearchTree< Key, Value, Compare >::cbegin() const noexcept
  {
    return bst_.cbegin();
  }
  template< typename Key, typename Value, typename Compare >
  ConstBidirectionalIterator< Key, Value, Compare >
  RotatableBinarySearchTree< Key, Value, Compare >::begin() const noexcept
  {
    return cbegin();
  }
  template< typename Key, typename Value, typename Compare >
  BidirectionalIterator< Key, Value, Compare > RotatableBinarySearchTree< Key, Value, Compare >::begin() noexcept
  {
    return bst_.begin();
  }
  template< typename Key, typename Value, typename Compare >
  RotatableBinarySearchTree< Key, Value, Compare > &
  RotatableBinarySearchTree< Key, Value, Compare >::operator=(std::initializer_list< data_t > initializerList)
  {
    bst_ = initializerList;
    return *this;
  }
  template< typename Key, typename Value, typename Compare >
  RotatableBinarySearchTree< Key, Value, Compare > &
  RotatableBinarySearchTree< Key, Value, Compare >::operator=(RotatableBinarySearchTree &&other) noexcept
  {
    bst_ = std::move(other.data);
    return *this;
  }
  template< typename Key, typename Value, typename Compare >
  RotatableBinarySearchTree< Key, Value, Compare > &
  RotatableBinarySearchTree< Key, Value, Compare >::operator=(const RotatableBinarySearchTree &other)
  {
    bst_ = other.bst_;
    return *this;
  }
  template< typename Key, typename Value, typename Compare >
  bool RotatableBinarySearchTree< Key, Value, Compare >::equal(const RotatableBinarySearchTree &rhs) const
  {
    return bst_ == rhs.bst_;
  }
  template< typename Key, typename Value, typename Compare >
  RotatableBinarySearchTree< Key, Value, Compare >::RotatableBinarySearchTree(
    RotatableBinarySearchTree &&other) noexcept:
    bst_(std::move(other.bst_))
  {
  }
  template< typename Key, typename Value, typename Compare >
  RotatableBinarySearchTree< Key, Value, Compare >::RotatableBinarySearchTree():
    bst_()
  {
  }
}
#endif
