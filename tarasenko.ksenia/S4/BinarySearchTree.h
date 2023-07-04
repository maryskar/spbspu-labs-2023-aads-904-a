#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <utility>

template< typename Key, typename Value, typename Compare >
class BinarySearchTree
{
 using BSTree = BinarySearchTree< Key, Value, Compare >;
public:
 BinarySearchTree():
   data_(),
   left_(nullptr),
   right_(nullptr),
   parent_(nullptr),
   compare_()
 {};
 ~BinarySearchTree()
 {};
 //insert(const std::pair< Key, Value >& data)
 //clear(BSTree** ptree)
 //leftRotation
 //rightRotation
private:
 std::pair< Key, Value > data_;
 BSTree* left_;
 BSTree* right_;
 BSTree* parent_;
 Compare compare_;
};

#endif
