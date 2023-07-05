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
   void leftRotation();
   void rightRotation();
   void remove(const data_t& data);

  private:
   root_t* root_;
   void leftRotation(root_t* ptree);
   void rightRotation(root_t* ptree);
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

  template< typename Key, typename Value, typename Compare >
  void BinarySearchTree< Key, Value, Compare >::leftRotation(root_t* ptree)
  {
    auto rightChild = ptree->right_;
    ptree->right_ = rightChild->left_;
    if (rightChild->left_)
    {
      rightChild->left_->parent_ = ptree;
    }
    rightChild->parent_ = ptree->parent_;
    if (!ptree->parent_)
    {
      root_ = rightChild;
    }
    else if (ptree == ptree->parent_->left_)
    {
      ptree->parent_->left_ = rightChild;
    }
    else
    {
      ptree->parent_->right_ = rightChild;
    }
    rightChild->left_ = ptree;
    ptree->parent_ = rightChild;
  }

  template< typename Key, typename Value, typename Compare >
  void BinarySearchTree< Key, Value, Compare >::rightRotation(root_t* ptree)
  {
    auto leftChild = ptree->left_;
    ptree->left_ = leftChild->right_;
    if (leftChild->right_)
    {
      leftChild->right_->parent_ = ptree;
    }
    leftChild->parent_ = ptree->parent_;
    if (!ptree->parent_)
    {
      root_ = leftChild;
    }
    else if (ptree == ptree->parent_->left_)
    {
      ptree->parent_->left_ = leftChild;
    }
    else
    {
      ptree->parent_->right_ = leftChild;
    }
    leftChild->right_ = ptree;
    ptree->parent_ = leftChild;
  }

  template< typename Key, typename Value, typename Compare >
  void BinarySearchTree< Key, Value, Compare >::leftRotation()
  {
    leftRotation(root_);
  }

  template< typename Key, typename Value, typename Compare >
  void BinarySearchTree< Key, Value, Compare >::rightRotation()
  {
    rightRotation(root_);
  }

  template< typename Key, typename Value, typename Compare >
  void BinarySearchTree< Key, Value, Compare >::remove(const data_t& data)
  {
    details::remove(data, root_);
  }
}

#endif
