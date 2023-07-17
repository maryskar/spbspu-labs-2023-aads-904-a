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
//   RedBlackTree(const RBTree& other)
//   {}
//   RedBlackTree(RBTree&& other)
//   {}
//   explicit RedBlackTree(const Compare& comp)
//   {}
//   template< typename InputIt >
//   RedBlackTree(InputIt first, InputIt last, const Compare& comp = Compare())
//   {}
   ~RedBlackTree() = default;

   //RBTree& operator=(const RBTree& other);
//   RBTree& operator=(RBTree&& other);

   friend class BidirectionalIterator< T, Compare >;
   iterator beforeBegin() const;
   iterator begin() const;
   iterator end() const;
   friend class ConstBidirectionalIterator< T, Compare >;
   const_iterator cbeforeBegin() const;
   const_iterator cbegin() const;
   const_iterator cend() const;
   T& at(const T& data);
   const T& at(const T& data) const;
   T& operator[](const T& data);
   T& operator[](T&& data);
   size_t size() const;
   bool isEmpty() const;
   std::pair< iterator, bool > insert(const T& data);
   std::pair< iterator, bool > insert(T&& data);
   iterator insert(const_iterator pos, const T& data);
   iterator insert(const_iterator pos, T&& data);
   const_iterator find(const T& data) const;
   iterator find(const T& data);
   iterator erase(iterator pos);
   iterator erase(const_iterator pos);
   iterator erase(const_iterator first, const_iterator last);
   size_t erase(const T& data);
   size_t count(const T& data) const;
   void swap(RBTree& other);
   void clear();
   iterator lower_bound(const T& data);
   const_iterator lower_bound(const T& data) const;
   iterator upper_bound(const T& data);
   const_iterator upper_bound(const T& data) const;
   Compare value_comp() const;
   bool isEqualTo(const RBTree& rhs) const;

   std::string printAsString();       //
   std::string printColorAsString(); //

  private:
   BSTree root_;
   void fixAfterInsert(Tree* node);
   Tree* fixBeforeErase(Tree* node);
  };

  template< typename T, typename Compare >
  BidirectionalIterator< T, Compare > RedBlackTree< T, Compare >::beforeBegin() const
  {
    return root_.beforeBegin();
  }

  template< typename T, typename Compare >
  BidirectionalIterator< T, Compare > RedBlackTree< T, Compare >::begin() const
  {
    return root_.begin();
  }

  template< typename T, typename Compare >
  BidirectionalIterator< T, Compare > RedBlackTree< T, Compare >::end() const
  {
    return root_.end();
  }

  template< typename T, typename Compare >
  ConstBidirectionalIterator< T, Compare > RedBlackTree< T, Compare >::cbeforeBegin() const
  {
    return root_.cbeforeBegin();
  }

  template< typename T, typename Compare >
  ConstBidirectionalIterator< T, Compare > RedBlackTree< T, Compare >::cbegin() const
  {
    return root_.cbegin();
  }

  template< typename T, typename Compare >
  ConstBidirectionalIterator< T, Compare > RedBlackTree< T, Compare >::cend() const
  {
    return root_.cend();
  }

  template< typename T, typename Compare >
  const T& RedBlackTree< T, Compare >::at(const T& data) const
  {
    return root_.at(data);
  }

  template< typename T, typename Compare >
  T& RedBlackTree< T, Compare >::at(const T& data)
  {
    return root_.at(data);
  }

  template< typename T, typename Compare >
  T& RedBlackTree< T, Compare >::operator[](const T& data)
  {
    iterator it = find(data);
    return *it;
  }

  template< typename T, typename Compare >
  T& RedBlackTree< T, Compare >::operator[](T&& data)
  {
    return (*this)[data];
  }

  template< typename T, typename Compare >
  size_t RedBlackTree< T, Compare >::size() const
  {
    return root_.size();
  }

  template< typename T, typename Compare >
  bool RedBlackTree< T, Compare >::isEmpty() const
  {
    return root_.isEmpty();
  }

  template< typename T, typename Compare >
  std::pair< BidirectionalIterator< T, Compare >, bool > RedBlackTree< T, Compare >::insert(const T& data)
  {
    std::pair< iterator, bool > res = root_.insert(data);
    if (res.second)
    {
      auto newNode = res.first.node_;
      newNode->color_ = 'r';
      fixAfterInsert(newNode);
    }
    return res;
  }

  template< typename T, typename Compare >
  std::pair< BidirectionalIterator< T, Compare >, bool > RedBlackTree< T, Compare >::insert(T&& data)
  {
    const T value = std::forward< T >(data);
    return insert(value);
  }

  template< typename T, typename Compare >
  BidirectionalIterator< T, Compare > RedBlackTree< T, Compare >::insert(const_iterator pos, const T& data)
  {
    iterator res = root_.insert(pos, data);
    if (res != end())
    {
      res.node_->color_ = 'r';
      fixAfterInsert(res.node_);
    }
    return res;
  }

  template< typename T, typename Compare >
  BidirectionalIterator< T, Compare > RedBlackTree< T, Compare >::insert(const_iterator pos, T&& data)
  {
    const T value = std::forward< T >(data);
    return insert(pos, value);
  }

  template< typename T, typename Compare >
  void RedBlackTree< T, Compare >::fixAfterInsert(Tree* node)
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
          fixAfterInsert(grandpa);
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
            fixAfterInsert(parent);
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
          fixAfterInsert(grandpa);
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
            fixAfterInsert(parent);
          }
        }
      }
    }
  }

  template< typename T, typename Compare >
  ConstBidirectionalIterator< T, Compare > RedBlackTree< T, Compare >::find(const T& data) const
  {
    return root_.find(data);
  }

  template< typename T, typename Compare >
  BidirectionalIterator< T, Compare > RedBlackTree< T, Compare >::find(const T& data)
  {
    return root_.find(data);
  }

  template< typename T, typename Compare >
  BidirectionalIterator< T, Compare > RedBlackTree< T, Compare >::erase(const_iterator pos)
  {
    auto fake = root_.fake_;
    iterator deletedIt = iterator(fake, pos.node_);
    Tree* deleted = deletedIt.node_;
    ++deletedIt;
    auto replacingIt = root_.findMax(const_iterator(fake, deleted->left_));
    Tree* toDel = deleted;
    if (replacingIt != cend())
    {
      std::swap(deleted->data_, *replacingIt);
      toDel = fixBeforeErase(replacingIt.node_);
    }
    else
    {
      toDel = fixBeforeErase(toDel);
    }
    root_.erase(const_iterator(fake, toDel));
    return deletedIt;
  }

  template< typename T, typename Compare >
  BidirectionalIterator< T, Compare > RedBlackTree< T, Compare >::erase(iterator pos)
  {
    return erase(const_iterator(pos));
  }

  template< typename T, typename Compare >
  BidirectionalIterator< T, Compare > RedBlackTree< T, Compare >::erase(const_iterator first, const_iterator last)
  {
    while (first != last)
    {
      erase(first++);
    }
    return iterator(root_.fake_, first.node_);
  }

  template< typename T, typename Compare >
  size_t RedBlackTree< T, Compare >::erase(const T& data)
  {
    const_iterator c_it = find(data);
    if (c_it != cend())
    {
      erase(c_it);
      return 1ull;
    }
    return 0ull;
  }

  template< typename T, typename Compare >
  details::Tree< T, Compare >* RedBlackTree< T, Compare >::fixBeforeErase(Tree* toDel)
  {
    auto fake = root_.fake_;
    auto root = root_.root_;
    if (toDel->color_ == 'r' || toDel == fake)
    {
      return toDel;
    }
    else
    {
      auto l_child = toDel->left_;
      auto r_child = toDel->right_;
      if ((l_child != fake && r_child != fake) || (l_child->color_ == 'b' && r_child->color_ == 'b'))
      {
        auto parent = toDel->parent_;
        if (toDel == root)
        {
          return toDel;
        }
        if (toDel == parent->left_)
        {
          auto brother = parent->right_;
          auto out_nephew = brother->right_;
          auto in_nephew = brother->left_;
          if (out_nephew != fake && out_nephew->color_ == 'r')
          {
            parent->color_ = 'b';
            out_nephew->color_ = 'b';
            root_.leftRotation(parent);
          }
          else if (in_nephew != fake && in_nephew->color_ == 'r')
          {
            in_nephew->color_ = 'b';
            brother->color_ = 'r';
            root_.rightRotation(brother);
            toDel = fixBeforeErase(toDel);
          }
          else if (parent->color_ == 'r')
          {
            parent->color_ = 'b';
            brother->color_ = 'r';
          }
          else if (brother->color_ == 'r')
          {
            parent->color_ = 'r';
            brother->color_ = 'b';
            root_.leftRotation(parent);
            toDel = fixBeforeErase(toDel);
          }
          else
          {
            brother->color_ = 'r';
            toDel->parent_ = fixBeforeErase(parent);
          }
        }
        else
        {
          auto brother = parent->left_;
          auto out_nephew = brother->left_;
          auto in_nephew = brother->right_;
          if (out_nephew != fake && out_nephew->color_ == 'r')
          {
            parent->color_ = 'b';
            out_nephew->color_ = 'b';
            root_.rightRotation(parent);
          }
          else if (in_nephew != fake && in_nephew->color_ == 'r')
          {
            in_nephew->color_ = 'b';
            brother->color_ = 'r';
            root_.leftRotation(brother);
            toDel = fixBeforeErase(toDel);
          }
          else if (parent->color_ == 'r')
          {
            parent->color_ = 'b';
            brother->color_ = 'r';
          }
          else if (brother->color_ == 'r')
          {
            parent->color_ = 'r';
            brother->color_ = 'b';
            root_.rightRotation(parent);
            toDel = fixBeforeErase(toDel);
          }
          else
          {
            brother->color_ = 'r';
            toDel->parent_ = fixBeforeErase(parent);
          }
        }
      }
      else
      {
        if (l_child->color_ == 'r')
        {
          l_child->color_ = 'b';
        }
        else
        {
          r_child->color_ = 'b';
        }
      }
    }
    return toDel;
  }

  template< typename T, typename Compare >
  size_t RedBlackTree< T, Compare >::count(const T& data) const
  {
    return root_.count(data);
  }

  template< typename T, typename Compare >
  void RedBlackTree< T, Compare >::swap(RBTree& other)
  {
    root_.swap(other.root_);
  }

  template< typename T, typename Compare >
  void RedBlackTree< T, Compare >::clear()
  {
    root_.clear();
  }

  template< typename T, typename Compare >
  BidirectionalIterator< T, Compare > RedBlackTree< T, Compare >::lower_bound(const T& data)
  {
    return root_.lower_bound(data);
  }

  template< typename T, typename Compare >
  ConstBidirectionalIterator< T, Compare > RedBlackTree< T, Compare >::lower_bound(const T& data) const
  {
    return root_.lower_bound(data);
  }

  template< typename T, typename Compare >
  BidirectionalIterator< T, Compare > RedBlackTree< T, Compare >::upper_bound(const T& data)
  {
    return root_.upper_bound(data);
  }

  template< typename T, typename Compare >
  ConstBidirectionalIterator< T, Compare > RedBlackTree< T, Compare >::upper_bound(const T& data) const
  {
    return root_.upper_bound(data);
  }

  template< typename T, typename Compare >
  Compare RedBlackTree< T, Compare >::value_comp() const
  {
    return root_.compare_;
  }

  template< typename T, typename Compare >
  bool operator==(const RedBlackTree< T, Compare >& lhs, const RedBlackTree< T, Compare >& rhs)
  {
    if (lhs.size() != rhs.size())
    {
      return false;
    }
    auto l_it = lhs.cbegin();
    auto r_it = rhs.cbegin();
    while (l_it != lhs.cend())
    {
      if (*l_it != *r_it)
      {
        return false;
      }
      ++l_it;
      ++r_it;
    }
    return true;
  }

  template< typename T, typename Compare >
  bool operator!=(const RedBlackTree< T, Compare >& lhs, const RedBlackTree< T, Compare >& rhs)
  {
    return !(lhs == rhs);
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
    if (!root || root == root_.fake_)
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
