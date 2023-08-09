#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H
#include <functional>
#include <stdexcept>
#include <iostream>
#include <cstddef>
#include "const_bidirectional_iterator.h"
namespace romanovich
{
  template< typename Key, typename Value, typename Compare >
  class RotatableBinarySearchTree;
  template< typename Key, typename Value, typename Compare >
  class RedBlackTree;
  template< typename Key, typename Value, typename Compare = std::less<> >
  class BinarySearchTree
  {
    friend class BidirectionalIterator< Key, Value, Compare >;
    friend class RotatableBinarySearchTree< Key, Value, Compare >;
    friend class RedBlackTree< Key, Value, Compare >;
  public:
    using data_t = std::pair< Key, Value >;
    using bst_t = BinarySearchTree< Key, Value, Compare >;
    using tree_t = TreeNode< data_t >;
    using iterator = BidirectionalIterator< Key, Value, Compare >;
    using const_iterator = ConstBidirectionalIterator< Key, Value, Compare >;
    using reverse_iterator = std::reverse_iterator< iterator >;
    using const_reverse_iterator = std::reverse_iterator< const_iterator >;
    BinarySearchTree();
    ~BinarySearchTree();
    BinarySearchTree(const BinarySearchTree &other);
    BinarySearchTree(BinarySearchTree &&other) noexcept;
    explicit BinarySearchTree(const Compare &compare);
    BinarySearchTree &operator=(const BinarySearchTree &other);
    BinarySearchTree &operator=(BinarySearchTree &&other) noexcept;
    void remove(const data_t &data);
    iterator find(const Key &key);
    const_iterator find(const Key &key) const;
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
    Value &at(const Key &key);
    const Value &at(const Key &key) const;
    Value &operator[](const Key &key);
    Value &operator[](Key &&key);
    size_t size() const;
    bool empty() const;
    template< typename P >
    std::pair< iterator, bool > insert(P &&data);
    std::pair< iterator, bool > insert(const data_t &data);
    iterator insert(const_iterator pos, const data_t &data);
    iterator insert(const_iterator pos, data_t &&data);
    template< typename... Args >
    std::pair< iterator, bool > emplace(Args &&... args);
    void clear();
    iterator erase(iterator pos);
    iterator erase(const_iterator pos);
    iterator erase(const_iterator first, const_iterator last);
    size_t erase(const Key &key);
    size_t count(const Key &key) const;
    void swap(bst_t &other);
    iterator lower_bound(const Key &key);
    const_iterator lower_bound(const Key &key) const;
    iterator upper_bound(const Key &key);
    const_iterator upper_bound(const Key &key) const;
    Compare value_comp() const;
    template< typename F >
    F traverseLnr(F f) const;
  private:
    tree_t *initFake();
    void clear(TreeNode< data_t > *node);
    TreeNode< data_t > *insertImpl(TreeNode< data_t > *node, TreeNode< data_t > *parent,
                                   const Key &key, const Value &value);
    TreeNode< data_t > *removeImpl(TreeNode< data_t > *node, const data_t &data);
    TreeNode< data_t > *copyBegin(const TreeNode< data_t > *beginNode);
    TreeNode< data_t > *copyEnd(const TreeNode< data_t > *endNode);
    TreeNode< data_t > *findMin(TreeNode< data_t > *node) const;
    TreeNode< data_t > *findMax(TreeNode< data_t > *node) const;
    TreeNode< data_t > *copyTree(const TreeNode< data_t > *node);
    template< typename F >
    F traverseLnrImpl(tree_t *node, F &f) const;
    tree_t *root_;
    tree_t *fakeNode_;
    size_t size_;
    Compare compare_;
  };
  template< typename Key, typename Value, typename Compare >
  template< typename F >
  F BinarySearchTree< Key, Value, Compare >::traverseLnrImpl(tree_t *node, F &f) const
  {
    if (!node)
    {
      return f;
    }
    traverseLnrImpl(node->left, f);
    f(node->data);
    std::cout << node->data << " \n";
    traverseLnrImpl(node->right, f);
  }
  template< typename Key, typename Value, typename Compare >
  template< typename F >
  F BinarySearchTree< Key, Value, Compare >::traverseLnr(F f) const
  {
    traverseLnrImpl(root_, f);
    return f;
  }
  template< typename Key, typename Value, typename Compare >
  typename BinarySearchTree< Key, Value, Compare >::const_reverse_iterator
  BinarySearchTree< Key, Value, Compare >::crend() const noexcept
  {
    return const_reverse_iterator(cbegin());
  }
  template< typename Key, typename Value, typename Compare >
  typename BinarySearchTree< Key, Value, Compare >::const_reverse_iterator
  BinarySearchTree< Key, Value, Compare >::rend() const noexcept
  {
    return crend();
  }
  template< typename Key, typename Value, typename Compare >
  typename BinarySearchTree< Key, Value, Compare >::reverse_iterator
  BinarySearchTree< Key, Value, Compare >::rend() noexcept
  {
    return const_reverse_iterator(begin());
  }
  template< typename Key, typename Value, typename Compare >
  typename BinarySearchTree< Key, Value, Compare >::const_reverse_iterator
  BinarySearchTree< Key, Value, Compare >::crbegin() const noexcept
  {
    return const_reverse_iterator(cend());
  }
  template< typename Key, typename Value, typename Compare >
  typename BinarySearchTree< Key, Value, Compare >::const_reverse_iterator
  BinarySearchTree< Key, Value, Compare >::rbegin() const noexcept
  {
    return crbegin();
  }
  template< typename Key, typename Value, typename Compare >
  typename BinarySearchTree< Key, Value, Compare >::reverse_iterator
  BinarySearchTree< Key, Value, Compare >::rbegin() noexcept
  {
    return const_reverse_iterator(end());
  }
  template< typename Key, typename Value, typename Compare >
  BinarySearchTree< Key, Value, Compare >::BinarySearchTree(const Compare &compare):
    BinarySearchTree()
  {
    compare_ = compare;
  }
  template< typename Key, typename Value, typename Compare >
  TreeNode< std::pair< Key, Value > > *BinarySearchTree< Key, Value, Compare >::copyTree(const TreeNode< data_t > *node)
  {
    if (!node)
    {
      return nullptr;
    }
    auto *newNode = new TreeNode< data_t >(node->data);
    newNode->left = copyTree(node->left);
    newNode->right = copyTree(node->right);
    if (newNode->left)
    {
      newNode->left->parent = newNode;
    }
    if (newNode->right)
    {
      newNode->right->parent = newNode;
    }
    return newNode;
  }
  template< typename Key, typename Value, typename Compare >
  TreeNode< std::pair< Key, Value > > *BinarySearchTree< Key, Value, Compare >::findMin(TreeNode< data_t > *node) const
  {
    if (!node)
    {
      return fakeNode_;
    }
    while (node->left)
    {
      node = node->left;
    }
    return node;
  }
  template< typename Key, typename Value, typename Compare >
  TreeNode< std::pair< Key, Value > > *BinarySearchTree< Key, Value, Compare >::findMax(TreeNode< data_t > *node) const
  {
    if (!node)
    {
      return fakeNode_;
    }
    while (node->right)
    {
      node = node->right;
    }
    return node;
  }
  template< typename Key, typename Value, typename Compare >
  ConstBidirectionalIterator< Key, Value, Compare > BinarySearchTree< Key, Value, Compare >::begin() const noexcept
  {
    return cbegin();
  }
  template< typename Key, typename Value, typename Compare >
  ConstBidirectionalIterator< Key, Value, Compare > BinarySearchTree< Key, Value, Compare >::last() const noexcept
  {
    return clast();
  }
  template< typename Key, typename Value, typename Compare >
  ConstBidirectionalIterator< Key, Value, Compare > BinarySearchTree< Key, Value, Compare >::end() const noexcept
  {
    return cend();
  }
  template< typename Key, typename Value, typename Compare >
  template< typename... Args >
  std::pair< typename BinarySearchTree< Key, Value, Compare >::iterator, bool >
  BinarySearchTree< Key, Value, Compare >::emplace(Args &&... args)
  {
    data_t data(std::forward< Args >(args)...);
    return insert(std::move(data));
  }
  template< typename Key, typename Value, typename Compare >
  void BinarySearchTree< Key, Value, Compare >::swap(BinarySearchTree::bst_t &other)
  {
    using std::swap;
    swap(fakeNode_, other.fakeNode_);
    swap(root_, other.root_);
    swap(size_, other.size_);
    swap(compare_, other.compare_);
  }
  template< typename Key, typename Value, typename Compare >
  size_t BinarySearchTree< Key, Value, Compare >::count(const Key &key) const
  {
    return (find(key) == end()) ? 0 : 1;
  }
  template< typename Key, typename Value, typename Compare >
  typename BinarySearchTree< Key, Value, Compare >::const_iterator
  BinarySearchTree< Key, Value, Compare >::upper_bound(const Key &key) const
  {
    return const_iterator(upper_bound(key));
  }
  template< typename Key, typename Value, typename Compare >
  typename BinarySearchTree< Key, Value, Compare >::iterator
  BinarySearchTree< Key, Value, Compare >::upper_bound(const Key &key)
  {
    iterator it = begin();
    while (it != end() && compare_(key, it->first))
    {
      ++it;
    }
    return it;
  }
  template< typename Key, typename Value, typename Compare >
  Compare BinarySearchTree< Key, Value, Compare >::value_comp() const
  {
    return compare_;
  }
  template< typename Key, typename Value, typename Compare >
  typename BinarySearchTree< Key, Value, Compare >::const_iterator
  BinarySearchTree< Key, Value, Compare >::lower_bound(const Key &key) const
  {
    return const_iterator(const_cast< BinarySearchTree * >(this)->lower_bound(key));
  }
  template< typename Key, typename Value, typename Compare >
  typename BinarySearchTree< Key, Value, Compare >::iterator
  BinarySearchTree< Key, Value, Compare >::lower_bound(const Key &key)
  {
    iterator it = begin();
    while (it != end())
    {
      if (!compare_(key, it->first))
      {
        break;
      }
      ++it;
    }
    return it;
  }
  template< typename Key, typename Value, typename Compare >
  ConstBidirectionalIterator< Key, Value, Compare > BinarySearchTree< Key, Value, Compare >::clast() const noexcept
  {
    return const_iterator(root_, findMax(root_), fakeNode_);
  }
  template< typename Key, typename Value, typename Compare >
  BidirectionalIterator< Key, Value, Compare > BinarySearchTree< Key, Value, Compare >::last() noexcept
  {
    return iterator(root_, findMax(root_), fakeNode_);
  }
  template< typename Key, typename Value, typename Compare >
  ConstBidirectionalIterator< Key, Value, Compare > BinarySearchTree< Key, Value, Compare >::cbegin() const noexcept
  {
    return const_iterator(root_, findMin(root_), fakeNode_);
  }
  template< typename Key, typename Value, typename Compare >
  BidirectionalIterator< Key, Value, Compare > BinarySearchTree< Key, Value, Compare >::begin() noexcept
  {
    return iterator(root_, findMin(root_), fakeNode_);
  }
  template< typename Key, typename Value, typename Compare >
  bool BinarySearchTree< Key, Value, Compare >::empty() const
  {
    return root_ == nullptr;
  }
  template< typename Key, typename Value, typename Compare >
  size_t BinarySearchTree< Key, Value, Compare >::size() const
  {
    return size_;
  }
  template< typename Key, typename Value, typename Compare >
  void BinarySearchTree< Key, Value, Compare >::clear()
  {
    clear(root_);
  }
  template< typename Key, typename Value, typename Compare >
  BidirectionalIterator< Key, Value, Compare > BinarySearchTree< Key, Value, Compare >::end() noexcept
  {
    return iterator(root_, fakeNode_, fakeNode_);
  }
  template< typename Key, typename Value, typename Compare >
  ConstBidirectionalIterator< Key, Value, Compare > BinarySearchTree< Key, Value, Compare >::cend() const noexcept
  {
    return const_iterator(root_, fakeNode_, fakeNode_);
  }
  template< typename Key, typename Value, typename Compare >
  template< typename P >
  std::pair< typename BinarySearchTree< Key, Value, Compare >::iterator, bool >
  BinarySearchTree< Key, Value, Compare >::insert(P &&data)
  {
    data_t newData(std::forward< P >(data));
    return insert(newData);
  }
  template< typename Key, typename Value, typename Compare >
  Value &BinarySearchTree< Key, Value, Compare >::operator[](const Key &key)
  {
    try
    {
      return at(key);
    }
    catch (const std::out_of_range &e)
    {
    }
    return insert({key, Value{}}).first->second;
  }
  template< typename Key, typename Value, typename Compare >
  Value &BinarySearchTree< Key, Value, Compare >::operator[](Key &&key)
  {
    try
    {
      return at(key);
    }
    catch (const std::out_of_range &)
    {
    }
    return *(emplace(key).first);
  }
  template< typename Key, typename Value, typename Compare >
  Value &BinarySearchTree< Key, Value, Compare >::at(const Key &key)
  {
    const BinarySearchTree *constThis = this;
    return const_cast<Value &>(constThis->at(key));
  }
  template< typename Key, typename Value, typename Compare >
  const Value &BinarySearchTree< Key, Value, Compare >::at(const Key &key) const
  {
    tree_t *node = root_;
    while (node)
    {
      if (compare_(key, node->data.first))
      {
        node = node->left;
      }
      else if (compare_(node->data.first, key))
      {
        node = node->right;
      }
      else
      {
        return node->data.second;
      }
    }
    throw std::out_of_range("Key not found.");
  }
  template< typename Key, typename Value, typename Compare >
  TreeNode< std::pair< Key, Value > > *
  BinarySearchTree< Key, Value, Compare >::copyBegin(const TreeNode< data_t > *beginNode)
  {
    if (!beginNode)
    {
      return nullptr;
    }
    auto *newBegin = new TreeNode< data_t >(beginNode->key, beginNode->value);
    newBegin->left = copyBegin(beginNode->left);
    newBegin->right = copyBegin(beginNode->right);
    if (newBegin->left)
    {
      newBegin->left->parent = newBegin;
    }
    if (newBegin->right)
    {
      newBegin->right->parent = newBegin;
    }
    return newBegin;
  }
  template< typename Key, typename Value, typename Compare >
  TreeNode< std::pair< Key, Value > > *
  BinarySearchTree< Key, Value, Compare >::copyEnd(const TreeNode< data_t > *endNode)
  {
    if (!endNode)
    {
      return nullptr;
    }
    auto *newEnd = new TreeNode< data_t >(endNode->key, endNode->value);
    newEnd->left = copyEnd(endNode->left);
    newEnd->right = copyEnd(endNode->right);
    if (newEnd->left)
    {
      newEnd->left->parent = newEnd;
    }
    if (newEnd->right)
    {
      newEnd->right->parent = newEnd;
    }
    return newEnd;
  }
  template< typename Key, typename Value, typename Compare >
  BinarySearchTree< Key, Value, Compare > &
  BinarySearchTree< Key, Value, Compare >::operator=(BinarySearchTree &&other) noexcept
  {
    if (this != std::addressof(other))
    {
      bst_t tmp(std::move(other));
      clear();
      swap(tmp);
    }
    return *this;
  }
  template< typename Key, typename Value, typename Compare >
  BinarySearchTree< Key, Value, Compare > &
  BinarySearchTree< Key, Value, Compare >::operator=(const BinarySearchTree &other)
  {
    if (this != std::addressof(other))
    {
      bst_t tmp(other);
      clear();
      swap(tmp);
    }
    return *this;
  }
  template< typename Key, typename Value, typename Compare >
  BinarySearchTree< Key, Value, Compare >::BinarySearchTree(BinarySearchTree &&other) noexcept:
    root_(other.root_),
    fakeNode_(other.fakeNode_),
    size_(other.size_),
    compare_(other.compare_)
  {
    other.fakeNode_ = nullptr;
    other.root_ = nullptr;
    other.size_ = 0;
  }
  template< typename Key, typename Value, typename Compare >
  TreeNode< std::pair< Key, Value > > *BinarySearchTree< Key, Value, Compare >::initFake()
  {
    void *nodeMemory = ::operator new(sizeof(BinarySearchTree::tree_t));
    auto *fakeNode = static_cast< BinarySearchTree::tree_t * >(nodeMemory);
    fakeNode->parent = nullptr;
    fakeNode->left = nullptr;
    fakeNode->right = nullptr;
    return fakeNode;
  }
  template< typename Key, typename Value, typename Compare >
  BinarySearchTree< Key, Value, Compare >::BinarySearchTree(const BinarySearchTree &other):
    root_(nullptr),
    fakeNode_(initFake()),
    size_(0),
    compare_(other.compare_)
  {
    try
    {
      root_ = copyTree(other.root_);
    }
    catch (...)
    {
      clear();
      ::operator delete(fakeNode_);
      throw;
    }
  }
  template< typename Key, typename Value, typename Compare >
  TreeNode< std::pair< Key, Value > > *
  BinarySearchTree< Key, Value, Compare >::removeImpl(TreeNode< data_t > *node, const data_t &data)
  {
    if (!node)
    {
      return nullptr;
    }
    if (compare_(data.first, node->data.first))
    {
      node->left = removeImpl(node->left, data);
    }
    else if (compare_(node->data.first, data.first))
    {
      node->right = removeImpl(node->right, data);
    }
    else
    {
      if (!node->left)
      {
        TreeNode< data_t > *rightChild = node->right;
        if (rightChild)
        {
          rightChild->parent = node->parent;
        }
        --size_;
        delete node;
        return rightChild;
      }
      else if (!node->right)
      {
        TreeNode< data_t > *leftChild = node->left;
        if (leftChild)
        {
          leftChild->parent = node->parent;
        }
        --size_;
        delete node;
        return leftChild;
      }
      else
      {
        TreeNode< data_t > *minRight = findMin(node->right);
        node->data.first = minRight->data.first;
        node->data.second = minRight->data.second;
        node->right = removeImpl(node->right, minRight->data);
      }
    }
    return node;
  }
  template< typename Key, typename Value, typename Compare >
  TreeNode< std::pair< Key, Value > > *BinarySearchTree< Key, Value, Compare >::insertImpl(TreeNode< data_t > *node,
                                                                                           TreeNode< data_t > *parent,
                                                                                           const Key &key,
                                                                                           const Value &value)
  {
    if (!node)
    {
      auto *newNode = new TreeNode< data_t >(data_t(key, value));
      newNode->parent = parent;
      return newNode;
    }
    if (compare_(key, node->data.first))
    {
      node->left = insertImpl(node->left, node, key, value);
      node->left->parent = node;
    }
    else if (compare_(node->data.first, key))
    {
      node->right = insertImpl(node->right, node, key, value);
      node->right->parent = node;
    }
    else
    {
      node->data.second = value;
    }
    return node;
  }
  template< typename Key, typename Value, typename Compare >
  ConstBidirectionalIterator< Key, Value, Compare > BinarySearchTree< Key, Value, Compare >::find(const Key &key) const
  {
    iterator it = const_cast<bst_t *>(this)->find(key);
    return const_iterator(it);
  }
  template< typename Key, typename Value, typename Compare >
  BidirectionalIterator< Key, Value, Compare > BinarySearchTree< Key, Value, Compare >::find(const Key &key)
  {
    tree_t *current = root_;
    while (current)
    {
      if (compare_(current->data.first, key))
      {
        current = current->right;
      }
      else if (compare_(key, current->data.first))
      {
        current = current->left;
      }
      else
      {
        return iterator(root_, current, fakeNode_);
      }
    }
    return end();
  }
  template< typename Key, typename Value, typename Compare >
  void BinarySearchTree< Key, Value, Compare >::remove(const data_t &data)
  {
    root_ = removeImpl(root_, data);
  }
  template< typename Key, typename Value, typename Compare >
  std::pair< typename BinarySearchTree< Key, Value, Compare >::iterator, bool >
  BinarySearchTree< Key, Value, Compare >::insert(const data_t &data)
  {
    root_ = insertImpl(root_, nullptr, data.first, data.second);
    ++size_;
    iterator it = find(data.first);
    if (it == end())
    {
      return std::make_pair(end(), false);
    }
    else
    {
      return std::make_pair(it, true);
    }
  }
  template< typename Key, typename Value, typename Compare >
  BinarySearchTree< Key, Value, Compare >::BinarySearchTree():
    root_(nullptr),
    fakeNode_(initFake()),
    size_(0),
    compare_()
  {
  }
  template< typename Key, typename Value, typename Compare >
  BinarySearchTree< Key, Value, Compare >::~BinarySearchTree()
  {
    ::operator delete(fakeNode_);
    clear(root_);
  }
  template< typename Key, typename Value, typename Compare >
  void BinarySearchTree< Key, Value, Compare >::clear(TreeNode< data_t > *node)
  {
    if (node)
    {
      clear(node->left);
      clear(node->right);
      delete node;
    }
    root_ = nullptr;
  }
  template< typename Key, typename Value, typename Compare >
  typename BinarySearchTree< Key, Value, Compare >::iterator
  BinarySearchTree< Key, Value, Compare >::insert(const_iterator pos, const data_t &data)
  {
    if (!pos.node_)
    {
      return iterator(root_, insertImpl(nullptr, nullptr, data.first, data.second), fakeNode_);
    }
    auto nonConstPos = iterator(pos);
    if (compare_(data.first, pos.node_->data.first))
    {
      if (!pos.node_->left)
      {
        return iterator(root_, insertImpl(nullptr, nonConstPos.node_, data.first, data.second), fakeNode_);
      }
      else
      {
        return iterator(root_, insertImpl(pos.node_->left, nonConstPos.node_, data.first, data.second), fakeNode_);
      }
    }
    else
    {
      if (!pos.node_->right)
      {
        return iterator(root_, insertImpl(nullptr, nonConstPos.node_, data.first, data.second), fakeNode_);
      }
      else
      {
        return iterator(root_, insertImpl(pos.node_->right, nonConstPos.node_, data.first, data.second), fakeNode_);
      }
    }
  }
  template< typename Key, typename Value, typename Compare >
  typename BinarySearchTree< Key, Value, Compare >::iterator
  BinarySearchTree< Key, Value, Compare >::insert(const_iterator pos, data_t &&data)
  {
    return insert(pos, std::forward< data_t >(data));
  }
  template< typename Key, typename Value, typename Compare >
  typename BinarySearchTree< Key, Value, Compare >::iterator
  BinarySearchTree< Key, Value, Compare >::erase(iterator pos)
  {
    if (pos == end() || pos.node_ == fakeNode_)
    {
      throw std::out_of_range("Invalid iterator for erase.");
    }
    tree_t *node = pos.node_;
    tree_t *parent = node->parent;
    tree_t *next_node = nullptr;
    if (node->right)
    {
      next_node = node->right;
      while (next_node->left)
      {
        next_node = next_node->left;
      }
    }
    else if (node->left)
    {
      next_node = node->left;
      while (next_node->right)
      {
        next_node = next_node->right;
      }
    }
    if (!parent)
    {
      root_ = next_node;
    }
    else if (parent->left == node)
    {
      parent->left = next_node;
    }
    else
    {
      parent->right = next_node;
    }
    delete node;
    --size_;
    return iterator(root_, next_node, fakeNode_);
  }
  template< typename Key, typename Value, typename Compare >
  typename BinarySearchTree< Key, Value, Compare >::iterator
  BinarySearchTree< Key, Value, Compare >::erase(const_iterator pos)
  {
    return erase(iterator(pos));
  }
  template< typename Key, typename Value, typename Compare >
  typename BinarySearchTree< Key, Value, Compare >::iterator
  BinarySearchTree< Key, Value, Compare >::erase(const_iterator first, const_iterator last)
  {
    iterator it_first(first);
    iterator it_last(last);
    while (it_first != it_last)
    {
      auto next = it_first;
      ++next;
      erase(it_first);
      it_first = next;
    }
    return it_first;
  }
  template< typename Key, typename Value, typename Compare >
  size_t BinarySearchTree< Key, Value, Compare >::erase(const Key &key)
  {
    iterator it = find(key);
    if (it != end())
    {
      erase(it);
      return 1;
    }
    return 0;
  }
}
#endif
