#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <utility>
#include <stack.h>
#include <queue.h>
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
   using reverse_iterator = std::reverse_iterator< iterator >;
   using const_reverse_iterator = std::reverse_iterator< const_iterator >;
  public:
   friend class RedBlackTree< T, Compare >;

   BinarySearchTree():
     fake_(static_cast< root_t* >(::operator new(sizeof(root_t)))),
     root_(nullptr),
     begin_(nullptr),
     end_(nullptr),
     size_(0),
     compare_()
   {
     fake_->left_ = fake_;
     fake_->right_ = fake_;
     fake_->parent_ = fake_;
   }

   BinarySearchTree(const BSTree& other):
     fake_(static_cast< root_t* >(::operator new(sizeof(root_t)))),
     root_(nullptr),
     begin_(nullptr),
     end_(nullptr),
     size_(0),
     compare_(other.compare_)
   {
     try
     {
       root_ = copyTree(other);
     }
     catch (...)
     {
       clear();
       ::operator delete(fake_);
       throw;
     }
   }

   BinarySearchTree(BSTree&& other):
     fake_(other.fake_),
     root_(other.root_),
     begin_(other.begin_),
     end_(other.end_),
     size_(other.size_),
     compare_(other.compare_)
   {
     other.fake_ = nullptr;
     other.root_ = nullptr;
     other.begin_ = nullptr;
     other.end_ = nullptr;
     other.size_ = 0;
   }

   ~BinarySearchTree()
   {
     clear();
     ::operator delete(fake_);
   }

   BSTree& operator=(const BSTree& other)
   {
     if (this != std::addressof(other))
     {
       BSTree temp(other);
       clear();
       swap(temp);
     }
     return *this;
   }

   BSTree& operator=(BSTree&& other)
   {
     if (this != std::addressof(other))
     {
       clear();
       BSTree temp(std::move(other));
       swap(temp);
     }
     return *this;
   }

   friend class BidirectionalIterator< T, Compare >;
   iterator beforeBegin() const;
   iterator begin() const;
   iterator end() const;
   friend class ConstBidirectionalIterator< T, Compare >;
   const_iterator cbeforeBegin() const;
   const_iterator cbegin() const;
   const_iterator cend() const;
   reverse_iterator rbegin();
   reverse_iterator rend();
   const_reverse_iterator crbegin() const;
   const_reverse_iterator crend() const;
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
   template< class InputIt >
   iterator insert(const_iterator pos, InputIt first, InputIt last);
   void leftRotation();
   void rightRotation();
   const_iterator find(const T& data) const;
   iterator find(const T& data);
   iterator erase(iterator pos);
   iterator erase(const_iterator pos);
   iterator erase(const_iterator first, const_iterator last);
   size_t erase(const T& data);
   size_t count(const T& data) const;
   void swap(BSTree& other);
   void clear();
   iterator lower_bound(const T& data);
   const_iterator lower_bound(const T& data) const;
   iterator upper_bound(const T& data);
   const_iterator upper_bound(const T& data) const;
   Compare value_comp() const;
   template< typename F >
   F traverse_lnr(F f);
   template< typename F >
   F traverse_lnr(F f) const;
   template< typename F >
   F traverse_rnl(F f);
   template< typename F >
   F traverse_rnl(F f) const;
   template< typename F >
   F traverse_breadth(F f);
   template< typename F >
   F traverse_breadth(F f) const;

  private:
   root_t* fake_;
   root_t* root_;
   root_t* begin_;
   root_t* end_;
   size_t size_;
   Compare compare_;
   std::pair< iterator, iterator > insert(const T& data, iterator it);
   void leftRotation(root_t* ptree);
   void rightRotation(root_t* ptree);
   const_iterator find(const T& data, const_iterator it) const;
   const_iterator findMax(const_iterator it);
   const_iterator findMin(const_iterator it);
   void deleteTree(root_t* ptree);
   root_t* copyTree(const BSTree& other);
  };

  template< typename T, typename Compare >
  details::Tree< T, Compare >* BinarySearchTree< T, Compare >::copyTree(const BSTree& other)
  {
    for (auto it = other.cbegin(); it != other.cend(); it++)
    {
      insert(*it);
    }
    return root_;
  }

  template< typename T, typename Compare >
  BidirectionalIterator< T, Compare > BinarySearchTree< T, Compare >::beforeBegin() const
  {
    if (!begin_)
    {
      return iterator(fake_, fake_);
    }
    fake_->right_ = begin_;
    begin_->left_ = fake_;
    return iterator(fake_, begin_->left_);
  }

  template< typename T, typename Compare >
  BidirectionalIterator< T, Compare > BinarySearchTree< T, Compare >::begin() const
  {
    if (!begin_)
    {
      return iterator(fake_, fake_);
    }
    return iterator(fake_, begin_);
  }

  template< typename T, typename Compare >
  BidirectionalIterator< T, Compare > BinarySearchTree< T, Compare >::end() const
  {
    if (!end_)
    {
      return iterator(fake_, fake_);
    }
    fake_->left_ = end_;
    end_->right_ = fake_;
    return iterator(fake_, end_->right_);
  }

  template< typename T, typename Compare >
  ConstBidirectionalIterator< T, Compare > BinarySearchTree< T, Compare >::cbeforeBegin() const
  {
    return const_iterator(beforeBegin());
  }

  template< typename T, typename Compare >
  ConstBidirectionalIterator< T, Compare > BinarySearchTree< T, Compare >::cbegin() const
  {
    return const_iterator(begin());
  }

  template< typename T, typename Compare >
  ConstBidirectionalIterator< T, Compare > BinarySearchTree< T, Compare >::cend() const
  {
    return const_iterator(end());
  }

  template< typename T, typename Compare >
  typename BinarySearchTree< T, Compare >::reverse_iterator BinarySearchTree< T, Compare >::rbegin()
  {
    return reverse_iterator(end());
  }

  template< typename T, typename Compare >
  typename BinarySearchTree< T, Compare >::reverse_iterator BinarySearchTree< T, Compare >::rend()
  {
    return reverse_iterator(begin());
  }

  template< typename T, typename Compare >
  typename BinarySearchTree< T, Compare >::const_reverse_iterator BinarySearchTree< T, Compare >::crbegin() const
  {
    return const_reverse_iterator(cend());
  }

  template< typename T, typename Compare >
  typename BinarySearchTree< T, Compare >::const_reverse_iterator BinarySearchTree< T, Compare >::crend() const
  {
    return const_reverse_iterator(cbegin());
  }

  template< typename T, typename Compare >
  const T& BinarySearchTree< T, Compare >::at(const T& data) const
  {
    const_iterator c_it = find(data);
    if (c_it == cend())
    {
      throw std::out_of_range("No data found");
    }
    return *c_it;
  }

  template< typename T, typename Compare >
  T& BinarySearchTree< T, Compare >::at(const T& data)
  {
    return const_cast< T& >((static_cast< const BSTree& >(*this)).at(data));
  }

  template< typename T, typename Compare >
  T& BinarySearchTree< T, Compare >::operator[](const T& data)
  {
    iterator it = find(data);
    return *it;
  }

  template< typename T, typename Compare >
  T& BinarySearchTree< T, Compare >::operator[](T&& data)
  {
    return (*this)[data];
  }

  template< typename T, typename Compare >
  size_t BinarySearchTree< T, Compare >::size() const
  {
    return size_;
  }

  template< typename T, typename Compare >
  bool BinarySearchTree< T, Compare >::isEmpty() const
  {
    return !size_;
  }

  template< typename T, typename Compare >
  std::pair< BidirectionalIterator< T, Compare >, BidirectionalIterator< T, Compare > >
    BinarySearchTree< T, Compare >::insert(const T& data, iterator it)
  {
    auto inserted = end();
    auto node = it.node_;
    if (compare_(data, *it))
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
        inserted = res.second;
      }
    }
    else if (compare_(*it, data))
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
      begin_ = root_;
      end_ = root_;
      ++size_;
      return std::make_pair(iterator(fake_, root_), true);
    }
    else
    {
      auto inserted = insert(data, iterator(fake_, root_)).second.node_;
      if (inserted != fake_)
      {
        if (compare_(data, begin_->data_))
        {
          begin_ = inserted;
        }
        if (compare_(end_->data_, data))
        {
          end_ = inserted;
        }
        ++size_;
        return std::make_pair(iterator(fake_, inserted), true);
      }
      return std::make_pair(end(), false);
    }
  }

  template< typename T, typename Compare >
  std::pair< BidirectionalIterator< T, Compare >, bool > BinarySearchTree< T, Compare >::insert(T&& data)
  {
    const T value = std::forward< T >(data);
    return insert(value);
  }

  template< typename T, typename Compare >
  BidirectionalIterator< T, Compare >
    BinarySearchTree< T, Compare >::insert(const_iterator pos, const T& data)
  {
    if (compare_(data, *pos) && compare_(*(--pos), data))
    {
      pos.node_->left_ = new root_t(data, pos.node_->left_, fake_, pos.node_);
      ++size_;
      return iterator(fake_, pos.node_->left_);
    }
    return insert(data).first;
  }

  template< typename T, typename Compare >
  BidirectionalIterator< T, Compare >
    BinarySearchTree< T, Compare >::insert(const_iterator pos, T&& data)
  {
    const T value = std::forward< T >(data);
    return insert(pos, value);
  }

  template< typename T, typename Compare >
  template< class InputIt >
  BidirectionalIterator< T, Compare >
    BinarySearchTree< T, Compare >::insert(const_iterator pos, InputIt first, InputIt last)
  {
    while (first != last)
    {
      return insert(pos, *first++);
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
    if (ptree == root_)
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
    if (ptree == root_)
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
  ConstBidirectionalIterator< T, Compare >
    BinarySearchTree< T, Compare >::find(const T& data, const_iterator it) const
  {
    if (it.node_ == fake_)
    {
      return cend();
    }
    if (!compare_(*it, data) && !compare_(data, *it))
    {
      return it;
    }
    if (compare_(data, *it))
    {
      return find(data, const_iterator(fake_, it.node_->left_));
    }
    return find(data, const_iterator(fake_, it.node_->right_));
  }

  template< typename T, typename Compare >
  ConstBidirectionalIterator< T, Compare > BinarySearchTree< T, Compare >::find(const T& data) const
  {
    auto c_it = const_iterator(fake_, root_);
    return root_ ? find(data, c_it) : cend();
  }

  template< typename T, typename Compare >
  BidirectionalIterator< T, Compare > BinarySearchTree< T, Compare >::find(const T& data)
  {
    const_iterator c_it = static_cast< const BSTree& >(*this).find(data);
    return iterator(fake_, c_it.node_);
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
  ConstBidirectionalIterator< T, Compare > BinarySearchTree< T, Compare >::findMax(const_iterator it)
  {
    if (it.node_ == fake_)
    {
      return cend();
    }
    else if (it.node_->right_ == fake_)
    {
      return it;
    }
    else
    {
      return findMax(const_iterator(fake_, it.node_->right_));
    }
  }

  template< typename T, typename Compare >
  BidirectionalIterator< T, Compare > BinarySearchTree< T, Compare >::erase(const_iterator pos)
  {
    auto toDel = iterator(fake_, pos.node_);
    auto nodeToDel = toDel.node_;
    ++toDel;
    auto left = nodeToDel->left_;
    auto right = nodeToDel->right_;
    auto parent = nodeToDel->parent_;

    if (left != fake_ && right != fake_)
    {
      auto replaceNodeIt = findMin(const_iterator(fake_, right));
      std::swap(nodeToDel->data_, *replaceNodeIt);
      return erase(replaceNodeIt);
    }
    else
    {
      auto child = left != fake_ ? left : right;
      if (nodeToDel != root_)
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
      else
      {
        root_ = child;
        root_->parent_ = fake_;
      }
      if (nodeToDel == end_)
      {
        end_ = left != fake_ ? left : parent;
      }
      if (nodeToDel == begin_)
      {
        begin_ = right != fake_ ? right : parent;
      }
      delete nodeToDel;
      --size_;
      return toDel;
    }
  }

  template< typename T, typename Compare >
  BidirectionalIterator< T, Compare > BinarySearchTree< T, Compare >::erase(iterator pos)
  {
    return erase(const_iterator(pos));
  }

  template< typename T, typename Compare >
  BidirectionalIterator< T, Compare > BinarySearchTree< T, Compare >::erase(const_iterator first, const_iterator last)
  {
    while (first != last)
    {
      erase(first++);
    }
    return iterator(fake_, first.node_);
  }

  template< typename T, typename Compare >
  size_t BinarySearchTree< T, Compare >::erase(const T& data)
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
  size_t BinarySearchTree< T, Compare >::count(const T& data) const
  {
    return find(data) != cend() ? 1ull : 0ull;
  }

  template< typename T, typename Compare >
  void BinarySearchTree< T, Compare >::swap(BSTree& other)
  {
    std::swap(fake_, other.fake_);
    std::swap(root_, other.root_);
    std::swap(begin_, other.begin_);
    std::swap(end_, other.end_);
    std::swap(size_, other.size_);
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
      size_ = 0;
    }
  }

  template< typename T, typename Compare >
  BidirectionalIterator< T, Compare > BinarySearchTree< T, Compare >::lower_bound(const T& data)
  {
    auto curr = iterator(fake_, root_);
    while (curr != end())
    {
      if (!compare_(data, *curr) && !compare_(*curr, data))
      {
        return curr;
      }
      else if (compare_(data, *curr))
      {
        --curr;
      }
      else
      {
        ++curr;
      }
    }
    return end();
  }

  template< typename T, typename Compare >
  ConstBidirectionalIterator< T, Compare > BinarySearchTree< T, Compare >::lower_bound(const T& data) const
  {
    return const_iterator(lower_bound(data));
  }

  template< typename T, typename Compare >
  BidirectionalIterator< T, Compare > BinarySearchTree< T, Compare >::upper_bound(const T& data)
  {
    iterator it = lower_bound(data);
    if (it == end())
    {
      return end();
    }
    else
    {
      if (!compare_(*it, data) && !compare_(data, *it))
      {
        return ++it;
      }
      else
      {
        return it;
      }
    }
  }

  template< typename T, typename Compare >
  ConstBidirectionalIterator< T, Compare > BinarySearchTree< T, Compare >::upper_bound(const T& data) const
  {
    return const_iterator(upper_bound(data));
  }

  template< typename T, typename Compare >
  Compare BinarySearchTree< T, Compare >::value_comp() const
  {
    return compare_;
  }

  template< typename T, typename Compare >
  bool operator==(const BinarySearchTree< T, Compare >& lhs, const BinarySearchTree< T, Compare >& rhs)
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
  bool operator!=(const BinarySearchTree< T, Compare >& lhs, const BinarySearchTree< T, Compare >& rhs)
  {
    return !(lhs == rhs);
  }

  template< typename T, typename Compare >
  template< typename F >
  F BinarySearchTree< T, Compare >::traverse_lnr(F f)
  {
    return static_cast< const BSTree& >(*this).traverse_lnr(f);
  }

  template< typename T, typename Compare >
  template< typename F >
  F BinarySearchTree< T, Compare >::traverse_lnr(F f) const
  {
    if (root_)
    {
      Stack< root_t* > s;
      root_t* curr = root_;
      while (curr != fake_ || !s.isEmpty())
      {
        if (curr != fake_)
        {
          s.push(curr);
          curr = curr->left_;
        }
        else
        {
          curr = s.getTopElem();
          s.pop();
          f(curr->data_);
          curr = curr->right_;
        }
      }
    }
    return f;
  }

  template< typename T, typename Compare >
  template< typename F >
  F BinarySearchTree< T, Compare >::traverse_rnl(F f)
  {
    return static_cast< const BSTree& >(*this).traverse_rnl(f);
  }

  template< typename T, typename Compare >
  template< typename F >
  F BinarySearchTree< T, Compare >::traverse_rnl(F f) const
  {
    if (root_)
    {
      Stack< root_t* > s;
      root_t* curr = root_;
      while (curr != fake_ || !s.isEmpty())
      {
        if (curr != fake_)
        {
          s.push(curr);
          curr = curr->right_;
        }
        else
        {
          curr = s.getTopElem();
          s.pop();
          f(curr->data_);
          curr = curr->left_;
        }
      }
    }
    return f;
  }

  template< typename T, typename Compare >
  template< typename F >
  F BinarySearchTree< T, Compare >::traverse_breadth(F f)
  {
    return static_cast< const BSTree& >(*this).traverse_breadth(f);
  }

  template< typename T, typename Compare >
  template< typename F >
  F BinarySearchTree< T, Compare >::traverse_breadth(F f) const
  {
    Queue< root_t* > q;
    if (root_)
    {
      q.push(root_);
    }
    while (!q.isEmpty())
    {
      root_t* curr = q.getHeadElem();
      q.popFront();
      f(curr->data_);
      if (curr->left_ != fake_)
      {
        q.push(curr->left_);
      }
      if (curr->right_ != fake_)
      {
        q.push(curr->right_);
      }
    }
    return f;
  }
}
#endif
