#ifndef S4_TREE_HPP
#define S4_TREE_HPP
#include <functional>

namespace chemodurov
{
  template< typename T, typename Compare = std::less< > >
  struct Tree
  {
    T data_;
    Tree< T, Compare > * left_;
    Tree< T, Compare > * right_;
    Tree< T, Compare > * parent_;
    char color_;
  };

  template< typename T, typename Compare = std::less< > >
  Tree< T, Compare > * left(Tree< T, Compare > * node)
  {
    return node->left_;
  }

  template< typename T, typename Compare = std::less< > >
  Tree< T, Compare > * right(Tree< T, Compare > * node)
  {
    return node->right_;
  }

  template< typename T, typename Compare = std::less< > >
  Tree< T, Compare > * parent(Tree< T, Compare > * node)
  {
    return node->parent_;
  }

  template< typename T, typename Compare = std::less< > >
  void setLeft(Tree< T, Compare > * node, Tree< T, Compare > * to_set)
  {
    node->left_ = to_set;
  }

  template< typename T, typename Compare = std::less< > >
  void setRight(Tree< T, Compare > * node, Tree< T, Compare > * to_set)
  {
    node->right_ = to_set;
  }

  template< typename T, typename Compare = std::less< > >
  void setParent(Tree< T, Compare > * node, Tree< T, Compare > * to_set)
  {
    node->parent_ = to_set;
  }

}

#endif
