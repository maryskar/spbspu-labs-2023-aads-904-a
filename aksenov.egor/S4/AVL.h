#ifndef AVL_H
#define AVL_H
#include <functional>
#include <iostream>
#include "bidirectionalIterator.h"
#include "constBidirectionalIterator.h"
#include "nonBalancedBinarySearchTree.h"
#include "tree.h"

namespace aksenov
{
  template< class Key, class T, class Compare = std::less< > >
  class AVL
  {
  public:
    using Element = std::pair< Key, T >;
    using mappedType = T;
    using Iter = BidirectionalIterator< Element >;
    using CIter = ConstBidirectionalIterator< Element >;

    friend class BidirectionalIterator< Element >;
    friend class ConstBidirectionalIterator< Element >;

    Iter begin();
    CIter begin() const;
    CIter cbegin() const;
    Iter end();
    CIter end() const;
    CIter cend() const;
    Iter insert(const Element &element);

    template< class P >
    std::pair< Iter, bool > insert(P &&value);

    Iter insert(CIter it, const Element &value);

    template< class InputIterator >
    void insert(InputIterator first, InputIterator last);

    template< class P >
    Iter insert(CIter it, P &&value);

    Iter insert(Iter iter, const Element &element);

    template< class... Args >
    std::pair< Iter, bool > emplace(Args &&...args);

    template< typename... Args >
    Iter emplaceHint(CIter hint, Args &&...args);

    Iter erase(Iter it);

    Iter erase(const Key &key);

    CIter find(const Key &key) const;

    Iter find(const Key &key);

    Iter lower_bound(const Key &key);

    CIter lower_bound(const Key &key) const;

    Iter upper_bound(const Key &key);

    CIter upper_bound(const Key &key) const;

    AVL() = default;

    ~AVL() = default;

    AVL(const AVL &other) = default;

    AVL(AVL &&other) = default;

    AVL &operator=(const AVL &other) = default;

    AVL &operator=(AVL &&other) = default;

    mappedType &operator[](const Key &key);

    mappedType &operator[](Key &&key);

    mappedType &at(const Key &key);

    const mappedType &at(const Key &key) const;

    size_t count(const Key &key) const;

    bool contains(const Key &key) const;

    void insert(const Key &key, const T &value);

    bool isEmpty() const;

    void swap(AVL &other) noexcept;

    void clear();

    template < typename F >
    F traverse_lnr(F f) const;
    template < typename F >
    F traverse_rnl(F f) const;
    template < typename F >
    F traverse_breadth(F f) const;
  private:
    BST< Key, T, Compare > data_;
    void balance(Iter toBalance);
  };

  template< class Key, class T, class Compare >
  typename AVL< Key, T, Compare >::Iter AVL< Key, T, Compare >::insert(const Element &element)
  {

  }

  template< class Key, class T, class Compare >
  void AVL< Key, T, Compare >::clear()
  {
    data_.clear();
  }

  template< class Key, class T, class Compare >
  void AVL< Key, T, Compare >::swap(AVL &other) noexcept
  {
    data_.swap(other);
  }

  template< class Key, class T, class Compare >
  bool AVL< Key, T, Compare >::isEmpty() const
  {
    return data_.isEmpty();
  }

  template< class Key, class T, class Compare >
  bool AVL< Key, T, Compare >::contains(const Key &key) const
  {
    return data_.contains(key);
  }

  template< class Key, class T, class Compare >
  size_t AVL< Key, T, Compare >::count(const Key &key) const
  {
    return data_.count(key);
  }

  template< class Key, class T, class Compare >
  typename AVL< Key, T, Compare >::CIter AVL< Key, T, Compare >::upper_bound(const Key &key) const
  {
    return data_.upper_bound(key);
  }

  template< class Key, class T, class Compare >
  typename AVL< Key, T, Compare >::Iter AVL< Key, T, Compare >::upper_bound(const Key &key)
  {
    return data_.upper_bound(key);
  }

  template< class Key, class T, class Compare >
  typename AVL< Key, T, Compare >::CIter AVL< Key, T, Compare >::lower_bound(const Key &key) const
  {
    return data_.lower_bound(key);
  }

  template< class Key, class T, class Compare >
  typename AVL< Key, T, Compare >::Iter AVL< Key, T, Compare >::lower_bound(const Key &key)
  {
    return data_.lower_bound(key);
  }

  template< class Key, class T, class Compare >
  typename AVL< Key, T, Compare >::Iter AVL< Key, T, Compare >::find(const Key &key)
  {
    return data_.find(key);
  }

  template< class Key, class T, class Compare >
  typename AVL< Key, T, Compare >::CIter AVL< Key, T, Compare >::find(const Key &key) const
  {
    return data_.find(key);
  }

  template< class Key, class T, class Compare >
  template< typename... Args >
  typename AVL< Key, T, Compare >::Iter AVL< Key, T, Compare >::emplaceHint(CIter hint, Args &&... args)
  {
    return data_.emplaceHint(hint, std::forward< Args >(args)...);
  }

  template< class Key, class T, class Compare >
  template< class... Args >
  std::pair< typename AVL< Key, T, Compare >::Iter, bool > AVL< Key, T, Compare >::emplace(Args &&... args)
  {
    return data_.emplace(std::forward< Args >(args)...);
  }

  template< class Key, class T, class Compare >
  void AVL< Key, T, Compare >::balance(AVL::Iter toBalance)
  {
    node_t< std::pair< Key, T> >* NodeToBalance = toBalance.iter_.node_;
    if (!NodeToBalance)
    {
      return;
    }
    if (data_.getDiff(NodeToBalance) > 1)
    {
      if (data_.getDiff(NodeToBalance) < 0)
      {
        NodeToBalance->right_ = data_.rotateRight(NodeToBalance->right_);
      }
      NodeToBalance = data_.rotateLeft(NodeToBalance);
    }
    if (data_.getDiff(NodeToBalance) < -1)
    {
      if (data_.getDiff(NodeToBalance) > 0)
      {
        NodeToBalance->left_ = data_.rotateLeft(NodeToBalance->left_);
      }
      NodeToBalance = data_.rotateRight(NodeToBalance);
    }
    data_.fixHeight(NodeToBalance);
    toBalance.iter_.node_ = NodeToBalance;
    Iter nextIter(NodeToBalance->parent_);
    balance(nextIter);
  }

  template< class Key, class T, class Compare >
  template< typename F >
  F AVL< Key, T, Compare >::traverse_breadth(F f) const
  {
    return data_.traverse_breadth();
  }

  template< class Key, class T, class Compare >
  template< typename F >
  F AVL< Key, T, Compare >::traverse_rnl(F f) const
  {
    return data_.traverse_rnl();
  }

  template< class Key, class T, class Compare >
  template< typename F >
  F AVL< Key, T, Compare >::traverse_lnr(F f) const
  {
    return data_.traverse_lnr(f);
  }

  template< class Key, class T, class Compare >
  typename AVL< Key, T, Compare >::Iter AVL< Key, T, Compare >::begin()
  {
    return data_.begin();
  }

  template< class Key, class T, class Compare >
  typename AVL< Key, T, Compare >::CIter AVL< Key, T, Compare >::begin() const
  {
    return data_.begin();
  }

  template< class Key, class T, class Compare >
  typename AVL< Key, T, Compare >::CIter AVL< Key, T, Compare >::cbegin() const
  {
    return data_.cbegin();
  }

  template< class Key, class T, class Compare >
  typename AVL< Key, T, Compare >::Iter AVL< Key, T, Compare >::end()
  {
    return data_.end();
  }

  template< class Key, class T, class Compare >
  typename AVL< Key, T, Compare >::CIter AVL< Key, T, Compare >::end() const
  {
    return data_.end();
  }

  template< class Key, class T, class Compare >
  typename AVL< Key, T, Compare >::CIter AVL< Key, T, Compare >::cend() const
  {
    return data_.end();
  }


}
#endif
