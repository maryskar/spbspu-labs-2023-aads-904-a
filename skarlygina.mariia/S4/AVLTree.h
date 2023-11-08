#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "BinSTree.h"
namespace skarlygina
{
  template < typename Key, typename Value, typename Compare = std::less< Key > >
  class AVLTree
  {
  public:
    using Iter = typename detail::BinSTree< Key, Value, Compare >::TreeIt;
    using ConstIter = typename detail::BinSTree< Key, Value, Compare >::CTreeIt;
    Iter insert(const Key&, const Value&);
    template < typename... Args >
    Iter emplace(const Key&, Args&&...);
    void erase(const Key&);
    Iter erase(Iter);
    Iter erase(Iter, Iter);
    bool isEmpty() const noexcept;
    Iter find(const Key&);
    ConstIter cfind(const Key&) const;
    Iter begin();
    ConstIter begin() const;
    ConstIter cbegin() const;
    Iter end();
    ConstIter end() const;
    ConstIter cend() const;

    ConstIter cupperBound(const Key&) const;
    Iter upperBound(const Key&);
    ConstIter clowerBound(const Key&) const;
    Iter lowerBound(const Key&);

    template < typename F >
    F traverse_lnr(F) const;
    template < typename F >
    F traverse_rnl(F) const;
    template < typename F >
    F traverse_breadth(F) const;
  private:
    detail::BinSTree< Key, Value, Compare > tree_;
    detail::node_t< Key, Value >* rightLeftRotation(detail::node_t< Key, Value >*);
    detail::node_t< Key, Value >* leftRightRotation(detail::node_t< Key, Value >*);
    detail::node_t< Key, Value >* balance(detail::node_t< Key, Value >*);
    void balanceAfterInsertion(detail::node_t< Key, Value >*);
    void balanceAfterErasure(detail::node_t< Key, Value >*);
  };
  template < typename Key, typename Value, typename Compare >
  typename AVLTree< Key, Value, Compare >::Iter AVLTree< Key, Value, Compare >::insert(const Key& k, const Value& v)
  {
    auto ptr = tree_.insert(k, v);
    balanceAfterInsertion(ptr);
    return Iter(ConstIter(ptr));
  }
  template < typename Key, typename Value, typename Compare >
  template < typename... Args >
  typename AVLTree< Key, Value, Compare >::Iter AVLTree< Key, Value, Compare >::emplace(const Key& k, Args&&... args)
  {
    auto ptr = tree_.emplace(k, std::forward< Args... >(args...));
    balanceAfterInsertion(ptr);
    return Iter(ConstIter(ptr));
  }
  template < typename Key, typename Value, typename Compare >
  void AVLTree< Key, Value, Compare >::erase(const Key& k)
  {
    auto current = tree_.erase(k);
    balanceAfterErasure(current);
  }
  template < typename Key, typename Value, typename Compare >
  typename AVLTree< Key, Value, Compare >::Iter AVLTree< Key, Value, Compare >::erase(Iter pos)
  {
    auto it = pos++;
    auto current = tree_.erase(it);
    balanceAfterErasure(current);
    return pos;
  }
  template < typename Key, typename Value, typename Compare >
  typename AVLTree< Key, Value, Compare >::Iter AVLTree< Key, Value, Compare >::erase(Iter beginIt,Iter endIt)
  {
    auto returnable = endIt;
    if (returnable != end())
    {
      ++returnable;
    }
    auto i = beginIt;
    while (i != endIt)
    {
      i = erase(i);
    }
    return returnable;
  }
  template < typename Key, typename Value, typename Compare >
  void AVLTree< Key, Value, Compare >::balanceAfterInsertion(detail::node_t< Key, Value >* current)
  {
    if (current->left_ || current->right_)
    {
      return;
    }
    while (current->parent_)
    {
      current = current->parent_;
      auto ptr = balance(current);
      if (ptr)
      {
        break;
      }
    }
  }
  template < typename Key, typename Value, typename Compare >
  detail::node_t< Key, Value >* AVLTree< Key, Value, Compare >::balance(detail::node_t< Key, Value >* node)
  {
    int rightHeight = tree_.getNodeHeight(node->right_);
    int leftHeight = tree_.getNodeHeight(node->left_);
    int balanceFactor = rightHeight - leftHeight;
    if ((balanceFactor == 2) && (tree_.getNodeHeight(node->right_->left_) <= tree_.getNodeHeight(node->right_->right_)))
    {
      return tree_.leftRotation(node);
    }
    else if (balanceFactor == 2)
    {
      return rightLeftRotation(node->right_);
    }
    else if ((balanceFactor == -2) && (tree_.getNodeHeight(node->left_->right_) <= tree_.getNodeHeight(node->left_->left_)))
    {
      return tree_.rightRotation(node);
    }
    else if (balanceFactor == -2)
    {
      return leftRightRotation(node->left_);
    }
    return nullptr;
  }
  template < typename Key, typename Value, typename Compare >
  void AVLTree< Key, Value, Compare >::balanceAfterErasure(detail::node_t< Key, Value >* current)
  {
    if (!current)
    {
      return;
    }
    if (current->right_ && current->left_)
    {
      current = tree_.findMin(current->right_);
    }
    while (current)
    {
      auto ptr = balance(current);
      if (ptr)
      {
        break;
      }
      current = current->parent_;
    }
  }
  template < typename Key, typename Value, typename Compare >
  bool AVLTree< Key, Value, Compare >::isEmpty() const noexcept
  {
    return tree_.isEmpty();
  }
  template < typename Key, typename Value, typename Compare >
  typename AVLTree< Key, Value, Compare >::Iter AVLTree< Key, Value, Compare >::find(const Key& k)
  {
    return tree_.itFind(k);
  }
  template < typename Key, typename Value, typename Compare >
  typename AVLTree< Key, Value, Compare >::ConstIter AVLTree< Key, Value, Compare >::cfind(const Key& k) const
  {
    return tree_.constItFind(k);
  }
  template < typename Key, typename Value, typename Compare >
  typename AVLTree< Key, Value, Compare >::Iter AVLTree< Key, Value, Compare >::begin()
  {
    return tree_.begin();
  }
  template < typename Key, typename Value, typename Compare >
  typename AVLTree< Key, Value, Compare >::ConstIter AVLTree< Key, Value, Compare >::begin() const
  {
    return tree_.begin();
  }
  template < typename Key, typename Value, typename Compare >
  typename AVLTree< Key, Value, Compare >::ConstIter AVLTree< Key, Value, Compare >::cbegin() const
  {
    return tree_.cbegin();
  }
  template < typename Key, typename Value, typename Compare >
  typename AVLTree< Key, Value, Compare >::Iter AVLTree< Key, Value, Compare >::end()
  {
    return tree_.end();
  }
  template < typename Key, typename Value, typename Compare >
  typename AVLTree< Key, Value, Compare >::ConstIter AVLTree< Key, Value, Compare >::end() const
  {
    return tree_.end();
  }
  template < typename Key, typename Value, typename Compare >
  typename AVLTree< Key, Value, Compare >::ConstIter AVLTree< Key, Value, Compare >::cend() const
  {
    return tree_.cend();
  }
  template < typename Key, typename Value, typename Compare >
  detail::node_t< Key, Value >* AVLTree< Key, Value, Compare >::rightLeftRotation(detail::node_t< Key, Value >* node)
  {
    if (!node || !node->parent_ || !node->left_)
    {
      return nullptr;
    }
    auto newNode = tree_.rightRotation(node);
    auto returnable = tree_.leftRotation(newNode->parent_);
    return returnable;
  }
  template < typename Key, typename Value, typename Compare >
  detail::node_t< Key, Value >* AVLTree< Key, Value, Compare >::leftRightRotation(detail::node_t< Key, Value >* node)
  {
    if (!node || !node->parent_ || !node->right_)
    {
      return nullptr;
    }
    auto newNode = tree_.leftRotation(node);
    auto returnable = tree_.rightRotation(newNode->parent_);
    return returnable;
  }
  template < typename Key, typename Value, typename Compare >
  typename AVLTree< Key, Value, Compare >::ConstIter AVLTree< Key, Value, Compare >::cupperBound(const Key& k) const
  {
    return tree_.cupperBound(k);
  }
  template < typename Key, typename Value, typename Compare >
  typename AVLTree< Key, Value, Compare >::Iter AVLTree< Key, Value, Compare >::upperBound(const Key& k)
  {
    return tree_.upperBound(k);
  }
  template < typename Key, typename Value, typename Compare >
  typename AVLTree< Key, Value, Compare >::ConstIter AVLTree< Key, Value, Compare >::clowerBound(const Key& k) const
  {
    return tree_.clowerBound(k);
  }
  template < typename Key, typename Value, typename Compare >
  typename AVLTree< Key, Value, Compare >::Iter AVLTree< Key, Value, Compare >::lowerBound(const Key& k)
  {
    return tree_.lowerBound(k);
  }
  template < typename Key, typename Value, typename Compare >
  template < typename F >
  F AVLTree< Key, Value, Compare >::traverse_lnr(F f) const
  {
    return tree_.traverse_lnr(f);
  }
  template < typename Key, typename Value, typename Compare >
  template < typename F >
  F AVLTree< Key, Value, Compare >::traverse_rnl(F f) const
  {
    return tree_.traverse_rnl(f);
  }
  template < typename Key, typename Value, typename Compare >
  template < typename F >
  F AVLTree< Key, Value, Compare >::traverse_breadth(F f) const
  {
    return tree_.traverse_breadth(f);
  }
}

#endif

