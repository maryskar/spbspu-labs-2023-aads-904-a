#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <cstddef>
#include <algorithm>

#include "iterators/iterator.hpp"
#include "iterators/const-iterator.hpp"
#include "tree-node.hpp"

namespace turkin
{
  template< typename K, typename V, typename C >
  class AVLtree
  {
    using tree = AVLtree< K, V, C >;
    using tree_t = std::pair< K, V >;
    using it = Iterator< K, V, C >;
    using cit = ConstIterator< K, V, C >;
    public:
      AVLtree(); // done
      AVLtree(const tree & rhs);
      AVLtree(tree && rhs); // done
      tree operator=(const tree & rhs);
      tree operator=(tree && rhs); //done
      ~AVLtree(); //done
      
      it src() noexcept; //done
      cit src() const noexcept; //done
      cit csrc() const noexcept; //done

      V & at(const K & key);
      const V & at(const K & key) const;
      V & operator[](const K & key);

      it insert(const K & k, const V & v);
      it insert(const tree_t & value); //base
      it insert(tree_t && value);
      template< class It >
      it insert(It first, It last);

      it erase(const K & k);
      it erase(it pos); //base
      it erase(cit pos);
      it erase(cit first, cit last);

      it lower_bound(const K & key);
      cit lower_bound(const K & key) const;
      it upper_bound(const K & key);
      cit upper_bound(const K & key) const;

      size_t count(const K & key) const;
      it find(const K & key);
      cit find(const K & key) const;

      bool empty() const noexcept; //done
      std::size_t size() const noexcept; //done
      void clear() noexcept; //done
      void swap(tree & rhs) noexcept;
      
    private:
      TreeNode< tree_t > * root_;
      C cmp_;
      std::size_t size_;

      void slr(TreeNode< tree_t > * src); //done
      void srr(TreeNode< tree_t > * src); //done
      void blr(TreeNode< tree_t > * src); //done
      void brr(TreeNode< tree_t > * src); //done

      void balanceDelete();
      void copy(const tree & rhs);
      void insert(TreeNode< tree_t > * src, const tree_t & value);
      void balance(TreeNode< tree_t > * src); //done
      void increase(TreeNode< tree_t > * src); //done
      int measure(TreeNode< tree_t > * src); //done
      int discern(TreeNode< tree_t > * src); //done
  };
}

template< typename K, typename V, typename C >
turkin::AVLtree< K, V, C >::AVLtree():
  root_(nullptr),
  cmp_(),
  size_(0)
{}

template< typename K, typename V, typename C >
turkin::AVLtree< K, V, C >::AVLtree(const tree & rhs):
  root_(nullptr),
  cmp_(rhs.cmp_),
  size_(rhs.size_)
{
  copy(rhs);
}

template< typename K, typename V, typename C >
turkin::AVLtree< K, V, C >::AVLtree(tree && rhs):
  root_(rhs.src_),
  cmp_(rhs.cmp_),
  size_(rhs.size_)
{
  rhs.src_ = nullptr;
  rhs.size_ = 0;
}

template< typename K, typename V, typename C >
turkin::AVLtree< K, V, C > turkin::AVLtree< K, V, C >::operator=(const tree & rhs)
{
  if (std::addressof(rhs) == this)
  {
    return * this;
  }
  clear();
  copy(rhs);
  return * this;
}

template< typename K, typename V, typename C >
turkin::AVLtree< K, V, C > turkin::AVLtree< K, V, C >::operator=(tree && rhs)
{
  if (std::addressof(rhs) == this)
  {
    return * this;
  }
  clear();
  root_ = rhs.src_;
  cmp_ = rhs.cmp_;
  size_ = rhs.size_;
  rhs.src_ = nullptr;
  rhs.size_ = 0;
  return * this;
}

template< typename K, typename V, typename C >
turkin::AVLtree< K, V, C >::~AVLtree()
{
  free(root_);
}

template< typename K, typename V, typename C >
turkin::Iterator< K, V, C > turkin::AVLtree< K, V, C >::src() noexcept
{
  return it(root_);
}

template< typename K, typename V, typename C >
turkin::ConstIterator< K, V, C > turkin::AVLtree< K, V, C >::src() const noexcept
{
  return cit(root_);
}

template< typename K, typename V, typename C >
turkin::ConstIterator< K, V, C > turkin::AVLtree< K, V, C >::csrc() const noexcept
{
  return cit(root_);
}

template< typename K, typename V, typename C >
turkin::Iterator< K, V, C > turkin::AVLtree< K, V, C >::insert(const tree_t & value)
{
  if (root_ == nullptr)
  {
    root_ = new TreeNode< tree_t > {value, nullptr, nullptr, nullptr, 0};
    increase(root_);
  }
  else
  {
    insert(root_, value);
  }
  return src();
}

template< typename K, typename V, typename C >
bool turkin::AVLtree< K, V, C >::empty() const noexcept
{
  return size_ == 0;
}

template< typename K, typename V, typename C >
std::size_t turkin::AVLtree< K, V, C >::size() const noexcept
{
  return size_;
}

template< typename K, typename V, typename C >
void turkin::AVLtree< K, V, C >::clear() noexcept
{
  free(root_);
  root_ = nullptr;
}

template< typename K, typename V, typename C >
void turkin::AVLtree< K, V, C >::slr(TreeNode< tree_t > * src)
{
  std::swap(src, src->right);
  TreeNode< tree_t > * local = src->left;
  src->left = src->right;
  src->right = src->left->right;
  src->right->left = src->right->right;
  src->left->right = src->left->left;
  src->left->left = local;
  increase(src->left);
  increase(src);
}

template< typename K, typename V, typename C >
void turkin::AVLtree< K, V, C >::srr(TreeNode< tree_t > * src)
{
  std::swap(src, src->left);
  TreeNode< tree_t > * local = src->right;
  src->right = src->left;
  src->left = src->right->left;
  src->right->left = src->right->right;
  src->right->right = local;
  increase(src->right);
  increase(src);
}

template< typename K, typename V, typename C >
void turkin::AVLtree< K, V, C >::blr(TreeNode< tree_t > * src)
{
  srr(src->right);
  slr(src);
}

template< typename K, typename V, typename C >
void turkin::AVLtree< K, V, C >::brr(TreeNode< tree_t > * src)
{
  slr(src->left);
  srr(src);
}

template< typename K, typename V, typename C >
void turkin::AVLtree< K, V, C >::balanceDelete() {}

template< typename K, typename V, typename C >
void turkin::AVLtree< K, V, C >::copy(const tree & rhs) {}

template< typename K, typename V, typename C >
void turkin::AVLtree< K, V, C >::insert(TreeNode< tree_t > * src, const tree_t & value)
{
  if (cmp_(value.first, src->data.first))
  {
    if (src->left == nullptr)
    {
      src->left = new TreeNode< tree_t > {value, src, nullptr, nullptr, 0};
    }
    else
    {
      insert(src->left, value);
    }
  }
  else if (!cmp_(value.first, src->data.first))
  {
    if (src->right == nullptr)
    {
      src->right = new TreeNode< tree_t > {value, src, nullptr, nullptr, 0};
    }
    else
    {
      insert(src->right, value);
    }
  }

  increase(src);
  balance(src);
}

template< typename K, typename V, typename C >
void turkin::AVLtree< K, V, C >::balance(TreeNode< tree_t > * src)
{
  int diff = discern(src);
  if (diff == -2)
  {
    if (discern(src->left) == 1)
    {
      brr(src);
    }
    else
    {
      srr(src);
    }
  }
  else if (diff == 2)
  {
    if (discern(src->right) == -1)
    {
      blr(src);
    }
    else
    {
      slr(src);
    }
  }
}

template< typename K, typename V, typename C >
void turkin::AVLtree< K, V, C >::increase(TreeNode< tree_t > * src)
{
  src->height = std::max(measure(src->left), measure(src->right)) + 1;
}

template< typename K, typename V, typename C >
int turkin::AVLtree< K, V, C >::measure(TreeNode< tree_t > * src)
{
  return (src == nullptr) ? -1 : src->height;
}

template< typename K, typename V, typename C >
int turkin::AVLtree< K, V, C >::discern(TreeNode< tree_t > * src)
{
  return (src == nullptr) ? 0 : measure(src->right) - measure(src->left);
}

#endif
