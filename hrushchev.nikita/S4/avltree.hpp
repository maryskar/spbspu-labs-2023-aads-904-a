#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <utility>  
#include <functional>
#include "tree.hpp"

#include <iostream>

template< typename Key, typename Value, typename Compare = std::less< > >
class AVLTree
{
  public:
    using data_t = std::pair< Key, Value >;
    AVLTree();
    void insert(const Key& key, const Value& value);
    void erase(const Key& key);
    Tree< data_t >* node_;
    Compare comp_;
  private:
    void updateHeight(Tree< data_t >* tree);
    Tree< data_t >* insert(const Key& key, const Value& value, Tree< data_t >* tree);
    Tree< data_t >* find(const Key& key, Tree< data_t >* tree);
    void erase(Tree< data_t >* tree);
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
  insert(key, value, node_);
}

template< typename Key, typename Value, typename Compare >
void AVLTree< Key, Value, Compare >::erase(const Key& key)
{
  erase(find(key, node_));
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
      tree->height_ = 1 + std::max(getHeight(tree->left_), getHeight(tree->right_));
      return tree->right_;
    }
    auto temp = insert(key, value, tree->right_);
    tree->height_ = 1 + std::max(getHeight(tree->left_), getHeight(tree->right_));
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
      tree->height_ = 1 + std::max(getHeight(tree->left_), getHeight(tree->right_));
      return tree->left_;
    }
    auto temp = insert(key, value, tree->left_);
    tree->height_ = 1 + std::max(getHeight(tree->left_), getHeight(tree->right_));
    return temp;
  }
}

template< typename Key, typename Value, typename Compare >
Tree< typename AVLTree< Key, Value, Compare >::data_t >* AVLTree< Key, Value, Compare >::find(const Key& key, Tree< data_t >* tree)
{
  if (!tree)
  {
    return nullptr;
  }
  if (!comp_(key, tree->data_.first))
  {
    if (key == tree->data_.first)
    {
      return tree;
    }
    return find(key, tree->right_);
  }
  else
  {
    if (key == tree->data_.first)
    {
      return tree;
    }
    return find(key, tree->left_);
  }
}

template<typename Key, typename Value, typename Compare>
void AVLTree<Key, Value, Compare>::erase(Tree<typename AVLTree<Key, Value, Compare>::data_t>* tree)
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
    //balance(tree->head_);
    return;
  }
  if (!tree->right_ || !tree->left_)
  {
    Tree<data_t>* child = (tree->left_ == nullptr) ? tree->right_ : tree->left_;
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
    //balance(child->head_);
    return;
  }
  
  Tree<data_t>* maxNode = getMax(tree->left_);
  tree->data_ = maxNode->data_;
  erase(maxNode);
  //balance(tree->head_);
}


#endif