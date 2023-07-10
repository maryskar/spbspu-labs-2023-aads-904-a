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
     root_(nullptr)
   {}

   ~RedBlackTree()
   {
     delete root_;
   }

   void insert(const T& data);
   void fixInsert(BSTree* node);
   void remove(const T& data);
   void fixRemove();

   friend class BidirectionalIterator< T, Compare >;
   friend class ConstBidirectionalIterator< T, Compare >;

   iterator beforeBegin() const
   {
     return root_->beforeBegin();
   }
   iterator begin() const
   {
     return root_->begin();
   }
   iterator end() const
   {
     return root_->end();
   }

   const_iterator cbeforeBegin() const
   {
     return root_->cbeforeBegin();
   }
   const_iterator cbegin() const
   {
     return root_->cbegin();
   }
   const_iterator cend() const
   {
     return root_->cend();
   }

  private:
   BSTree* root_;
  };

  template< typename T, typename Compare >
  void RedBlackTree< T, Compare >::insert(const T& data)
  {
    //
    fixInsert();
  }

  template< typename T, typename Compare >
  void RedBlackTree< T, Compare >::fixInsert(BSTree* node)
  {
    //...
  }

  template< typename T, typename Compare >
  void RedBlackTree< T, Compare >::remove(const T& data)
  {
    root_->remove(data);
    fixRemove();
  }

  template< typename T, typename Compare >
  void RedBlackTree< T, Compare >::fixRemove()
  {
    //...
  }
}

#endif
