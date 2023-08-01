#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <cstddef>

#include "iterators/direct-iterator.hpp"
#include "iterators/direct-const-iterator.hpp"
#include "tree-node.hpp"

namespace turkin
{
  template< typename K, typename V, typename C >
  class AVLtree
  {
    using tree = AVLtree< K, V, C >;
    using tree_t = std::pair< K, V >;
    using it = DirectIterator< K, V, C >;
    using cit = DirectConstIterator< K, V, C >;
    public:
      AVLtree();
      AVLtree(const tree & rhs);
      AVLtree(tree && rhs);
      tree operator=(const tree & rhs);
      tree operator=(tree && rhs);
      ~AVLtree();
      
      it directSource() noexcept;
      cit directSource() const noexcept;
      cit directCSource() const noexcept;

      bool empty() const noexcept;
      std::size_t size() const noexcept;

      void clear() noexcept;
      it insert(const K & k, const V & v);
      void erase(const K & k);
      
      void swap(tree & rhs) noexcept;
      
    private:
      TreeNode< tree_t, C > source_;
      TreeNode< tree_t, C > dummy_;
      C cmp_;
      std::size_t size_;

      void balanceInsert();
      void balanceErase();
      void copy(const tree & rhs);
  };
}

template< typename K, typename V, typename C >
turkin::AVLtree< K, V, C >::AVLtree():
  source_(new TreeNode< tree_t, C >),
  dummy_(new TreeNode< tree_t, C >),
  cmp_(),
  size_(0)
{
  source_.parent = nullptr;
  source_.left = dummy_;
  source_.right = dummy_;
}

template< typename K, typename V, typename C >
turkin::AVLtree< K, V, C >::AVLtree(const tree & rhs):
  source_(nullptr),
  dummy_(new TreeNode< tree_t, C >),
  cmp_(rhs.cmp_),
  size_(rhs.size_)
{
  copy(rhs);
}

template< typename K, typename V, typename C >
turkin::AVLtree< K, V, C >::AVLtree(tree && rhs):
  source_(rhs.source_),
  dummy_(rhs.dummy_),
  cmp_(rhs.cmp_),
  size_(rhs.size_)
{
  rhs.source_ = nullptr;
  rhs.dummy_ = nullptr;
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
  dummy_ = rhs.dummy_;
  cmp_ = rhs.cmp_;
  size_ = rhs.size_;
  rhs.source_ = nullptr;
  rhs.dummy_ = nullptr;
  rhs.size_ = 0;
  return * this;
}

template< typename K, typename V, typename C >
turkin::AVLtree< K, V, C >::~AVLtree()
{
  free(source_);
}

template< typename K, typename V, typename C >
turkin::DirectIterator< K, V, C > turkin::AVLtree< K, V, C >::directSource() noexcept
{
  return dit(source_);
}

template< typename K, typename V, typename C >
turkin::DirectConstIterator< K, V, C > turkin::AVLtree< K, V, C >::directSource() const noexcept
{
  return dcit(source_);
}

template< typename K, typename V, typename C >
turkin::DirectConstIterator< K, V, C > turkin::AVLtree< K, V, C >::directCSource() const noexcept
{
  return dcit(source_);
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

#endif
