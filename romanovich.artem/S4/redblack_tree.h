#ifndef RREDBLACK_TREE_H
#define RREDBLACK_TREE_H
//#include "color_tree_node.h"
#include "rotatable_binary_search_tree.h"
namespace romanovich
{
  template< typename Key, typename Value, typename Compare = std::less<> >
  class RedBlackTree
  {
  public:
    using data_type = std::pair< Key, Value >;
    RedBlackTree();
    void insert(const data_type &data);
    void remove(const data_type &data);
  private:
    //ColorTreeNode< data_type > *root_;
    //void leftRotate(ColorTreeNode< data_type > *colorNode);
    //void rightRotate(ColorTreeNode< data_type > *colorNode);
    //void balanceAfterInsert(ColorTreeNode< data_type > *colorNode);
    //void balanceAfterRemove(ColorTreeNode< data_type > *colorNode);
  };
/*template< typename Key, typename Value, typename Compare >
void RedBlackTree< Key, Value, Compare >::balanceAfterRemove(ColorTreeNode< data_type > *colorNode)
{
}
template< typename Key, typename Value, typename Compare >
void RedBlackTree< Key, Value, Compare >::balanceAfterInsert(ColorTreeNode< data_type > *colorNode)
{
}
template< typename Key, typename Value, typename Compare >
void RedBlackTree< Key, Value, Compare >::rightRotate(ColorTreeNode< data_type > *colorNode)
{
}
template< typename Key, typename Value, typename Compare >
void RedBlackTree< Key, Value, Compare >::leftRotate(ColorTreeNode< data_type > *colorNode)
{
}
template< typename Key, typename Value, typename Compare >
void RedBlackTree< Key, Value, Compare >::remove(const data_type &data)
{
  ColorTreeNode< data_type > *node = findNode(data);
  //delete
  balanceAfterRemove(node);
}
template< typename Key, typename Value, typename Compare >
void RedBlackTree< Key, Value, Compare >::insert(const data_type &data)
{
  auto *newNode = new ColorTreeNode< data_type >(data);
  //insert
  balanceAfterInsert(newNode);
}
template< typename Key, typename Value, typename Compare >
RedBlackTree< Key, Value, Compare >::RedBlackTree():
  root_(nullptr)
{
}}*/
}
#endif
