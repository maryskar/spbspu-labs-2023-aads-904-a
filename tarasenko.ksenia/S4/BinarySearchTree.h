#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <utility>
#include <iostream>
#include "Tree.h"
#include "RedBlackTree.h"

namespace tarasenko
{
  template< typename T, typename Compare >
  class BinarySearchTree
  {
   using BSTree = BinarySearchTree< T, Compare >;
   using root_t = details::Tree< T, Compare >;
  public:
   friend class RedBlackTree< T, Compare >;

   BinarySearchTree():
     fake_(static_cast< root_t* >(::operator new(sizeof(root_t)))),
     root_(nullptr)
   {
     fake_->left_ = fake_;
     fake_->right_ = fake_;
     fake_->parent_ = fake_;
     fake_->color_ = 'b';
   };

   ~BinarySearchTree()
   {
     deleteTree(root_);
     ::operator delete(fake_);
   }

   void insert(const T& data);
   void remove(const T& data);
   void leftRotation();
   void rightRotation();

   root_t* find(const T& data);
   std::string SubTreeAsString();               //
   std::string SubTreeAsString(root_t* ptree); //

  private:
   root_t* fake_;
   root_t* root_;
   root_t* insert(const T& data, root_t* ptree);
   root_t* findMin(root_t* ptree);
   root_t* find(const T& data, root_t* ptree);
   void remove(const T& data, root_t* ptree);
   void deleteTree(root_t* ptree);
   void leftRotation(root_t* ptree);
   void rightRotation(root_t* ptree);
  };

  template< typename T, typename Compare >
  details::Tree< T, Compare >* BinarySearchTree< T, Compare >::insert(const T& data, root_t* ptree)
  {
    auto comp = ptree->compare_;
    if (comp(data, ptree->data_))
    {
      if (ptree->left_ == fake_)
      {
        ptree->left_ = new root_t(data, fake_, fake_, ptree);
      }
      else
      {
        root_t* leftChild = insert(data, ptree->left_);
        ptree->left_ = leftChild;
        leftChild->parent_ = ptree;
      }
    }
    else
    {
      if (ptree->right_ == fake_)
      {
        ptree->right_ = new root_t(data, fake_, fake_, ptree);
      }
      else
      {
        root_t* rightChild = insert(data, ptree->right_);
        ptree->right_ = rightChild;
        rightChild->parent_ = ptree;
      }
    }
    return ptree;
  }

  template< typename T, typename Compare >
  void BinarySearchTree< T, Compare >::insert(const T& data)
  {
    if (!root_)
    {
      root_ = new root_t(data, fake_, fake_, fake_);
    }
    else
    {
      insert(data, root_);
    }
  }

  template< typename T, typename Compare >
  void BinarySearchTree< T, Compare >::leftRotation(root_t* ptree)
  {
    auto rightChild = ptree->right_;
    ptree->right_ = rightChild->left_;
    if (rightChild->left_ != fake_)
    {
      rightChild->left_->parent_ = ptree;
    }
    rightChild->parent_ = ptree->parent_;
    if (ptree->parent_ == fake_)
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

  template< typename T, typename Compare >
  void BinarySearchTree< T, Compare >::rightRotation(root_t* ptree)
  {
    auto leftChild = ptree->left_;
    ptree->left_ = leftChild->right_;
    if (leftChild->right_ != fake_)
    {
      leftChild->right_->parent_ = ptree;
    }
    leftChild->parent_ = ptree->parent_;
    if (ptree->parent_ == fake_)
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

  template< typename T, typename Compare >
  void BinarySearchTree< T, Compare >::leftRotation()
  {
    leftRotation(root_);
  }

  template< typename T, typename Compare >
  void BinarySearchTree< T, Compare >::rightRotation()
  {
    rightRotation(root_);
  }

  template< typename T, typename Compare >
  void BinarySearchTree< T, Compare >::remove(const T& data)
  {
    remove(data, root_);
  }

  template< typename T, typename Compare >
  void BinarySearchTree< T, Compare >::deleteTree(root_t* ptree)
  {
    if (ptree != fake_)
    {
      deleteTree(ptree->left_);
      deleteTree(ptree->right_);
      delete ptree;
    }
  }

  template< typename T, typename Compare >
  details::Tree< T, Compare >* BinarySearchTree< T, Compare >::find(const T& data, root_t* ptree)
  {
    auto comp = ptree->compare_;
    if (ptree == fake_ || ptree->data_ == data)
    {
      return ptree;
    }
    if (comp(data, ptree->data_))
    {
      return find(data, ptree->left_);
    }
    return find(data, ptree->right_);
  }

  template< typename T, typename Compare >
  details::Tree< T, Compare >* BinarySearchTree< T, Compare >::find(const T& data)
  {
    find(data, root_);
  }

  template< typename T, typename Compare >
  details::Tree< T, Compare >* BinarySearchTree< T, Compare >::findMin(root_t* ptree)
  {
    if (ptree == fake_)
    {
      return fake_;
    }
    else if (ptree->left_ == fake_)
    {
      return ptree;
    }
    else
    {
      return findMin(ptree->left_);
    }
  }

  template< typename T, typename Compare >
  void BinarySearchTree< T, Compare >::remove(const T& data, root_t* ptree)
  {
    auto toDelete = find(data, ptree);
    if (toDelete == fake_)
    {
      return;
    }
    else if (toDelete->left_ != fake_ && toDelete->right_ != fake_)
    {
      auto replaceNode = findMin(toDelete->right_);
      toDelete->data_ = replaceNode->data_;
      remove(replaceNode->data_, replaceNode);
      return;
    }
    else
    {
      auto child = toDelete->left_ != fake_ ? toDelete->left_ : toDelete->right_;
      if (toDelete->parent_ != fake_)
      {
        if (toDelete->parent_->left_ == toDelete)
        {
          toDelete->parent_->left_ = child;
        }
        else
        {
          toDelete->parent_->right_ = child;
        }
        if (toDelete->left_ != fake_ || toDelete->right_ != fake_)
        {
          child->parent_ = toDelete->parent_;
        }
      }
      delete toDelete;
    }
  }


  //==============================================

  template< typename T, typename Compare >
  std::string BinarySearchTree< T, Compare >::SubTreeAsString(root_t* ptree)
  {
    std::string left = (ptree->left_ == fake_) ? "{}" : SubTreeAsString(ptree->left_);
    std::string right = (ptree->right_ == fake_) ? "{}" : SubTreeAsString(ptree->right_);
    std::string res = "{" + std::to_string(ptree->data_) + ", " + left + ", " + right + "}";
    return res;
  }

  template< typename T, typename Compare >
  std::string BinarySearchTree< T, Compare >::SubTreeAsString()
  {
    std::string left = (root_->left_ == fake_) ? "{}" : SubTreeAsString(root_->left_);
    std::string right = (root_->right_ == fake_) ? "{}" : SubTreeAsString(root_->right_);
    std::string res = "{" + std::to_string(root_->data_) + ", " + left + ", " + right + "}";
    return res;
  }
}

#endif
