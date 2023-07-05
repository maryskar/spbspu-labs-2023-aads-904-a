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
   using root_t = details::Tree< data_t, Compare >;
  public:
   BinarySearchTree():
     root_(nullptr)
   {};

   ~BinarySearchTree()
   {
     details::deleteTree(root_);
   }

   void insert(const data_t& data);
   void leftRotation(root_t* ptree);
   void rightRotation(root_t* ptree);

  private:
   root_t* root_;
  };

  template< typename Key, typename Value, typename Compare >
  void BinarySearchTree< Key, Value, Compare >::insert(const data_t& data)
  {
    if (!root_)
    {
      root_ = new root_t;
      root_->data_ = data;
    }
    else
    {
      details::insert(data, root_);
    }
  }
}

#endif
