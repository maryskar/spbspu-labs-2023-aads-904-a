#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <utility>  
#include "tree.hpp"

template< typename Key, typename Value, typename Compare >
class AVLTree
{
  public:
    using data_t = std::pair< Key, Value >;
    AVLTree();
    void insert(Key key, Value value);
    Tree< data_t >* tree_;
    Compare comp_;
};

template< typename Key, typename Value, typename Compare >
AVLTree< Key, Value, Compare >::AVLTree():
  tree_(nullptr),
  comp_()
{
}

#endif