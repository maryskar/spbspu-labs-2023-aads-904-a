#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <utility>  
#include <functional>
#include "tree.hpp"

template< typename Key, typename Value, typename Compare = std::less< > >
class AVLTree
{
  public:
    using data_t = std::pair< Key, Value >;
    AVLTree();
    void insert(Key key, Value value);
    Tree< data_t >* node_;
    Compare comp_;
  private:
    Tree< data_t >* insert(Key key, Value value, Tree< data_t >* tree);
};

template< typename Key, typename Value, typename Compare >
AVLTree< Key, Value, Compare >::AVLTree():
  node_(nullptr),
  comp_()
{
}

template<typename Key, typename Value, typename Compare>
Tree< typename AVLTree< Key, Value, Compare >::data_t >* AVLTree< Key, Value, Compare >::insert(Key key, Value value, Tree<data_t>* tree)
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
      tree->height_ = 1 + std::max(getHeight(tree->left_), getHeight(tree->right_));
      return tree->left_;
    }
    auto temp = insert(key, value, tree->left_);
    tree->height_ = 1 + std::max(getHeight(tree->left_), getHeight(tree->right_));
    return temp;
  }
}

template< typename Key, typename Value, typename Compare >
void AVLTree< Key, Value, Compare >::insert(Key key, Value value)
{
  insert(key, value, node_);
}

#endif