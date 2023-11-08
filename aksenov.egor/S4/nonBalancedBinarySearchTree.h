#ifndef NONBALANCEDBINARYSEARCHTREE_H
#define NONBALANCEDBINARYSEARCHTREE_H
#include <functional>
#include <iostream>
#include "bidirectionalIterator.h"
#include "constBidirectionalIterator.h"
#include "tree.h"
#include <stack.h>

namespace aksenov
{
  template < class Key, class T, class Compare = std::less<  > >
  class BST
  {
  public:
    using Element = std::pair< Key, T >;
    using TreeNode = node_t< Element >;
    using NodePtr = node_t< Element > *;
    using mappedType = T;
    using Iter = BidirectionalIterator< Element >;
    using CIter = ConstBidirectionalIterator< Element >;
    friend class BidirectionalIterator< Element >;
    friend class ConstBidirectionalIterator< Element >;
    template < class, class, class >
    friend class AVL;

    Iter begin();
    CIter begin() const;
    CIter cbegin() const;
    Iter end();
    CIter end() const;
    CIter cend() const;
    Iter insert(const Element& element);
    template < class P >
    std::pair< Iter , bool > insert(P &&value);
    Iter insert( CIter it, const Element &value);
    template <class InputIterator>
    void insert(InputIterator first, InputIterator last);
    template < class P >
    Iter insert(CIter it, P &&value);
    Iter insert(Iter iter, const Element& element);
    template < class... Args >
    std::pair< Iter, bool > emplace(Args  &&...args);
    template< typename... Args >
    Iter emplaceHint(CIter hint, Args && ...args);
    Iter erase(Iter it);
    Iter erase(const Key& key);
    CIter find(const Key& key) const;
    Iter find(const Key& key);
    Iter lower_bound(const Key& key);
    CIter lower_bound(const Key& key) const;
    Iter upper_bound(const Key& key);
    CIter upper_bound(const Key& key) const;

    BST();
    ~BST();
    BST(const BST &other);
    BST(BST &&other) noexcept;
    BST& operator=(const BST &other);
    BST& operator=(BST &&other) noexcept;
    mappedType &operator[](const Key &key);
    mappedType &operator[](Key &&key);
    mappedType &at(const Key &key);
    const mappedType &at(const Key &key) const;
    size_t count(const Key& key) const;
    bool contains(const Key& key) const;
    void insert(const Key &key, const T &value);
    bool isEmpty() const;
    void swap(BST& other) noexcept;
    void clear();
    template < typename F >
    F traverse_rnl(F f) const;
    template < typename F >
    F traverse_lnr(F f) const;
    template < typename F >
    F traverse_breadth(F f) const;
  private:
    Compare cmp_;
    NodePtr root_;

    bool isEqual(const Key& key1, const Key& key2) const
    {
      return !cmp_(key1, key2) && !cmp_(key2, key1);
    }

    bool isLess(const Key& key1, const Key& key2) const
    {
      return cmp_(key1, key2);
    }

    NodePtr insert(NodePtr root, const Element& element)
    {
      if (!root)
      {
        NodePtr toInsert = new TreeNode(element, nullptr);
        return toInsert;
      }
      else if (isLess(element.first, root->data_.first))
      {
        root->left_ = insert(root->left_, element);
        root->left_->parent_ = root;
      }
      else if (isLess(root->data_.first, element.first))
      {
        root->right_ = insert(root->right_, element);
        root->right_->parent_ = root;
      }
      fixHeight(root);
      return root;
    }

    NodePtr find(const NodePtr root, const Key& key) const
    {
      if (!root)
      {
        return nullptr;
      }
      const Key nodeKey = root->data_.first;
      if (isLess(nodeKey, key))
      {
        return find(root->right_, key);
      }
      if (isLess(key, nodeKey))
      {
        return find(root->left_, key);
      }
      return root;
    }

    NodePtr erase(NodePtr root, const Key& key)
    {
      if (!root || !root_)
      {
        return nullptr;
      }
      else if (isLess(root->data_.first, key))
      {
        root = erase(root->right_, key);
      }
      else if (isLess(key, root->data_.first))
      {
        root = erase(root->left_, key);
      }
      else
      {
        if (getAmountOfChildren(root) == 0)
        {
          NodePtr toReturn = getNext< Element >(root);
          if (root->parent_)
          {
            if (root->parent_->left_ == root)
            {
              root->parent_->left_ = nullptr;
            }
            else
            {
              root->parent_->right_ = nullptr;
            }
          }
          delete root;
          if (!toReturn)
          {
            root_ = nullptr;
          }
          else
          {
            fixHeightOfAllTree(toReturn);
          }
          return toReturn;
        }
        if (getAmountOfChildren(root) == 2)
        {
          if (root->right_ && !root->right_->left_)
          {
            root->data_ = root->right_->data_;
            NodePtr toDelete = root->right_;
            root->right_ = root->right_->right_;
            delete toDelete;
            fixHeightOfAllTree(root);
            return root;
          }
          else
          {
            NodePtr toCopy = findMin(root->right_);
            root->data_ = toCopy->data_;
            toCopy->parent_->left_ = nullptr;
            NodePtr toFix = toCopy->parent_;
            delete toCopy;
            fixHeightOfAllTree(toFix);
            return root;
          }
        }
        else if (getAmountOfChildren(root) == 1)
        {
          NodePtr toDelete = root->left_ ? root->left_ : root->right_;
          root->data_ = toDelete->data_;
          root->left_ = toDelete->left_;
          if (root->left_)
          {
            root->left_->parent_ = root_;
          }
          root->right_ = toDelete->right_;
          if (root->right_)
          {
            root->right_->parent_ = root_;
          }
          delete toDelete;
          NodePtr toReturn = root;
          fixHeightOfAllTree(toReturn);
          return toReturn;
        }
      }
      return root;
    }

    int getAmountOfChildren(const NodePtr node) const
    {
      bool isTwoChildren = node->left_ && node->right_;
      bool isOneChildren = (node->left_ && !node->right_) || (!node->left_ && node->right_);
      return isTwoChildren ? 2 : (isOneChildren ? 1 : 0);
    }

    NodePtr findMin(const NodePtr node) const
    {
      if (!node)
      {
        return nullptr;
      }
      if (node->left_)
      {
        return findMin(node->left_);
      }
      return node;
    }

    NodePtr findMax(const NodePtr node) const
    {
      return node->right_ ? findMin(node->right_) : node;
    }

    void fixHeight(NodePtr node)
    {
      int rh = node->right_ ? node->right_->height_ : 0;
      int lh = node->left_ ? node->left_->height_ : 0;
      node->height_ = std::max(rh, lh) + 1;
    }

    void fixHeightOfAllTree(NodePtr node)
    {
      fixHeight(node);
      if (node->parent_)
      {
        fixHeightOfAllTree(node->parent_);
      }
    }

    int getDiff(const NodePtr node) const
    {
      int rh = node->right_ ? node->right_->height_ : 0;
      int lh = node->left_ ? node->left_->height_ : 0;
      return rh - lh;
    }

    NodePtr rotateLeft(NodePtr node)
    {
      NodePtr helper = node->right_;
      node->right_ = helper->left_;
      if (node->right_)
      {
        node->right_->parent_ = node;
      }
      helper->left_ = node;
      if (node == root_)
      {
        root_ = helper;
        helper->parent_ = nullptr;
      }
      else if (node->parent_)
      {
        if (node->parent_->left_ == node)
        {
          node->parent_->left_ = helper;
        }
        else
        {
          node->parent_->right_ = helper;
        }
      }
      helper->parent_ = node->parent_;
      node->parent_ = helper;
      fixHeightOfAllTree(node);
      return helper;
    }

    NodePtr rotateRight(NodePtr node)
    {
      NodePtr helper = node->left_;
      node->left_ = helper->right_;
      if (node->left_)
      {
        node->left_->parent_ = node;
      }
      helper->right_ = node;
      if (node == root_)
      {
        root_ = helper;
        helper->parent_ = nullptr;
      }
      else if (node->parent_)
      {
        if (node->parent_->left_ == node)
        {
          node->parent_->left_ = helper;
        }
        else
        {
          node->parent_->right_ = helper;
        }
      }
      helper->parent_ = node->parent_;
      node->parent_ = helper;
      fixHeightOfAllTree(node);
      return helper;
    }
  };

  template< class Key, class T, class Compare >
  template< typename F >
  F BST< Key, T, Compare >::traverse_lnr(F f) const
  {
    NodePtr tmp = root_;
    if (!tmp)
    {
      return f;
    }
    Stack< NodePtr > helper(root_->height_ * 2);
    while (!helper.isEmpty() || tmp)
    {
      if (tmp)
      {
        helper.push(tmp);
        tmp = tmp->left_;
      }
      else
      {
        tmp = helper.getTop();
        helper.pop();
        f(tmp->data_);
        tmp = tmp->right_;
      }
    }
    return f;
  }

  template< class Key, class T, class Compare >
  template< typename F >
  F BST< Key, T, Compare >::traverse_rnl(F f) const
  {
    NodePtr tmp = root_;
    if (!tmp)
    {
      return f;
    }
    Stack< NodePtr > helper(root_->height_ * 2);
    helper.push(tmp);
    while (!helper.isEmpty() && tmp)
    {
      while (tmp->right_)
      {
        tmp = tmp->right_;
        helper.push(tmp);
      }
      tmp = helper.getTop();
      helper.pop();
      f(tmp->data_);
      if (tmp->left_)
      {
        tmp = tmp->left_;
        helper.push(tmp);
      }
    }
    return f;
  }

  template< class Key, class T, class Compare >
  typename BST< Key, T, Compare >::Iter BST< Key, T, Compare >::begin()
  {
    return Iter(findMin(root_));
  }

  template< class Key, class T, class Compare >
  typename BST< Key, T, Compare >::CIter BST< Key, T, Compare >::begin() const
  {
    return cbegin();
  }

  template< class Key, class T, class Compare >
  typename BST< Key, T, Compare >::Iter BST< Key, T, Compare >::end()
  {
    return Iter(nullptr);
  }

  template< class Key, class T, class Compare >
  typename BST< Key, T, Compare >::CIter BST< Key, T, Compare >::end() const
  {
    return cend();
  }

  template< class Key, class T, class Compare >
  typename BST< Key, T, Compare >::CIter BST< Key, T, Compare >::cbegin() const
  {
    return CIter(findMin(root_));
  }

  template< class Key, class T, class Compare >
  typename BST< Key, T, Compare >::CIter BST< Key, T, Compare >::cend() const
  {
    return CIter(nullptr);
  }

  template< class Key, class T, class Compare >
  typename BST< Key, T, Compare >::Iter BST< Key, T, Compare >::insert(const Element& element)
  {
    root_ = insert(root_, element);
    Iter toReturn(find(root_, element.first));
    return toReturn;
  }

  template< class Key, class T, class Compare >
  void BST< Key, T, Compare >::insert(const Key &key, const T &value)
  {
    insert(std::make_pair(key, value));
  }

  template< class Key, class T, class Compare >
  template < class P >
  std::pair< typename BST< Key, T, Compare >::Iter, bool > BST< Key, T, Compare >::insert(P &&value)
  {
    Element element = std::forward< P >(value);
    if (!root_)
    {
      root_ = new TreeNode(element, nullptr);
      return std::make_pair(Iter(root_), true);
    }
    NodePtr current = root_;
    NodePtr parent = nullptr;
    while (current)
    {
      if (element.first == current->data_.first)
      {
        return std::make_pair(Iter(current), false);
      }
      parent = current;
      if (isLess(element.first, current->data_.first))
      {
        current = current->left_;
      }
      else
      {
        current = current->right_;
      }
    }
    NodePtr newNode = new TreeNode(element, parent);
    if (isLess(element.first, parent->data_.first))
    {
      parent->left_ = newNode;
    }
    else
    {
      parent->right_ = newNode;
    }
    fixHeightOfAllTree(newNode);
    return std::make_pair(Iter(newNode), true);
  }

  template< class Key, class T, class Compare >
  typename BST< Key, T, Compare >::Iter BST< Key, T, Compare >::insert( CIter it, const Element &value)
  {
    return insert(it, std::make_pair(value.first, value.second));
  }

  template< class Key, class T, class Compare >
  template <class InputIterator>
  void BST< Key, T, Compare >::insert(InputIterator first, InputIterator last)
  {
    for (; first != last; ++first)
    {
      insert(*first);
    }
  }

  template< class Key, class T, class Compare >
  template < class P >
  typename BST< Key, T, Compare >::Iter BST< Key, T, Compare >::insert(CIter it, P &&value)
  {
    return insert(it, std::forward< P >(value));
  }

  template< class Key, class T, class Compare >
  typename BST< Key, T, Compare >::Iter BST< Key, T, Compare >::insert(Iter iter, const Element& element)
  {
    *iter = insert(*iter, element);
    Iter toReturn(find(root_, element.first));
    return toReturn;
  }

  template < class Key, class T, class Compare >
  template < class... Args >
  std::pair< typename BST< Key, T, Compare >::Iter, bool > BST< Key, T, Compare >::emplace(Args&&... args)
  {
    Iter toReturn = insert(std::forward< Args >(args)...);
    return {toReturn, toReturn != end()};
  }

  template < class Key, class T, class Compare >
  template < class... Args >
  typename BST< Key, T, Compare >::Iter BST< Key, T, Compare >::emplaceHint(CIter hint, Args &&...args)
  {
    Element element(std::forward< Args >(args)...);
    return insert(hint, element);
  }

  template < class Key, class T, class Compare >
  typename BST< Key, T, Compare >::Iter BST< Key, T, Compare >::erase(Iter it)
  {
    return Iter(erase(root_, (*it).first));
  }

  template < class Key, class T, class Compare >
  typename BST< Key, T, Compare >::Iter BST< Key, T, Compare >::erase(const Key& key)
  {
    return Iter(erase(root_, key));
  }

  template < class Key, class T, class Compare >
  typename BST< Key, T, Compare >::CIter BST< Key, T, Compare >::find(const Key& key) const
  {
    return CIter(find(root_, key));
  }

  template < class Key, class T, class Compare >
  typename BST< Key, T, Compare >::Iter BST< Key, T, Compare >::find(const Key& key)
  {
    return Iter(find(root_, key));
  }

  template < class Key, class T, class Compare >
  typename BST< Key, T, Compare >::Iter BST< Key, T, Compare >::lower_bound(const Key& key)
  {
    return find(key);
  }

  template < class Key, class T, class Compare >
  typename BST< Key, T, Compare >::CIter BST< Key, T, Compare >::lower_bound(const Key& key) const
  {
    return const_cast<BST<Key, T, Compare>*>(this)->lower_bound(key);
  }

  template < class Key, class T, class Compare >
  typename BST< Key, T, Compare >::Iter BST< Key, T, Compare >::upper_bound(const Key& key)
  {
    return ++find(key);
  }

  template < class Key, class T, class Compare >
  typename BST< Key, T, Compare >::CIter BST< Key, T, Compare >::upper_bound(const Key& key) const
  {
    return const_cast< BST< Key, T, Compare >* >(this)->upper_bound(key);
  }

  template < class Key, class T, class Compare >
  BST< Key, T, Compare >::BST():
    root_(nullptr)
  {}

  template < class Key, class T, class Compare >
  BST< Key, T, Compare >::~BST()
  {
    clear();
  }

  template < class Key, class T, class Compare >
  BST< Key, T, Compare >::BST(const BST& other):
    root_(nullptr)
  {
    if (other.root_)
    {
      try
      {
        Iter it = this->insert(*(other.cbegin()));
        CIter otherIt = other.cbegin();
        ++otherIt;
        while (otherIt != other.cend())
        {
          it = this->insert(*otherIt);
          ++otherIt;
        }
      }
      catch (...)
      {
        clear();
        throw;
      }
    }
  }

  template < class Key, class T, class Compare >
  BST< Key, T, Compare >::BST(BST  &&other) noexcept:
    root_(other.root_)
  {
    other.root_ = nullptr;
  }

  template < class Key, class T, class Compare >
  typename BST< Key, T, Compare >::BST &BST< Key, T, Compare >::operator=(const BST& other)
  {
    if (this != std::addressof(other))
    {
      BST< Key, T, Compare > tmp(other);
      swap(tmp);
    }
    return *this;
  }

  template < class Key, class T, class Compare >
  typename BST< Key, T, Compare >::BST &BST< Key, T, Compare >::operator=(BST&& other) noexcept
  {
    if (this != std::addressof(other))
    {
    BST< Key, T, Compare > tmp(std::move(other));
    swap(other);
    }
    return *this;
  }

  template <class Key, class T, class Compare>
  typename BST<Key, T, Compare>::mappedType &BST<Key, T, Compare>::operator[](const Key &key)
  {
    Element element(key, T());
    Iter it = insert(element).first;
    return it->second;
  }

  template <class Key, class T, class Compare>
  typename BST<Key, T, Compare>::mappedType &BST<Key, T, Compare>::operator[](Key &&key)
  {
    return (*this)[key];
  }

  template < class Key, class T, class Compare >
  typename BST< Key, T, Compare >::mappedType &BST< Key, T, Compare >::at(const Key &key)
  {
    Iter it = find(key);
    if (it == end())
    {
      throw std::out_of_range("Key not found");
    }
    return it->second;
  }

  template < class Key, class T, class Compare >
  const typename BST< Key, T, Compare >::mappedType &BST< Key, T, Compare >::at(const Key &key) const
  {
    return const_cast<BST<Key, T, Compare>*>(this)->at(key);
  }

  template < class Key, class T, class Compare >
  size_t BST< Key, T, Compare >::count(const Key& key) const
  {
    auto it = find(key);
    return (it != end()) ? 1ull : 0ull;
  }

  template < class Key, class T, class Compare >
  bool BST< Key, T, Compare >::contains(const Key& key) const
  {
    return count(key);
  }

  template < class Key, class T, class Compare >
  bool BST< Key, T, Compare >::isEmpty() const
  {
    return !root_;
  }

  template < class Key, class T, class Compare >
  void BST< Key, T, Compare >::swap(BST& other) noexcept
  {
  std::swap(root_, other.root_);
  std::swap(cmp_, other.cmp_);
  }

  template < class Key, class T, class Compare >
  void BST< Key, T, Compare >::clear()
  {
    if (root_)
    {
      Iter otherIt = begin();
      while (otherIt != end())
      {
        otherIt = erase(otherIt);
      }
    }
  }
}
#endif

