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
      
      it source() noexcept; //done
      cit source() const noexcept; //done
      cit csource() const noexcept; //done

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
      TreeNode< tree_t > * source_;
      C cmp_;
      std::size_t size_;

      void slr(TreeNode< tree_t > * source);
      void srr(TreeNode< tree_t > * source);
      void blr(TreeNode< tree_t > * source);
      void brr(TreeNode< tree_t > * source);

      void balanceDelete();
      void copy(const tree & rhs);
      void balance(TreeNode< tree_t > * source);
      void increase(TreeNode< tree_t > * source);
      int measure(TreeNode< tree_t > * source);
      int discern(TreeNode< tree_t > * source);
  };
}

template< typename K, typename V, typename C >
turkin::AVLtree< K, V, C >::AVLtree():
  source_(new TreeNode< tree_t >),
  cmp_(),
  size_(0)
{}

template< typename K, typename V, typename C >
turkin::AVLtree< K, V, C >::AVLtree(const tree & rhs):
  source_(nullptr),
  cmp_(rhs.cmp_),
  size_(rhs.size_)
{
  copy(rhs);
}

template< typename K, typename V, typename C >
turkin::AVLtree< K, V, C >::AVLtree(tree && rhs):
  source_(rhs.source_),
  cmp_(rhs.cmp_),
  size_(rhs.size_)
{
  rhs.source_ = nullptr;
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
  source_ = rhs.source_;
  cmp_ = rhs.cmp_;
  size_ = rhs.size_;
  rhs.source_ = nullptr;
  rhs.size_ = 0;
  return * this;
}

template< typename K, typename V, typename C >
turkin::AVLtree< K, V, C >::~AVLtree()
{
  free(source_);
}

template< typename K, typename V, typename C >
turkin::Iterator< K, V, C > turkin::AVLtree< K, V, C >::source() noexcept
{
  return it(source_);
}

template< typename K, typename V, typename C >
turkin::ConstIterator< K, V, C > turkin::AVLtree< K, V, C >::source() const noexcept
{
  return cit(source_);
}

template< typename K, typename V, typename C >
turkin::ConstIterator< K, V, C > turkin::AVLtree< K, V, C >::csource() const noexcept
{
  return cit(source_);
}

template< typename K, typename V, typename C >
turkin::Iterator< K, V, C > turkin::AVLtree< K, V, C >::insert(const tree_t & value)
{
  TreeNode< tree_t > * ins = {value, nullptr, nullptr, nullptr, 1};
  if (!source_)
  {
    source_ = ins;
  }

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
  free(source_);
  source_ = nullptr;
}

template< typename K, typename V, typename C >
void turkin::AVLtree< K, V, C >::slr(TreeNode< tree_t > * source)
{
  TreeNode< tree_t > * rhs = source->right;
  source->right = rhs->left;
  rhs->left = source;
  increase(rhs);
  increase(source);
}

template< typename K, typename V, typename C >
void turkin::AVLtree< K, V, C >::srr(TreeNode< tree_t > * source)
{
  TreeNode< tree_t > * lhs = source->right;
  source->left = lhs->right;
  lhs->left = source;
  increase(lhs);
  increase(source);
}

template< typename K, typename V, typename C >
void turkin::AVLtree< K, V, C >::blr(TreeNode< tree_t > * source)
{
  srr(source->right);
  slr(source);
}

template< typename K, typename V, typename C >
void turkin::AVLtree< K, V, C >::brr(TreeNode< tree_t > * source)
{
  slr(source->left);
  srr(source);
}

template< typename K, typename V, typename C >
void turkin::AVLtree< K, V, C >::balanceDelete() {}

template< typename K, typename V, typename C >
void turkin::AVLtree< K, V, C >::copy(const tree & rhs) {}

template< typename K, typename V, typename C >
void turkin::AVLtree< K, V, C >::balance(TreeNode< tree_t > * source)
{
  int diff = discern(source);
  if (diff == -2)
  {
    if (discern(source->left) == 1)
    {
      brr(source);
    }
    else
    {
      srr(source);
    }
  }
  else if (diff == 2)
  {
    if (discern(source->right) == -1)
    {
      blr(source);
    }
    else
    {
      slr(source);
    }
  }
}

template< typename K, typename V, typename C >
void turkin::AVLtree< K, V, C >::increase(TreeNode< tree_t > * source)
{
  source->height = std::max(measure(source->left), measure(source->right)) + 1;
}

template< typename K, typename V, typename C >
int turkin::AVLtree< K, V, C >::measure(TreeNode< tree_t > * source)
{
  return (source == nullptr) ? -1 : source->height;
}

template< typename K, typename V, typename C >
int turkin::AVLtree< K, V, C >::discern(TreeNode< tree_t > * source)
{
  return (source == nullptr) ? 0 : measure(source->right) - measure(source->left);
}

#endif
