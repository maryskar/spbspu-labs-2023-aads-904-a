#ifndef RBTREE_H
#define RBTREE_H

#include "BinarySearchTree.h"

namespace tarasenko
{
  template< typename Key, typename Value, typename Compare >
  class RedBlackTree
  {
   using BSTree = BinarySearchTree< Key, Value, Compare >;
   using RBTree = RedBlackTree< Key, Value, Compare >;
  public:
   //...
// ~RedBlackTree()
// {
//   clear();
//   ::operator delete(fakeNode_);
// }
  private:
   BSTree* root_;
   BSTree* fakeNode_;
   //...
  };
}

#endif
