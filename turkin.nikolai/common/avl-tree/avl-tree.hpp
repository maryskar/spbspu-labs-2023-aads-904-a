#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <cstddef>
#include <algorithm>
#include <stdexcept>

#include "iterators/iterator.hpp"
#include "iterators/const-iterator.hpp"
#include "tree-node.hpp"
#include "comparator.hpp"

namespace turkin
{
  template< typename K, typename V, typename C >
  class AVLtree
  {
    using tree = AVLtree< K, V, C >;
    using tree_t = std::pair< K, V >;
    using node_t = TreeNode< tree_t > *;
    using it = Iterator< K, V, C >;
    using cit = ConstIterator< K, V, C >;
    public:
      AVLtree();
      AVLtree(const tree & rhs);
      AVLtree(tree && rhs);
      tree operator=(const tree & rhs);
      tree operator=(tree && rhs);
      ~AVLtree();

      it root() noexcept;
      cit root() const noexcept;
      cit croot() const noexcept;

      it begin() noexcept;
      cit begin() const noexcept;
      cit cbegin() const noexcept;

      it end() noexcept;
      cit end() const noexcept;
      cit cend() const noexcept;

      V & at(const K & key);
      const V & at(const K & key) const;
      V & operator[](const K & key);

      it insert(const K & k, const V & v);
      it insert(const tree_t & value);
      template< class It >
      It insert(It first, It last);

      it erase(const K & k);
      it erase(it pos);
      it erase(cit pos);
      it erase(cit first, cit last);

      it lower_bound(const K & key);
      cit lower_bound(const K & key) const;
      it upper_bound(const K & key);
      cit upper_bound(const K & key) const;

      std::size_t count(const K & key) const;
      it find(const K & key);
      cit find(const K & key) const;

      bool empty() const noexcept;
      std::size_t size() const noexcept;
      void clear() noexcept;
      void swap(tree & rhs) noexcept;

    private:
      node_t root_;
      node_t tail_;
      C cmp_;
      std::size_t size_;

      void slr(node_t src);
      void srr(node_t src);

      void copy(const tree & rhs);
      void free(node_t src);
      it insert(node_t src, const tree_t & value);
      node_t erase(node_t src, const K & k);
      void balance(node_t src);
      void increase(node_t src);
      int measure(node_t src);
      int discern(node_t src);
  };
}

template< typename K, typename V, typename C >
turkin::AVLtree< K, V, C >::AVLtree():
  root_(nullptr),
  tail_(new TreeNode< tree_t >),
  cmp_(),
  size_(0)
{}

template< typename K, typename V, typename C >
turkin::AVLtree< K, V, C >::AVLtree(const tree & rhs):
  root_(nullptr),
  tail_(nullptr),
  cmp_(rhs.cmp_),
  size_(rhs.size_)
{
  copy(rhs);
}

template< typename K, typename V, typename C >
turkin::AVLtree< K, V, C >::AVLtree(tree && rhs):
  root_(rhs.root_),
  tail_(rhs.tail_),
  cmp_(rhs.cmp_),
  size_(rhs.size_)
{
  rhs.root_ = nullptr;
  rhs.tail_ = nullptr;
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
  root_ = rhs.root_;
  tail_ = rhs.tail_;
  cmp_ = rhs.cmp_;
  size_ = rhs.size_;
  rhs.root_ = nullptr;
  rhs.size_ = 0;
  return * this;
}

template< typename K, typename V, typename C >
turkin::AVLtree< K, V, C >::~AVLtree()
{
  free(root_);
  delete tail_;
}

template< typename K, typename V, typename C >
turkin::Iterator< K, V, C > turkin::AVLtree< K, V, C >::root() noexcept
{
  return it(root_, tail_);
}

template< typename K, typename V, typename C >
turkin::ConstIterator< K, V, C > turkin::AVLtree< K, V, C >::root() const noexcept
{
  return croot();
}

template< typename K, typename V, typename C >
turkin::ConstIterator< K, V, C > turkin::AVLtree< K, V, C >::croot() const noexcept
{
  return cit(root());
}

template< typename K, typename V, typename C >
turkin::Iterator< K, V, C > turkin::AVLtree< K, V, C >::begin() noexcept
{
  node_t temp = root_;
  while (temp->left != tail_)
  {
    temp = temp->left;
  }
  return it(temp, tail_);
}

template< typename K, typename V, typename C >
turkin::ConstIterator< K, V, C > turkin::AVLtree< K, V, C >::begin() const noexcept
{
  return cbegin();
}

template< typename K, typename V, typename C >
turkin::ConstIterator< K, V, C > turkin::AVLtree< K, V, C >::cbegin() const noexcept
{
  node_t temp = root_;
  while (temp->left != tail_)
  {
    temp = temp->left;
  }
  return cit(temp, tail_);
}

template< typename K, typename V, typename C >
turkin::Iterator< K, V, C > turkin::AVLtree< K, V, C >::end() noexcept
{
  return it(tail_, tail_);
}

template< typename K, typename V, typename C >
turkin::ConstIterator< K, V, C > turkin::AVLtree< K, V, C >::end() const noexcept
{
  return cend();
}

template< typename K, typename V, typename C >
turkin::ConstIterator< K, V, C > turkin::AVLtree< K, V, C >::cend() const noexcept
{
  return cit(tail_, tail_);
}

template< typename K, typename V, typename C >
V & turkin::AVLtree< K, V, C >::at(const K & key)
{
  auto ins = find(key);
  if (neq< K, C >(ins->first, key))
  {
    throw std::out_of_range("out of range");
  }
  return ins->second;
}

template< typename K, typename V, typename C >
const V & turkin::AVLtree< K, V, C >::at(const K & key) const
{
  auto ins = find(key);
  if (neq< K, C >(ins->first, key))
  {
    throw std::out_of_range("out of range");
  }
  return ins->second;
}

template< typename K, typename V, typename C >
V & turkin::AVLtree< K, V, C >::operator[](const K & key)
{
  it ins = find(key);
  return (ins == end()) ? insert(tree_t(key, V()))->second : ins->second;
}

template< typename K, typename V, typename C >
turkin::Iterator< K, V, C > turkin::AVLtree< K, V, C >::insert(const K & k, const V & v)
{
  return insert(std::make_pair(k, v));
}

template< typename K, typename V, typename C >
turkin::Iterator< K, V, C > turkin::AVLtree< K, V, C >::insert(const tree_t & value)
{
  size_++;
  if (empty())
  {
    root_ = new TreeNode< tree_t > {value, tail_, tail_, tail_, 0};
    increase(root_);
    return root();
  }
  return insert(root_, value);
}

template< typename K, typename V, typename C >
template< class It >
It turkin::AVLtree< K, V, C >::insert(It first, It last)
{
  for (auto it = first; it != last; it++)
  {
    insert(*it);
  }
  return last;
}

template< typename K, typename V, typename C >
turkin::Iterator< K, V, C > turkin::AVLtree< K, V, C >::erase(const K & k)
{
  if (empty())
  {
    return it(tail_, tail_);
  }
  return it(erase(root_, k), tail_);
}

template< typename K, typename V, typename C >
turkin::Iterator< K, V, C > turkin::AVLtree< K, V, C >::erase(it pos)
{
  if (empty())
  {
    return it(tail_, tail_);
  }
  size_--;
  return it(erase(pos.cur_, pos->first), tail_);
}

template< typename K, typename V, typename C >
turkin::Iterator< K, V, C > turkin::AVLtree< K, V, C >::erase(cit pos)
{
  return cit(erase(it(pos.cur_)), tail_);
}

template< typename K, typename V, typename C >
turkin::Iterator< K, V, C > turkin::AVLtree< K, V, C >::erase(cit first, cit last)
{
  for (auto it = first; it != last; it++)
  {
    erase(it);
  }
  return it(last.cur_, tail_);
}

template< typename K, typename V, typename C >
turkin::Iterator< K, V, C > turkin::AVLtree< K, V, C >::lower_bound(const K & key)
{
  auto ins = root();
  while (ins != end())
  {
    if (eq< K, C >(key, ins->first))
    {
      return ins;
    }
    else if (cmp_(key, ins->first))
    {
      ins++;
    }
    else
    {
      ins--;
    }
  }
  return end();
}

template< typename K, typename V, typename C >
turkin::ConstIterator< K, V, C > turkin::AVLtree< K, V, C >::lower_bound(const K & key) const
{
  return cit(lower_bound(key), tail_);
}

template< typename K, typename V, typename C >
turkin::Iterator< K, V, C > turkin::AVLtree< K, V, C >::upper_bound(const K & key)
{
  auto ins = lower_bound(key);
  if (ins == end())
  {
    return end();
  }
  return (eq< K, V >(key, ins->first)) ? ins++ : ins;
}

template< typename K, typename V, typename C >
turkin::ConstIterator< K, V, C > turkin::AVLtree< K, V, C >::upper_bound(const K & key) const
{
  return cit(upper_bound(key), tail_);
}

template< typename K, typename V, typename C >
std::size_t turkin::AVLtree< K, V, C >::count(const K & key) const
{
  std::size_t amount = 0;
  for (auto ins : *this)
  {
    if (eq< K, C >(key, ins.first))
    {
      amount++;
    }
  }
  return amount;
}

template< typename K, typename V, typename C >
turkin::Iterator< K, V, C > turkin::AVLtree< K, V, C >::find(const K & key)
{
  auto ins = begin();
  for(; ins != end() && neq< K, C >(key, ins->first); ins++);
  return ins;
}

template< typename K, typename V, typename C >
turkin::ConstIterator< K, V, C > turkin::AVLtree< K, V, C >::find(const K & key) const
{
  return cit(find(key), tail_);
}

template< typename K, typename V, typename C >
bool turkin::AVLtree< K, V, C >::empty() const noexcept
{
  return root_ == nullptr;
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
  delete tail_;
  tail_ = nullptr;
  root_ = nullptr;
}

template< typename K, typename V, typename C >
void turkin::AVLtree< K, V, C >::swap(tree & rhs) noexcept
{
  std::swap(root_, rhs.root_);
  std::swap(cmp_, rhs.cmp_);
}

template< typename K, typename V, typename C >
void turkin::AVLtree< K, V, C >::slr(node_t src)
{
  auto head = src->right;
  if (src == root_)
  {
    root_ = head;
  }
  src->right = src->right->left;
  head->left = src;
  src->parent = head;
  increase(src);
  increase(head);
}

template< typename K, typename V, typename C >
void turkin::AVLtree< K, V, C >::srr(node_t src)
{
  auto head = src->left;
  if (src == root_)
  {
    root_ = head;
  }
  src->left = src->left->right;
  head->right = src;
  src->parent = head;
  increase(src);
  increase(head);
}

template< typename K, typename V, typename C >
void turkin::AVLtree< K, V, C >::copy(const tree & rhs)
{
  tail_ = new TreeNode< tree_t >;
  insert(rhs.begin(), rhs.end());
}

template< typename K, typename V, typename C >
void turkin::AVLtree< K, V, C >::free(node_t src)
{
  if (src == tail_ || src == nullptr)
  {
    return;
  }
  free(src->left);
  free(src->right);
  delete src;
}

template< typename K, typename V, typename C >
turkin::Iterator< K, V, C > turkin::AVLtree< K, V, C >::insert(node_t src, const tree_t & value)
{
  if (cmp_(value.first, src->data.first))
  {
    if (src->left == tail_)
    {
      src->left = new TreeNode< tree_t > {value, src, tail_, tail_, 0};
    }
    else
    {
      return insert(src->left, value);
    }
  }
  else if (!cmp_(value.first, src->data.first))
  {
    if (src->right == tail_)
    {
      src->right = new TreeNode< tree_t > {value, src, tail_, tail_, 0};
    }
    else
    {
      return insert(src->right, value);
    }
  }

  increase(src);
  balance(src);

  return it(src, tail_);
}

template< typename K, typename V, typename C >
turkin::TreeNode< std::pair< K, V > > * turkin::AVLtree< K, V, C >::erase(node_t src, const K & k)
{
  if (src == tail_)
  {
    return tail_;
  }
  else if (cmp_(k, src->data.first))
  {
    src->left = erase(src->left, k);
  }
  else if (!cmp_(k, src->data.first))
  {
    src->right = erase(src->right, k);
  }
  else
  {
    if (src->left == tail_ || src->right == tail_)
    {
      src = (src->left == tail_) ? src->right : src->left;
    }
    else
    {
      node_t temp = src;
      for (;temp->right != tail_; temp = temp->right);
      src->data = temp->data;
      src->right = erase(src->right, temp->data.first);
    }
  }
  if (src != nullptr)
  {
    increase(src);
    balance(src);
  }
  return src;
}

template< typename K, typename V, typename C >
void turkin::AVLtree< K, V, C >::balance(node_t src)
{
  int diff = discern(src);
  if (diff == -2)
  {
    if (discern(src->left) == 1)
    {
      slr(src);
    }
    srr(src);
  }
  else if (diff == 2)
  {
    if (discern(src->right) == -1)
    {
      srr(src);
    }
    slr(src);
  }
}

template< typename K, typename V, typename C >
void turkin::AVLtree< K, V, C >::increase(node_t src)
{
  src->height = std::max(measure(src->left), measure(src->right)) + 1;
}

template< typename K, typename V, typename C >
int turkin::AVLtree< K, V, C >::measure(node_t src)
{
  return (src == tail_) ? -1 : src->height;
}

template< typename K, typename V, typename C >
int turkin::AVLtree< K, V, C >::discern(node_t src)
{
  return (src == tail_) ? 0 : measure(src->right) - measure(src->left);
}

#endif
