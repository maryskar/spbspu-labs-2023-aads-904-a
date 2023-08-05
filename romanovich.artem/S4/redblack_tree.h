#ifndef RREDBLACK_TREE_H
#define RREDBLACK_TREE_H
#include "color_tree_node.h"
template< typename T >
class RedBlackTree
{
public:
  RedBlackTree();
  void insert(const T &data);
  void remove(const T &data);
private:
  ColorTreeNode< T > *root_;
  void leftRotate(ColorTreeNode< T > *colorNode);
  void rightRotate(ColorTreeNode< T > *colorNode);
  void balanceAfterInsert(ColorTreeNode< T > *colorNode);
  void balanceAfterRemove(ColorTreeNode< T > *colorNode);
};
template< typename T >
void RedBlackTree< T >::balanceAfterRemove(ColorTreeNode< T > *colorNode)
{
}
template< typename T >
void RedBlackTree< T >::balanceAfterInsert(ColorTreeNode< T > *colorNode)
{
}
template< typename T >
void RedBlackTree< T >::rightRotate(ColorTreeNode< T > *colorNode)
{
}
template< typename T >
void RedBlackTree< T >::leftRotate(ColorTreeNode< T > *colorNode)
{
}
template< typename T >
void RedBlackTree< T >::remove(const T &data)
{
  ColorTreeNode< T > *node = findNode(data);
  //delete
  balanceAfterRemove(node);
}
template< typename T >
void RedBlackTree< T >::insert(const T &data)
{
  auto *newNode = new ColorTreeNode< T >(data);
  //insert
  balanceAfterInsert(newNode);
}
template< typename T >
RedBlackTree< T >::RedBlackTree():
  root_(nullptr)
{
}
#endif
