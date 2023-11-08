#ifndef TREE_DICT_H
#define TREE_DICT_H

#include <functional>
#include "AVLTree.h"
namespace skarlygina
{
  template < typename Key, typename Value, typename Compare = std::less< Key > >
  class TreeDict
  {
  public:
    using Iter = typename detail::BinSTree< Key, Value, Compare >::TreeIt;
    using ConstIter = typename detail::BinSTree< Key, Value, Compare >::CTreeIt;
    Iter begin();
    ConstIter begin() const;
    ConstIter cbegin() const;
    Iter end();
    ConstIter end() const;
    ConstIter cend() const;
    Iter find(const Key&);
    ConstIter cfind(const Key&) const;
    Iter push(const Key&, const Value&);
    template < typename... Args >
    Iter emplace(const Key&, Args&&...);
    void pop(const Key&);
    Iter pop(Iter);
    Iter pop(Iter, Iter);
    void clear();
    bool isEmpty() const;

    ConstIter cupperBound(const Key&) const;
    Iter upperBound(const Key&);
    ConstIter clowerBound(const Key&) const;
    Iter lowerBound(const Key&);
  private:
    AVLTree< Key, Value, Compare > tree_;
  };
  template < typename Key, typename Value, typename Compare >
  typename  TreeDict< Key, Value, Compare >::Iter TreeDict< Key, Value, Compare >::begin()
  {
    return tree_.begin();
  }
  template < typename Key, typename Value, typename Compare >
  typename  TreeDict< Key, Value, Compare >::ConstIter TreeDict< Key, Value, Compare >::begin() const
  {
    return tree_.begin();
  }
  template < typename Key, typename Value, typename Compare >
  typename  TreeDict< Key, Value, Compare >::ConstIter TreeDict< Key, Value, Compare >::cbegin() const
  {
    return tree_.cbegin();
  }
  template < typename Key, typename Value, typename Compare >
  typename  TreeDict< Key, Value, Compare >::Iter TreeDict< Key, Value, Compare >::end()
  {
    return tree_.end();
  }
  template < typename Key, typename Value, typename Compare >
  typename  TreeDict< Key, Value, Compare >::ConstIter TreeDict< Key, Value, Compare >::end() const
  {
    return tree_.end();
  }
  template < typename Key, typename Value, typename Compare >
  typename  TreeDict< Key, Value, Compare >::ConstIter TreeDict< Key, Value, Compare >::cend() const
  {
    return tree_.cend();
  }
  template < typename Key, typename Value, typename Compare >
  typename  TreeDict< Key, Value, Compare >::Iter TreeDict< Key, Value, Compare >::find(const Key& k)
  {
    return tree_.find(k);
  }
  template < typename Key, typename Value, typename Compare >
  typename  TreeDict< Key, Value, Compare >::ConstIter TreeDict< Key, Value, Compare >::cfind(const Key& k) const
  {
    return tree_.cfind(k);
  }
  template < typename Key, typename Value, typename Compare >
  typename TreeDict< Key, Value, Compare >::Iter TreeDict< Key, Value, Compare >::push(const Key& k, const Value& v)
  {
    return tree_.insert(k, v);
  }
  template < typename Key, typename Value, typename Compare >
  template < typename... Args >
  typename TreeDict< Key, Value, Compare >::Iter TreeDict< Key, Value, Compare >::emplace(const Key& k, Args&&... args)
  {
    return tree_.emplace(k, std::forward< Args... >(args...));
  }
  template < typename Key, typename Value, typename Compare >
  void TreeDict< Key, Value, Compare >::pop(const Key& k)
  {
    tree_.erase(k);
  }
  template < typename Key, typename Value, typename Compare >
  typename TreeDict< Key, Value, Compare >::Iter TreeDict< Key, Value, Compare >::pop(Iter pos)
  {
    return tree_.erase(pos);
  }
  template < typename Key, typename Value, typename Compare >
  typename TreeDict< Key, Value, Compare >::Iter TreeDict< Key, Value, Compare >::pop(Iter begin, Iter end)
  {
    return tree_.erase(begin, end);
  }
  template < typename Key, typename Value, typename Compare >
  void TreeDict< Key, Value, Compare >::clear()
  {
    tree_.clear();
  }
  template < typename Key, typename Value, typename Compare >
  bool TreeDict< Key, Value, Compare >::isEmpty() const
  {
    return tree_.isEmpty();
  }
  template < typename Key, typename Value, typename Compare >
  typename TreeDict< Key, Value, Compare >::ConstIter TreeDict< Key, Value, Compare >::cupperBound(const Key& k) const
  {
    return tree_.cupperBound(k);
  }
  template < typename Key, typename Value, typename Compare >
  typename TreeDict< Key, Value, Compare >::Iter TreeDict< Key, Value, Compare >::upperBound(const Key& k)
  {
    return tree_.upperBound(k);
  }
  template < typename Key, typename Value, typename Compare >
  typename TreeDict< Key, Value, Compare >::ConstIter TreeDict< Key, Value, Compare >::clowerBound(const Key& k) const
  {
    return tree_.clowerBound(k);
  }
  template < typename Key, typename Value, typename Compare >
  typename TreeDict< Key, Value, Compare >::Iter TreeDict< Key, Value, Compare >::lowerBound(const Key& k)
  {
    return tree_.lowerBound(k);
  }
}

#endif

