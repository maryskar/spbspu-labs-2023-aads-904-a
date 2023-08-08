#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <cstddef>
#include <algorithm>

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
      AVLtree(); //done
      AVLtree(const tree & rhs); //done
      AVLtree(tree && rhs); //done
      tree operator=(const tree & rhs); //done
      tree operator=(tree && rhs); //done
      ~AVLtree(); //done
      
      it root() noexcept; //done
      cit root() const noexcept; //done
      cit croot() const noexcept; //done

      it begin() noexcept; //done
      cit begin() const noexcept; //done
      cit cbegin() const noexcept; //done

      it end() noexcept; //done
      cit end() const noexcept; //done
      cit cend() const noexcept; //done

      V & at(const K & key);
      const V & at(const K & key) const;
      V & operator[](const K & key);

      it insert(const K & k, const V & v); //done
      it insert(const tree_t & value); //done
      template< class It >
      It insert(It first, It last); //done

      it erase(const K & k);
      it erase(it pos); //base
      it erase(cit pos);
      it erase(cit first, cit last);

      it lower_bound(const K & key);
      cit lower_bound(const K & key) const;
      it upper_bound(const K & key);
      cit upper_bound(const K & key) const;

      std::size_t count(const K & key) const; //done
      it find(const K & key); //done
      cit find(const K & key) const;

      bool empty() const noexcept; //done
      std::size_t size() const noexcept; //done
      void clear() noexcept; //done
      void swap(tree & rhs) noexcept; //done
      
    private:
      node_t root_;
      C cmp_;
      std::size_t size_;

      void slr(node_t src); //done
      void srr(node_t src); //done

      void copy(const tree & rhs); //done
      void free(node_t src); //done
      it insert(node_t src, const tree_t & value); //done
      it erase(node_t src, const K & k);
      void balance(node_t src); //done
      void increase(node_t src); //done
      int measure(node_t src); //done
      int discern(node_t src); //done
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
  root_(rhs.root_),
  cmp_(rhs.cmp_),
  size_(rhs.size_)
{
  rhs.root_ = nullptr;
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
}

template< typename K, typename V, typename C >
turkin::Iterator< K, V, C > turkin::AVLtree< K, V, C >::root() noexcept
{
  return it(root_);
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
  while (temp->left != nullptr)
  {
    temp = temp->left;
  }
  return it(temp);
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
  while (temp->left != nullptr)
  {
    temp = temp->left;
  }
  return cit(temp);
}

template< typename K, typename V, typename C >
turkin::Iterator< K, V, C > turkin::AVLtree< K, V, C >::end() noexcept
{
  node_t temp = root_;
  while (temp->right != nullptr)
  {
    temp = temp->right;
  }
  return it(temp);
}

template< typename K, typename V, typename C >
turkin::ConstIterator< K, V, C > turkin::AVLtree< K, V, C >::end() const noexcept
{
  return cend();
}

template< typename K, typename V, typename C >
turkin::ConstIterator< K, V, C > turkin::AVLtree< K, V, C >::cend() const noexcept
{
  node_t temp = root_;
  while (temp->right != nullptr)
  {
    temp = temp->right;
  }
  return cit(temp);
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
    root_ = new TreeNode< tree_t > {value, nullptr, nullptr, nullptr, 0};
    increase(root_);
    return root();
  }
  return insert(root_, value);
}

template< typename K, typename V, typename C >
template< class It >
It turkin::AVLtree< K, V, C >::insert(It first, It last)
{
  for (auto it : *this)
  {
    insert(it);
  }
  return last;
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
  return cit(find(key));
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
  insert(rhs.begin(), rhs.end());
}

template< typename K, typename V, typename C >
void turkin::AVLtree< K, V, C >::free(node_t src)
{
  if (src == nullptr)
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
    if (src->left == nullptr)
    {
      src->left = new TreeNode< tree_t > {value, src, nullptr, nullptr, 0};
    }
    else
    {
      return insert(src->left, value);
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
      return insert(src->right, value);
    }
  }

  increase(src);
  balance(src);

  return it(src);
}

template< typename K, typename V, typename C >
turkin::Iterator< K, V, C > turkin::AVLtree< K, V, C >::erase(node_t src, const K & k)
{
  if (src == nullptr)
  {
    return it(nullptr);
  }
  else if (cmp_(k, src->data.first))
  {
    src->left = erase(src->left, k);
  }
  //else if (!cmp_(k, src->data.first))
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
  return (src == nullptr) ? -1 : src->height;
}

template< typename K, typename V, typename C >
int turkin::AVLtree< K, V, C >::discern(node_t src)
{
  return (src == nullptr) ? 0 : measure(src->right) - measure(src->left);
}

#endif
