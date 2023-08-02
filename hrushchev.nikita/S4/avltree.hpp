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
};

template< typename Key, typename Value, typename Compare >
AVLTree< Key, Value, Compare >::AVLTree():
  node_(nullptr),
  comp_()
{
}

template< typename Key, typename Value, typename Compare >
void AVLTree< Key, Value, Compare >::insert(Key key, Value value)
{
  if (!node_)
  {
    node_ = new Tree< data_t >();
    node_->data_ = data_t(key, value);
    return
  }
}

#endif