#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <cstddef>

#include "iterators/direct-iterator.hpp"
#include "iterators/direct-const-iterator.hpp"
#include "iterators/reverse-iterator.hpp"
#include "iterators/reverse-const-iterator.hpp"
#include "tree-node.hpp"

namespace turkin
{
  template< typename K, typename V, typename C >
  class RBtree
  {
    using tree = RBtree< K, V, C >;
    using tree_t = std::pair< K, V >;
    using dit = DirectIterator< K, V, C >;
    using dcit = DirectConstIterator< K, V, C >;
    using rit = ReverseIterator< K, V, C >;
    using rcit = ReverseConstIterator< K, V, C >;
    public:
      RBtree();
      RBtree(const tree & rhs);
      RBtree(tree && rhs);
      tree operator=(const tree & rhs);
      tree operator=(tree && rhs);
      ~RBtree();
      
      dit directSource() noexcept;
      dcit directSource() const noexcept;
      dcit directCSource() const noexcept;
      
      rit reverseSource() noexcept;
      rcit reverseSource() const noexcept;
      rcit reverseCSource() const noexcept;

      bool empty() const noexcept;
      std::size_t size() const noexcept;

      void clear() noexcept;
      dit insert(const K & k, const V & v);
      dit insert(const tree_t & value);
      void erase(const K & k);
      tree_t extract(dcit pos);
      
      void swap(tree & rhs) noexcept;
      V at(const K & k);
      const V at(const K & k) const;

      dit find(const K & k);
      dcit find(const K & k) const;
      
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
turkin::RBtree< K, V, C >::RBtree():
  source_(new TreeNode< tree_t, C >),
  dummy_(new TreeNode< tree_t, C >),
  cmp_(),
  size_(0)
{
  source_.parent = nullptr;
  source_.left = dummy_;
  source_.right = dummy_;
  source_.color = TreeColor::BLACK;
  
  dummy_.color = TreeColor::BLACK;
}

template< typename K, typename V, typename C >
turkin::RBtree< K, V, C >::RBtree(const tree & rhs):
  source_(nullptr),
  dummy_(new TreeNode< tree_t, C >),
  cmp_(rhs.cmp_),
  size_(rhs.size_)
{
  copy(rhs);
}

template< typename K, typename V, typename C >
turkin::RBtree< K, V, C >::RBtree(tree && rhs):
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
turkin::RBtree< K, V, C > turkin::RBtree< K, V, C >::operator=(const tree & rhs)
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
turkin::RBtree< K, V, C > turkin::RBtree< K, V, C >::operator=(tree && rhs)
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
turkin::RBtree< K, V, C >::~RBtree()
{
  free(source_);
}

template< typename K, typename V, typename C >
turkin::DirectIterator< K, V, C > turkin::RBtree< K, V, C >::directSource() noexcept
{
  return dit(source_);
}

template< typename K, typename V, typename C >
turkin::DirectConstIterator< K, V, C > turkin::RBtree< K, V, C >::directSource() const noexcept
{
  return dcit(source_);
}

template< typename K, typename V, typename C >
turkin::DirectConstIterator< K, V, C > turkin::RBtree< K, V, C >::directCSource() const noexcept
{
  return dcit(source_);
}

template< typename K, typename V, typename C >
turkin::ReverseIterator< K, V, C > turkin::RBtree< K, V, C >::reverseSource() noexcept
{
  return rit(source_);
}

template< typename K, typename V, typename C >
turkin::ReverseConstIterator< K, V, C > turkin::RBtree< K, V, C >::reverseSource() const noexcept
{
  return rcit(source_); 
}

template< typename K, typename V, typename C >
turkin::ReverseConstIterator< K, V, C > turkin::RBtree< K, V, C >::reverseCSource() const noexcept {}

template< typename K, typename V, typename C >
bool turkin::RBtree< K, V, C >::empty() const noexcept
{
  return size_ == 0;
}

template< typename K, typename V, typename C >
std::size_t turkin::RBtree< K, V, C >::size() const noexcept
{
  return size_;
}

#endif
