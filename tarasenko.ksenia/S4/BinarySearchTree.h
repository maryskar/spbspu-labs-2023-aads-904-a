#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <utility>
#include "Tree.h"
#include "bidirect_iter.h"
#include "const_bidirect_iter.h"
#include "RedBlackTree.h"

namespace tarasenko
{
  template< typename T, typename Compare >
  class BinarySearchTree
  {
   using BSTree = BinarySearchTree< T, Compare >;
   using root_t = details::Tree< T, Compare >;
   using iterator = BidirectionalIterator< T, Compare >;
   using const_iterator = ConstBidirectionalIterator< T, Compare >;
  public:
   friend class RedBlackTree< T, Compare >;

   BinarySearchTree():
     fake_(static_cast< root_t* >(::operator new(sizeof(root_t)))),
     root_(nullptr),
     begin_(nullptr),
     end_(nullptr)
   {
     fake_->left_ = fake_;
     fake_->right_ = fake_;
     fake_->parent_ = fake_;
     fake_->color_ = 'b';
   };

   ~BinarySearchTree()
   {
     clear();
     ::operator delete(fake_);
   }

   std::pair< iterator, bool > insert(const T& data);
   void remove(const T& data);
   const_iterator find(const T& data);
   void clear();
   void leftRotation();
   void rightRotation();

   std::string SubTreeAsString();               //
   std::string SubTreeAsString(root_t* ptree); //

   friend class BidirectionalIterator< T, Compare >;
   friend class ConstBidirectionalIterator< T, Compare >;

   iterator beforeBegin() const
   {
     return begin_ ? iterator(fake_, begin_->left_) : iterator(fake_, begin_);
   }
   iterator begin() const
   {
     return iterator(fake_, begin_);
   }
   iterator end() const
   {
     return end_ ? iterator(fake_, end_->right_) : iterator(fake_, end_);
   }

   const_iterator cbeforeBegin() const
   {
     return begin_ ? iterator(fake_, begin_->left_) : iterator(fake_, begin_);
   }
   const_iterator cbegin() const
   {
     return iterator(fake_, begin_);
   }
   const_iterator cend() const
   {
     return end_ ? iterator(fake_, end_->right_) : iterator(fake_, end_);
   }

  private:
   root_t* fake_;
   root_t* root_;
   root_t* begin_;
   root_t* end_;
   std::pair< iterator, iterator > insert(const T& data, iterator ptree);
   const_iterator findMin(const_iterator ptree);
   const_iterator find(const T& data, const_iterator ptree);
   void remove(const T& data, iterator ptree);
   void deleteTree(root_t* ptree);
   void leftRotation(root_t* ptree);
   void rightRotation(root_t* ptree);
  };

  template< typename T, typename Compare >
  std::pair< BidirectionalIterator< T, Compare >, BidirectionalIterator< T, Compare > >
     BinarySearchTree< T, Compare >::insert(const T& data, iterator it)
  {
    auto inserted = end();
    auto node = it.node_;
    auto comp = node->compare_;
    if (comp(data, *it))
    {
      if (node->left_ == fake_)
      {
        node->left_ = new root_t(data, fake_, fake_, node);
        inserted = iterator(fake_, node->left_);
      }
      else
      {
        auto res = insert(data, iterator(fake_, node->left_));
        node->left_ = res.first.node_;
        res.first.node_->parent_ = node;
        inserted = res.second;
      }
    }
    else if (comp(*it, data))
    {
      if (node->right_ == fake_)
      {
        node->right_ = new root_t(data, fake_, fake_, node);
        inserted = iterator(fake_, node->right_);
      }
      else
      {
        auto res = insert(data, iterator(fake_, node->right_));
        node->right_ = res.first.node_;
        res.first.node_->parent_ = node;
        inserted = res.second;
      }
    }
    return std::make_pair(it, inserted);
  }

  template< typename T, typename Compare >
  std::pair< BidirectionalIterator< T, Compare >, bool > BinarySearchTree< T, Compare >::insert(const T& data)
  {
    if (!root_)
    {
      root_ = new root_t(data, fake_, fake_, fake_);
      root_->parent_->right_ = root_;
      root_->parent_->left_ = root_;
      begin_ = root_;
      end_ = root_;
      return std::make_pair(iterator(fake_, root_), true);
    }
    else
    {
      auto inserted = insert(data, iterator(fake_, root_)).second.node_;
      if (inserted != fake_)
      {
        if (data < begin_->data_)
        {
          begin_ = inserted;
        }
        if (end_->data_ < data)
        {
          end_ = inserted;
        }
        return std::make_pair(iterator(fake_, inserted), true);
      }
      return std::make_pair(end(), false);
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
    if (root_)
    {
      leftRotation(root_);
    }
  }

  template< typename T, typename Compare >
  void BinarySearchTree< T, Compare >::rightRotation()
  {
    if (root_)
    {
      rightRotation(root_);
    }
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
  void BinarySearchTree< T, Compare >::clear()
  {
    if (root_)
    {
      deleteTree(root_);
      root_ = nullptr;
      begin_ = nullptr;
      end_ = nullptr;
    }
  }

  template< typename T, typename Compare >
  ConstBidirectionalIterator< T, Compare > BinarySearchTree< T, Compare >::find(const T& data, const_iterator it)
  {
    auto comp = it.node_->compare_;
    if (it.node_ == fake_)
    {
      return cend();
    }
    if (*it == data)
    {
      return it;
    }
    if (comp(data, *it))
    {
      return find(data, const_iterator(fake_, it.node_->left_));
    }
    return find(data, const_iterator(fake_, it.node_->right_));
  }

  template< typename T, typename Compare >
  ConstBidirectionalIterator< T, Compare > BinarySearchTree< T, Compare >::find(const T& data)
  {
    auto c_it = const_iterator(fake_, root_);
    return root_ ? find(data, c_it) : cend();
  }

  template< typename T, typename Compare >
  ConstBidirectionalIterator< T, Compare > BinarySearchTree< T, Compare >::findMin(const_iterator it)
  {
    if (it.node_ == fake_)
    {
      return cend();
    }
    else if (it.node_->left_ == fake_)
    {
      return it;
    }
    else
    {
      return findMin(const_iterator(fake_, it.node_->left_));
    }
  }

  template< typename T, typename Compare >
  void BinarySearchTree< T, Compare >::remove(const T& data, iterator it)
  {
    auto toDelIt = find(data, it);

    auto nodeToDel = toDelIt.node_;
    auto left = nodeToDel->left_;
    auto right = nodeToDel->right_;
    auto parent = nodeToDel->parent_;

    if (toDelIt == cend())
    {
      return;
    }
    else if (left != fake_ && right != fake_)
    {
      auto replaceNodeIt = findMin(const_iterator(fake_, right));
      nodeToDel->data_ = *replaceNodeIt;
      remove(*replaceNodeIt, iterator(fake_, replaceNodeIt.node_));
      return;
    }
    else
    {
      auto child = left != fake_ ? left : right;
      if (parent != fake_)
      {
        if (parent->left_ == nodeToDel)
        {
          parent->left_ = child;
        }
        else
        {
          parent->right_ = child;
        }
        if (left != fake_ || right != fake_)
        {
          child->parent_ = parent;
        }
      }
      if (nodeToDel == end_)
      {
        end_ = left != fake_ ? left : parent;
      }
      else if (nodeToDel == begin_)
      {
        begin_ = right != fake_ ? right : parent;
      }
      delete nodeToDel;
    }
  }

  template< typename T, typename Compare >
  void BinarySearchTree< T, Compare >::remove(const T& data)
  {
    auto it = iterator(fake_, root_);
    remove(data, it);
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
    if (!root_)
    {
      return " ";
    }
    std::string left = (root_->left_ == fake_) ? "{}" : SubTreeAsString(root_->left_);
    std::string right = (root_->right_ == fake_) ? "{}" : SubTreeAsString(root_->right_);
    return "{" + std::to_string(root_->data_) + ", " + left + ", " + right + "}";
  }
}

#endif
