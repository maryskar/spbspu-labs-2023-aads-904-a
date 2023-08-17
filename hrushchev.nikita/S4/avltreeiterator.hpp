#ifndef AVLTREEITERATOR_HPP
#define AVLTREEITERATOR_HPP

#include <utility>

template< typename T  >
class Tree;

template< typename Key, typename Value, typename Compare >
class AVLTree;

template< typename Key, typename Value, typename Compare >
class AVLTreeIterator
{
  friend class AVLTree< Key, Value, Compare >;
  public:
    using data_t = std::pair< Key, Value >;
    AVLTreeIterator();
    explicit AVLTreeIterator(Tree< data_t >* rhs);
    ~AVLTreeIterator() = default;
  private:
    Tree< data_t >* ptr_;
};

template< typename Key, typename Value, typename Compare >
AVLTreeIterator< Key, Value, Compare >::AVLTreeIterator():
  ptr_(nullptr)
{
}

template< typename Key, typename Value, typename Compare >
AVLTreeIterator< Key, Value, Compare >::AVLTreeIterator(Tree< typename AVLTreeIterator< Key, Value, Compare >::data_t >* rhs):
  ptr_(rhs)
{
}

#endif
