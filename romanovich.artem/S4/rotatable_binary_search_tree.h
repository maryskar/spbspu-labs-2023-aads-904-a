#ifndef ROTATABLE_BINARY_SEARCH_TREE_H
#define ROTATABLE_BINARY_SEARCH_TREE_H
#include <utility>
#include <functional>
#include "tree_node.h"
#include "binary_search_tree.h"
namespace romanovich
{
  template< typename Key, typename Value, typename Compare = std::less< Key >>
  class RotatableBinarySearchTree
  {
  public:
    using data_type = std::pair< Key, Value >;
    using r_bst_t = RotatableBinarySearchTree< Key, Value, Compare >;
    using tree_t = TreeNode< data_type >;
    using iterator = BidirectionalIterator< Key, Value, Compare >;
    using const_iterator = ConstBidirectionalIterator< Key, Value, Compare >;
    RotatableBinarySearchTree();
    RotatableBinarySearchTree(const RotatableBinarySearchTree &other) = default;
    RotatableBinarySearchTree(RotatableBinarySearchTree &&other) noexcept;
    // explicit RotatableBinarySearchTree(const Compare &comp);
    /*  template< typename InputIt >
      RotatableBinarySearchTree(InputIt first, InputIt last, const Compare &comp = Compare());
      RotatableBinarySearchTree(std::initializer_list< data_type > init, const Compare &comp = Compare());*/
    ~RotatableBinarySearchTree() = default;
    RotatableBinarySearchTree &operator=(const RotatableBinarySearchTree &other);
    RotatableBinarySearchTree &operator=(RotatableBinarySearchTree &&other) noexcept;
    RotatableBinarySearchTree &operator=(std::initializer_list< data_type > initializerList);
    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;
    iterator last() noexcept;
    const_iterator last() const noexcept;
    const_iterator clast() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;
    bool empty() const noexcept;
    size_t size() const noexcept;
    void clear() noexcept;
    std::pair< iterator, bool > insert(const data_type &data);
    template< typename P >
    std::pair< iterator, bool > insert(P &&data);
    iterator insert(const_iterator pos, const data_type &data);
    template< typename P >
    iterator insert(const_iterator pos, P &&data);
    template< typename InputIt >
    void insert(InputIt first, InputIt last);
    void insert(std::initializer_list< data_type > initializerList);
    template< typename... Args >
    std::pair< iterator, bool > emplace(Args &&... args);
    data_type &at(const data_type &data);
    const data_type &at(const data_type &data) const;
    data_type &operator[](const data_type &data);
    data_type &operator[](data_type &&data);
    iterator erase(iterator pos);
    iterator erase(const_iterator pos);
    iterator erase(const_iterator first, const_iterator last);
    size_t erase(const data_type &data);
    void swap(RotatableBinarySearchTree &other);
    size_t count(const data_type &data) const;
    iterator find(const data_type &data);
    const_iterator find(const data_type &data) const;
    std::pair< iterator, iterator > equal_range(const data_type &data);
    std::pair< const_iterator, const_iterator > equal_range(const data_type &data) const;
    iterator lower_bound(const data_type &data);
    const_iterator lower_bound(const data_type &data) const;
    iterator upper_bound(const data_type &data);
    const_iterator upper_bound(const data_type &data) const;
    Compare data_comp() const;
    bool isEqual(const RotatableBinarySearchTree &rhs) const;
    void rotateLeftLeft(TreeNode< data_type > *node);
    void rotateRightRight(TreeNode< data_type > *node);
    void printNode(const TreeNode< data_type > *node, bool isLeft, const std::string &prefix) const
    {
      std::cout << prefix;
      if (node == nullptr)
      {
        std::cout << "nullptr\n";
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
      std::cout << node->data.second << "\n";
      std::string newPrefix = prefix + (isLeft ? "│   " : "    ");
      printNode(node->left, true, newPrefix);
      printNode(node->right, false, newPrefix);
    }
  private:
    BinarySearchTree< Key, Value, Compare > bst_;
  public:
    const BinarySearchTree< Key, Value, Compare > &getBst() const
    {
      return bst_;
    }
  };
  template< typename Key, typename Value, typename Compare >
  void RotatableBinarySearchTree< Key, Value, Compare >::rotateLeftLeft(TreeNode< data_type > *node)
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
  void RotatableBinarySearchTree< Key, Value, Compare >::rotateRightRight(TreeNode< data_type > *node)
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
  RotatableBinarySearchTree< Key, Value, Compare >::upper_bound(const RotatableBinarySearchTree::data_type &data) const
  {
    return bst_.upper_bound(data);
  }
  template< typename Key, typename Value, typename Compare >
  BidirectionalIterator< Key, Value, Compare >
  RotatableBinarySearchTree< Key, Value, Compare >::upper_bound(const RotatableBinarySearchTree::data_type &data)
  {
    return bst_.upper_bound(data);
  }
  template< typename Key, typename Value, typename Compare >
  ConstBidirectionalIterator< Key, Value, Compare >
  RotatableBinarySearchTree< Key, Value, Compare >::lower_bound(const RotatableBinarySearchTree::data_type &data) const
  {
    return bst_.lower_bound(data);
  }
  template< typename Key, typename Value, typename Compare >
  BidirectionalIterator< Key, Value, Compare >
  RotatableBinarySearchTree< Key, Value, Compare >::lower_bound(const RotatableBinarySearchTree::data_type &data)
  {
    return bst_.lower_bound(data);
  }
  template< typename Key, typename Value, typename Compare >
  std::pair< ConstBidirectionalIterator< Key, Value, Compare >, ConstBidirectionalIterator< Key, Value, Compare > >
  RotatableBinarySearchTree< Key, Value, Compare >::equal_range(const RotatableBinarySearchTree::data_type &data) const
  {
    return data.equal_range(data);
  }
  template< typename Key, typename Value, typename Compare >
  std::pair< BidirectionalIterator< Key, Value, Compare >, BidirectionalIterator< Key, Value, Compare > >
  RotatableBinarySearchTree< Key, Value, Compare >::equal_range(const RotatableBinarySearchTree::data_type &data)
  {
    return bst_.equal_range(data);
  }
  template< typename Key, typename Value, typename Compare >
  ConstBidirectionalIterator< Key, Value, Compare >
  RotatableBinarySearchTree< Key, Value, Compare >::find(const RotatableBinarySearchTree::data_type &data) const
  {
    return bst_.find(data);
  }
  template< typename Key, typename Value, typename Compare >
  BidirectionalIterator< Key, Value, Compare >
  RotatableBinarySearchTree< Key, Value, Compare >::find(const RotatableBinarySearchTree::data_type &data)
  {
    return bst_.find(data);
  }
  template< typename Key, typename Value, typename Compare >
  size_t RotatableBinarySearchTree< Key, Value, Compare >::count(const RotatableBinarySearchTree::data_type &data) const
  {
    return bst_.count(data);
  }
  template< typename Key, typename Value, typename Compare >
  void RotatableBinarySearchTree< Key, Value, Compare >::swap(RotatableBinarySearchTree &other)
  {
    bst_.swap(other.bst_);
  }
  template< typename Key, typename Value, typename Compare >
  size_t RotatableBinarySearchTree< Key, Value, Compare >::erase(const RotatableBinarySearchTree::data_type &data)
  {
    return bst_.erase(data);
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
  std::pair< Key, Value > &
  RotatableBinarySearchTree< Key, Value, Compare >::operator[](RotatableBinarySearchTree::data_type &&data)
  {
    return bst_[std::move(data)];
  }
  template< typename Key, typename Value, typename Compare >
  std::pair< Key, Value > &
  RotatableBinarySearchTree< Key, Value, Compare >::operator[](const RotatableBinarySearchTree::data_type &data)
  {
    return bst_[data];
  }
  template< typename Key, typename Value, typename Compare >
  const std::pair< Key, Value > &
  RotatableBinarySearchTree< Key, Value, Compare >::at(const RotatableBinarySearchTree::data_type &data) const
  {
    return bst_.at(data);
  }
  template< typename Key, typename Value, typename Compare >
  std::pair< Key, Value > &
  RotatableBinarySearchTree< Key, Value, Compare >::at(const RotatableBinarySearchTree::data_type &data)
  {
    return bst_.at(data);
  }
  template< typename Key, typename Value, typename Compare >
  template< typename... Args >
  std::pair< BidirectionalIterator< Key, Value, Compare >, bool >
  RotatableBinarySearchTree< Key, Value, Compare >::emplace(Args &&... args)
  {
    return bst_.emplace(std::forward< Args >(args)...);
  }
  template< typename Key, typename Value, typename Compare >
  void RotatableBinarySearchTree< Key, Value, Compare >::insert(std::initializer_list< data_type > initializerList)
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
                                                           const RotatableBinarySearchTree::data_type &data)
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
  RotatableBinarySearchTree< Key, Value, Compare >::insert(const RotatableBinarySearchTree::data_type &data)
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
  RotatableBinarySearchTree< Key, Value, Compare >::operator=(std::initializer_list< data_type > initializerList)
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
  bool RotatableBinarySearchTree< Key, Value, Compare >::isEqual(const RotatableBinarySearchTree &rhs) const
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
