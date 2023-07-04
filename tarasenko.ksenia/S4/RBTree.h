#ifndef RBTREE_H
#define RBTREE_H

#include "BinarySearchTree.h"

template< typename Key, typename Value, typename Compare >
class RedBlackTree
{
 using BSTree = BinarySearchTree< Key, Value, Compare >;
 using RBTree = RedBlackTree< Key, Value, Compare >;
public:
 //...
private:
 BSTree* root_;
 BSTree* fakeNode_;
 //...
};

#endif
