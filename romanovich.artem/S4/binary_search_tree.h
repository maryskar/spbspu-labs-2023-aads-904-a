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
    using tree_node_t = TreeNode< data_t, bst_t >;
    using iterator = BidirectionalIterator< Key, Value, Compare >;
    using const_iterator = ConstBidirectionalIterator< Key, Value, Compare >;
    //using reverse_iterator = int;
    //using const_reverse_iterator = int;
    BinarySearchTree();
    ~BinarySearchTree();
    BinarySearchTree(const BinarySearchTree &other);
    BinarySearchTree(BinarySearchTree &&other) noexcept;
    BinarySearchTree &operator=(const BinarySearchTree &other);
    BinarySearchTree &operator=(BinarySearchTree &&other) noexcept;
    void remove(const data_t &data);
    iterator find(const data_t &data);
    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;
    iterator last() noexcept;
    const_iterator last() const noexcept;
    const_iterator clast() const noexcept;
    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;
    /*reverse_iterator rbegin();
    reverse_iterator rend();
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;*/
    data_t &at(const data_t &data);
    const data_t &at(const data_t &data) const;
    data_t &operator[](const data_t &data);
    data_t &operator[](data_t &&data);
    size_t size() const;
    bool empty() const;
    std::pair< iterator, bool > insert(data_t &&data);
    std::pair< iterator, bool > insert(const data_t &data);
    iterator insert(const_iterator pos, const data_t &data);
    iterator insert(const_iterator pos, data_t &&data);
    /*template< class InputIt >
    iterator insert(const_iterator pos, InputIt first, InputIt last);*/
    template< typename... Args >
    std::pair< iterator, bool > emplace(Args &&... args);
    void clear();
    iterator erase(iterator pos);
    iterator erase(const_iterator pos);
    iterator erase(const_iterator first, const_iterator last);
    size_t erase(const data_t &data);
    size_t count(const data_t &data) const;
    void swap(bst_t &other);
    iterator lower_bound(const data_t &data);
    const_iterator lower_bound(const data_t &data) const;
    iterator upper_bound(const data_t &data);
    const_iterator upper_bound(const data_t &data) const;
    Compare value_comp() const;
  private:
    tree_node_t *fakeNode_;
    tree_node_t *root_;
    size_t size_;
    Compare compare_;
    void clear(TreeNodeImpl< data_t > *nodeImpl);
    tree_node_t *insertImpl(tree_node_t *node, tree_node_t *parent,
                            const Key &key, const Value &value);
    tree_node_t *removeImpl(tree_node_t *node, const data_t &data);
    tree_node_t *initFake();
    tree_node_t *copyBegin(const tree_node_t *beginNode);
    tree_node_t *copyEnd(const tree_node_t *endNode);
  };
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
  size_t BinarySearchTree< Key, Value, Compare >::count(const data_t &data) const
  {
    size_t count = 0;
    const_iterator it = lower_bound(data);
    while (it != end() && it.node_->data == data)
    {
      ++count;
      ++it;
    }
    return count;
  }
  template< typename Key, typename Value, typename Compare >
  typename BinarySearchTree< Key, Value, Compare >::const_iterator
  BinarySearchTree< Key, Value, Compare >::upper_bound(const data_t &data) const
  {
    return const_iterator(upper_bound(data));
  }
  template< typename Key, typename Value, typename Compare >
  typename BinarySearchTree< Key, Value, Compare >::iterator
  BinarySearchTree< Key, Value, Compare >::upper_bound(const data_t &data)
  {
    iterator it = begin();
    while (it != end() && compare_(data.first, it->first))
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
  BinarySearchTree< Key, Value, Compare >::lower_bound(const data_t &data) const
  {
    return const_iterator(const_cast< BinarySearchTree * >(this)->lower_bound(data));
  }
  template< typename Key, typename Value, typename Compare >
  typename BinarySearchTree< Key, Value, Compare >::iterator
  BinarySearchTree< Key, Value, Compare >::lower_bound(const data_t &data)
  {
    iterator it = begin();
    while (it != end())
    {
      if (!compare_(data.first, it->first))
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
    return const_iterator(root_, root_->findMax(root_), fakeNode_);
  }
  template< typename Key, typename Value, typename Compare >
  BidirectionalIterator< Key, Value, Compare > BinarySearchTree< Key, Value, Compare >::last() noexcept
  {
    return iterator(root_, root_->findMax(root_), fakeNode_);
  }
  template< typename Key, typename Value, typename Compare >
  ConstBidirectionalIterator< Key, Value, Compare > BinarySearchTree< Key, Value, Compare >::cbegin() const noexcept
  {
    return const_iterator(root_, root_->findMin(root_), fakeNode_);
  }
  template< typename Key, typename Value, typename Compare >
  BidirectionalIterator< Key, Value, Compare > BinarySearchTree< Key, Value, Compare >::begin() noexcept
  {
    return iterator(root_, root_->findMin(root_), fakeNode_);
  }
  template< typename Key, typename Value, typename Compare >
  bool BinarySearchTree< Key, Value, Compare >::empty() const
  {
    return root_ == nullptr;
    //return size_ == 0;
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
  std::pair< typename BinarySearchTree< Key, Value, Compare >::iterator, bool >
  BinarySearchTree< Key, Value, Compare >::insert(data_t &&data)
  {
//  const Key &const_key = new_data.first;
//  const Value &const_value = new_data.second;
    data_t new_data(std::forward< data_t >(data));
    return insert(new_data);
  }
  template< typename Key, typename Value, typename Compare >
  std::pair< Key, Value > &BinarySearchTree< Key, Value, Compare >::operator[](const data_t &data)
  {
    //std::pair< iterator, bool > result = insert(key, Value{});
    //return result.first->value;
    return find(data).node_->data.second;
  }
  template< typename Key, typename Value, typename Compare >
  std::pair< Key, Value > &BinarySearchTree< Key, Value, Compare >::operator[](data_t &&data)
  {
    try
    {
      return at(data);
    }
    catch (const std::out_of_range &e)
    {
    }
    return *(emplace(data).first);
  }
  template< typename Key, typename Value, typename Compare >
  std::pair< Key, Value > &BinarySearchTree< Key, Value, Compare >::at(const data_t &data)
  {
    const BinarySearchTree *constThis = this;
    return const_cast<data_t &>(constThis->at(data));
  }
  template< typename Key, typename Value, typename Compare >
  const std::pair< Key, Value > &BinarySearchTree< Key, Value, Compare >::at(const data_t &data) const
  {
    tree_node_t *node = root_;
    while (node)
    {
      if (compare_(data.first, node->nodeImpl->data.first))
      {
        node = node->nodeImpl->left;
      }
      else if (compare_(node->nodeImpl->data.first, data.first))
      {
        node = node->nodeImpl->right;
      }
      else
      {
        return node->nodeImpl->data;
      }
    }
    throw std::out_of_range("Key not found.");
  }
  template< typename Key, typename Value, typename Compare >
  TreeNode< std::pair< Key, Value >, BinarySearchTree< Key, Value, Compare > > *
  BinarySearchTree< Key, Value, Compare >::copyBegin(const tree_node_t *beginNode)
  {
    if (!beginNode)
    {
      return nullptr;
    }
    auto *newBegin = new tree_node_t(beginNode->key, beginNode->value);
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
  TreeNode< std::pair< Key, Value >, BinarySearchTree< Key, Value, Compare > > *
  BinarySearchTree< Key, Value, Compare >::copyEnd(const tree_node_t *endNode)
  {
    if (!endNode)
    {
      return nullptr;
    }
    auto *newEnd = new tree_node_t(endNode->key, endNode->value);
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
    fakeNode_(other.fakeNode_),
    root_(other.root_),
//  begin_(other.begin_),
//  end_(other.end_),
    size_(other.size_),
    compare_(other.compare_)
  {
    other.fakeNode_ = nullptr;
    other.root_ = nullptr;
    other.begin_ = nullptr;
    other.end_ = nullptr;
    other.size_ = 0;
  }
  template< typename Key, typename Value, typename Compare >
  TreeNode< std::pair< Key, Value >, BinarySearchTree< Key, Value, Compare > > *
  BinarySearchTree< Key, Value, Compare >::initFake()
  {
    void *nodeMemory = ::operator new(sizeof(tree_node_t));
    auto *fakeNode = static_cast< tree_node_t * >(nodeMemory);
    fakeNode->nodeImpl = new TreeNodeImpl< data_t >(data_t(Key(), Value()));
    //std::cout << (int)fakeNode->color;
    fakeNode->nodeImpl->parent = nullptr;
    fakeNode->nodeImpl->left = nullptr;
    fakeNode->nodeImpl->right = nullptr;
    return fakeNode;
  }
  template< typename Key, typename Value, typename Compare >
  BinarySearchTree< Key, Value, Compare >::BinarySearchTree(const BinarySearchTree &other):
    fakeNode_(initFake()),
    root_(nullptr),
//  begin_(nullptr),
//  end_(nullptr),
    compare_(other.compare_),
    size_(0)
  {
    try
    {
      root_ = copyTree(other.root_);
    }
    catch (...)
    {
      clear();
      delete fakeNode_;
      throw;
    }
//  begin_ = copyBegin(other.begin_);
//  end_ = copyEnd(other.end_);
  }
  template< typename Key, typename Value, typename Compare >
  TreeNode< std::pair< Key, Value >, BinarySearchTree< Key, Value, Compare > > *
  BinarySearchTree< Key, Value, Compare >::removeImpl(tree_node_t *node, const data_t &data)
  {
    if (!node)
    {
      return nullptr;
    }
    if (compare_(data.first, node->nodeImpl->data.first))
    {
      node->nodeImpl->left = removeImpl(node->nodeImpl->left, data);
    }
    else if (compare_(node->nodeImpl->data.first, data.first))
    {
      node->nodeImpl->right = removeImpl(node->nodeImpl->right, data);
    }
    else
    {
      if (!node->nodeImpl->left)
      {
        tree_node_t *rightChild = node->nodeImpl->right;
        if (rightChild)
        {
          rightChild->parent = node->nodeImpl->parent;
        }
        --size_;
        delete node;
        return rightChild;
      }
      else if (!node->nodeImpl->right)
      {
        tree_node_t *leftChild = node->nodeImpl->left;
        if (leftChild)
        {
          leftChild->parent = node->nodeImpl->parent;
        }
        --size_;
        delete node;
        return leftChild;
      }
      else
      {
        tree_node_t *minRight = root_->findMin(node->nodeImpl->right);
        node->nodeImpl->data.first = minRight->data.first;
        node->nodeImpl->data.second = minRight->data.second;
        node->nodeImpl->right = removeImpl(node->nodeImpl->right, minRight->data);
      }
    }
    return node;
  }
  template< typename Key, typename Value, typename Compare >
  TreeNode< std::pair< Key, Value >, BinarySearchTree< Key, Value, Compare > > *
  BinarySearchTree< Key, Value, Compare >::insertImpl(tree_node_t *node,
                                                      tree_node_t *parent,
                                                      const Key &key,
                                                      const Value &value)
  {
    if (!node)
    {
      auto *newNode = new tree_node_t(data_t(key, value));
      newNode->parent = parent;
      return newNode;
    }
    if (compare_(key, node->nodeImpl->data.first))
    {
      node->nodeImpl->left = insertImpl(node->nodeImpl->left, node, key, value);
      node->nodeImpl->left->parent = node;
    }
    else if (compare_(node->nodeImpl->data.first, key))
    {
      node->nodeImpl->right = insertImpl(node->nodeImpl->right, node, key, value);
      node->nodeImpl->right->parent = node;
    }
    else
    {
      node->nodeImpl->data.second = value;
    }
    return node;
  }
  template< typename Key, typename Value, typename Compare >
  BidirectionalIterator< Key, Value, Compare > BinarySearchTree< Key, Value, Compare >::find(const data_t &data)
  {
    tree_node_t *current = root_;
    while (current != nullptr)
    {
      if (compare_(current->data.first, data.first))
      {
        current = current->right;
      }
      else if (compare_(data.first, current->data.first))
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
    iterator it = find(data);
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
    fakeNode_(initFake()),
    root_(nullptr),
    size_(0),
    compare_()
  {
  }
  template< typename Key, typename Value, typename Compare >
  BinarySearchTree< Key, Value, Compare >::~BinarySearchTree()
  {
    delete fakeNode_;
    clear(root_->nodeImpl);
  }
  template< typename Key, typename Value, typename Compare >
  void BinarySearchTree< Key, Value, Compare >::clear(TreeNodeImpl< data_t > *nodeImpl)
  {
    if (nodeImpl)
    {
      clear(nodeImpl->left);
      clear(nodeImpl->right);
      delete nodeImpl;
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
/*template< typename Key, typename Value, typename Compare >
template< class InputIt >
typename BinarySearchTree< Key, Value, Compare >::iterator
BinarySearchTree< Key, Value, Compare >::insert(const_iterator pos, InputIt first, InputIt last)
{
  iterator result;
  for (InputIt it = first; it != last; ++it)
  {
    result = insert(pos, it);
  }
  return result;
}*/
  template< typename Key, typename Value, typename Compare >
  typename BinarySearchTree< Key, Value, Compare >::iterator
  BinarySearchTree< Key, Value, Compare >::erase(iterator pos)
  {
    if (pos == end() || pos.node_ == fakeNode_)
    {
      throw std::out_of_range("Invalid iterator for erase.");
    }
    tree_node_t *node = pos.node_;
    tree_node_t *parent = node->nodeImpl->parent;
    tree_node_t *next_node = nullptr;
    if (node->nodeImpl->right)
    {
      next_node = node->nodeImpl->right;
      while (next_node->nodeImpl->left)
      {
        next_node = next_node->nodeImpl->left;
      }
    }
    else if (node->nodeImpl->left)
    {
      next_node = node->nodeImpl->left;
      while (next_node->nodeImpl->right)
      {
        next_node = next_node->nodeImpl->right;
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
  size_t BinarySearchTree< Key, Value, Compare >::erase(const data_t &data)
  {
    //size_t count = 0;
    iterator it = find(data);
    if (it != end())
    {
      //iterator next = it;
      //++next;
      erase(it);
      return 1;
      //it = next;
      //++count;
    }
    return 0;//count;
  }
}
#endif
