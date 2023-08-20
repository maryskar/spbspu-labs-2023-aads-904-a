#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <utility>
#include <functional>

#include "tree.hpp"
#include "avltreeiterator.hpp"
#include "avltreeconstiterator.hpp"

template< typename Key, typename Value, typename Compare = std::less< > >
class AVLTree
{
  public:
    using data_t = std::pair< Key, Value >;
    using iterator = AVLTreeIterator< Key, Value, Compare >;
    using const_iterator = AVLTreeConstIterator< Key, Value, Compare >;
    AVLTree();
    void insert(const Key& key, const Value& value);
    void erase(const Key& key);
    Value& at(const Key& key);
    bool empty();
    iterator begin();
    const_iterator cbegin();
    iterator end();
    const_iterator cend();
    Tree< data_t >* node_;
    Compare comp_;
  private:
    void updateHeight(Tree< data_t >* tree);
    Tree< data_t >* insert(const Key& key, const Value& value, Tree< data_t >* tree);
    Tree< data_t >* find(const Key& key);
    void erase(Tree< data_t >* tree);
    void rotateLeft(Tree< data_t >* node);
    void rotateRight(Tree< data_t >* node);
    void rotateRightLeft(Tree< data_t >* node);
    void rotateLeftRight(Tree< data_t >* node);
    void balance(Tree< data_t >* node);
};

template< typename Key, typename Value, typename Compare >
AVLTree< Key, Value, Compare >::AVLTree():
  node_(nullptr),
  comp_()
{
}

template< typename Key, typename Value, typename Compare >
void AVLTree< Key, Value, Compare >::insert(const Key& key, const Value& value)
{
  auto to_balance = insert(key, value, node_);
  balance(to_balance);
}

template< typename Key, typename Value, typename Compare >
void AVLTree< Key, Value, Compare >::erase(const Key& key)
{
  erase(find(key));
  balance(node_);
}

template< typename Key, typename Value, typename Compare >
Value& AVLTree< Key, Value, Compare >::at(const Key& key)
{
  for (auto cur = begin(); cur != end(); cur++)
  {
    if (cur->first == key)
    {
      return cur->second;
    }
  }
  throw std::out_of_range("No such key in dictionary");
}

template< typename Key, typename Value, typename Compare >
bool AVLTree< Key, Value, Compare >::empty()
{
  return node_ == nullptr;
}

template< typename Key, typename Value, typename Compare >
typename AVLTree< Key, Value, Compare >::iterator AVLTree< Key, Value, Compare >::begin()
{
  return iterator(getMin(node_));
}
template< typename Key, typename Value, typename Compare >
typename AVLTree< Key, Value, Compare >::const_iterator AVLTree< Key, Value, Compare >::cbegin()
{
  return const_iterator(getMin(node_));
}

template< typename Key, typename Value, typename Compare >
typename AVLTree< Key, Value, Compare >::iterator AVLTree< Key, Value, Compare >::end()
{
  return iterator(getMax(node_)->right_);
}

template< typename Key, typename Value, typename Compare >
typename AVLTree< Key, Value, Compare >::const_iterator AVLTree< Key, Value, Compare >::cend()
{
  return const_iterator(getMax(node_)->right_);
}

template<typename Key, typename Value, typename Compare>
void AVLTree<Key, Value, Compare>::updateHeight(Tree< data_t >* tree)
{
  if (!tree)
  {
    return;
  }
  tree->height_ = 1 + std::max(getHeight(tree->left_), getHeight(tree->right_));
}

template<typename Key, typename Value, typename Compare>
Tree< typename AVLTree< Key, Value, Compare >::data_t >* AVLTree< Key, Value, Compare >::insert(const Key& key,
    const Value & value, Tree< data_t >* tree)
{
  if (!node_)
  {
    node_ = new Tree< data_t >();
    node_->data_ = data_t(key, value);
    node_->height_ = 1;
    return node_;
  }
  if (comp_(tree->data_.first, key))
  {
    if (!tree->right_)
    {
      auto temp = new Tree< data_t >();
      temp->data_ = data_t(key, value);
      temp->height_ = 1;
      tree->right_ = temp;
      temp->head_ = tree;
      updateHeight(tree);
      return tree->right_;
    }
    auto temp = insert(key, value, tree->right_);
    updateHeight(tree);
    return temp;
  }
  else
  {
    if (!tree->left_)
    {
      auto temp = new Tree< data_t >();
      temp->data_ = data_t(key, value);
      temp->height_ = 1;
      tree->left_ = temp;
      temp->head_ = tree;
      updateHeight(tree);
      return tree->left_;
    }
    auto temp = insert(key, value, tree->left_);
    updateHeight(tree);
    return temp;
  }
}

template< typename Key, typename Value, typename Compare >
Tree< typename AVLTree< Key, Value, Compare >::data_t >* AVLTree< Key, Value, Compare >::find(const Key& key)
{
  for (auto cur = begin(); cur != end(); cur++)
  {
    if (cur->first == key)
    {
      return cur.ptr_;
    }
  }
  throw std::out_of_range("No such key in dictionary");
}

template<typename Key, typename Value, typename Compare>
void AVLTree< Key, Value, Compare >::erase(Tree< typename AVLTree< Key, Value, Compare >::data_t >* tree)
{
  if (!tree)
  {
    return;
  }
  if (!tree->right_ && !tree->left_)
  {
    if (!tree->head_)
    {
      delete tree;
      node_ = nullptr;
      return;
    }
    if (tree->head_->left_ == tree)
    {
      tree->head_->left_ = nullptr;
    }
    else
    {
      tree->head_->right_ = nullptr;
    }
    delete tree;
    updateHeight(tree->head_);
    balance(tree->head_);
    return;
  }
  if (!tree->right_ || !tree->left_)
  {
    Tree< data_t >* child = (tree->left_ == nullptr) ? tree->right_ : tree->left_;
    if (!tree->head_)
    {
      node_ = child;
      node_->head_ = nullptr;
    }
    else if (tree->head_->left_ == tree)
    {
      tree->head_->left_ = child;
      child->head_ = tree->head_;
    }
    else
    {
      tree->head_->right_ = child;
      child->head_ = tree->head_;
    }
    delete tree;
    updateHeight(child->head_);
    balance(child->head_);
    return;
  }
  Tree<data_t>* maxNode = getMax(tree->left_);
  tree->data_ = maxNode->data_;
  erase(maxNode);
  updateHeight(tree->head_);
  balance(tree->head_);
}

template<typename Key, typename Value, typename Compare>
void AVLTree< Key, Value, Compare >::rotateLeft(Tree< data_t >* node)
{
  Tree< data_t >* new_root = node->right_;
  node->right_ = new_root->left_;
  if (new_root->left_)
  {
    new_root->left_->head_ = node;
  }
  new_root->head_ = node->head_;
  if (node->head_)
  {
    if (node->head_->left_ == node)
    {
      node->head_->left_ = new_root;
    }
    else
    {
      node->head_->right_ = new_root;
    }
  }
  else
  {
    node_ = new_root;
  }
  new_root->left_ = node;
  node->head_ = new_root;
  updateHeight(node);
  updateHeight(new_root);
}

template< typename Key, typename Value, typename Compare >
void AVLTree< Key, Value, Compare >::rotateRight(Tree< data_t >* node)
{
  Tree< data_t >* new_root = node->left_;
  node->left_ = new_root->right_;
  if (new_root->right_)
  {
    new_root->right_->head_ = node;
  }
  new_root->head_ = node->head_;
  if (node->head_)
  {
    if (node->head_->left_ == node)
    {
      node->head_->left_ = new_root;
    }
    else
    {
      node->head_->right_ = new_root;
    }
  }
  else
  {
    node_ = new_root;
  }
  new_root->right_ = node;
  node->head_ = new_root;
  updateHeight(node);
  updateHeight(new_root);
}

template< typename Key, typename Value, typename Compare >
void AVLTree< Key, Value, Compare >::rotateRightLeft(Tree< data_t >* node)
{
  rotateRight(node);
  rotateLeft(node);
}

template< typename Key, typename Value, typename Compare >
void AVLTree< Key, Value, Compare >::rotateLeftRight(Tree< data_t >* node)
{
  rotateLeft(node);
  rotateRight(node);
}

template< typename Key, typename Value, typename Compare >
void AVLTree< Key, Value, Compare >::balance(Tree< data_t >* node)
{
  if (!node)
  {
    return;
  }
  int balanceFactor = getHeight(node->left_) - getHeight(node->right_);

  if (balanceFactor > 1)
  {
    if (getHeight(node->left_->left_) >= getHeight(node->left_->right_))
    {
      rotateRight(node);
    }
    else
    {
      rotateLeftRight(node);
    }
  }
  else if (balanceFactor < -1)
  {
    if (getHeight(node->right_->right_) >= getHeight(node->right_->left_))
    {
      rotateLeft(node);
    }
    else
    {
      rotateRightLeft(node);
    }
  }
  balance(node->head_);
}

#endif
