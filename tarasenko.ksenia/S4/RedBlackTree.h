#ifndef RBTREE_H
#define RBTREE_H

#include "Tree.h"
#include "bidirect_iter.h"
#include "const_bidirect_iter.h"
#include "BinarySearchTree.h"

namespace tarasenko
{
  template< typename T, typename Compare >
  class BinarySearchTree;

  template< typename T, typename Compare >
  class RedBlackTree
  {
   using Tree = details::Tree< T, Compare >;
   using BSTree = BinarySearchTree< T, Compare >;
   using RBTree = RedBlackTree< T, Compare >;
   using iterator = BidirectionalIterator< T, Compare >;
   using const_iterator = ConstBidirectionalIterator< T, Compare >;
  public:
   RedBlackTree():
     root_()
   {
     root_.fake_->color_ = 'b';
   }
   ~RedBlackTree() = default;

   std::pair< iterator, bool > insert(const T& data);
   void remove(const T& data);

   friend class BidirectionalIterator< T, Compare >;
   friend class ConstBidirectionalIterator< T, Compare >;

   iterator beforeBegin() const
   {
     return root_.beforeBegin();
   }
   iterator begin() const
   {
     return root_.begin();
   }
   iterator end() const
   {
     return root_.end();
   }

   const_iterator cbeforeBegin() const
   {
     return root_.cbeforeBegin();
   }
   const_iterator cbegin() const
   {
     return root_.cbegin();
   }
   const_iterator cend() const
   {
     return root_.cend();
   }

   std::string printAsString();       //
   std::string printColorAsString(); //

  private:
   BSTree root_;
   void fixInsert(Tree* node);
   void fixRemove(Tree* node);
  };

  template< typename T, typename Compare >
  std::pair< BidirectionalIterator< T, Compare >, bool > RedBlackTree< T, Compare >::insert(const T& data)
  {
    std::pair< iterator, bool > res = root_.insert(data);
    if (res.second)
    {
      auto newNode = res.first.node_;
      newNode->color_ = 'r';
      fixInsert(newNode);
    }
    return res;
  }

  template< typename T, typename Compare >
  void RedBlackTree< T, Compare >::fixInsert(Tree* node)
  {
    auto root = root_.root_;
    auto parent = node->parent_;
    if (parent->color_ == 'b')
    {
      return;
    }
    else if (parent == root)
    {
      parent->color_ = 'b';
    }
    else
    {
      auto grandpa = node->parent_->parent_;
      if (parent == grandpa->left_)
      {
        auto uncle = node->parent_->parent_->right_;
        if (uncle->color_ == 'r')
        {
          parent->color_ = 'b';
          uncle->color_ = 'b';
          grandpa->color_ = 'r';
          fixInsert(grandpa);
        }
        else
        {
          if (node == parent->left_)
          {
            parent->color_ = 'b';
            grandpa->color_ = 'r';
            root_.rightRotation(grandpa);
          }
          else
          {
            root_.leftRotation(parent);
            fixInsert(parent);
          }
        }
      }
      else
      {
        auto uncle = node->parent_->parent_->left_;
        if (uncle->color_ == 'r')
        {
          parent->color_ = 'b';
          uncle->color_ = 'b';
          grandpa->color_ = 'r';
          fixInsert(grandpa);
        }
        else
        {
          if (node == parent->right_)
          {
            parent->color_ = 'b';
            grandpa->color_ = 'r';
            root_.leftRotation(grandpa);
          }
          else
          {
            root_.rightRotation(parent);
            fixInsert(parent);
          }
        }
      }
    }
  }

  template< typename T, typename Compare >
  void RedBlackTree< T, Compare >::remove(const T& data)
  {
    root_.remove(data);
    fixRemove();
  }

  template< typename T, typename Compare >
  void RedBlackTree< T, Compare >::fixRemove(Tree* it)
  {
    //...
  }

//=================================================================
  template< typename T, typename Compare >
  std::string RedBlackTree< T, Compare >::printAsString()
  {
    return root_.printAsString();
  }

  template< typename T, typename Compare >
  std::string RedBlackTree< T, Compare >::printColorAsString()
  {
    auto root = root_.root_;
    if (!root)
    {
      return " ";
    }
    std::string fake_c = root_.fake_->color_ == 'b' ? "b" : "r";
    std::string root_c = root->color_ == 'b' ? "b" : "r";

    std::string left = (root->left_ == root_.fake_) ? "{" + fake_c + "}" : root_.printColorAsString(root->left_);
    std::string right = (root->right_ == root_.fake_) ? "{" + fake_c + "}" : root_.printColorAsString(root->right_);
    return "{" + root_c + ", " + left + ", " + right + "}";
  }
}

#endif
