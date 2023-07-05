#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <utility>
#include <iostream>
#include "Tree.h"

namespace tarasenko
{
  template< typename Key, typename Value, typename Compare >
  class BinarySearchTree
  {
   using BSTree = BinarySearchTree< Key, Value, Compare >;
   using data_t = std::pair< Key, Value >;
  public:
   BinarySearchTree():
     root_(nullptr)
   {};
   ~BinarySearchTree()
   {
    //...
   }
  private:
   details::Tree< data_t, Compare >* root_;
  };

}

#endif
