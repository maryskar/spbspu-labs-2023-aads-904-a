#ifndef AVLTREECONSTITERATOR
#define AVLTREECONSTITERATOR

#include <utility>

template< typename T >
class Tree;

template< typename Key, typename Value, typename Compare >
class AVLTree;

template< typename Key, typename Value, typename Compare >
class AVLTreeConstIterator;

template< typename Key, typename Value, typename Compare >
class AVLTreeConstIterator
{
  public:
    using data_t = std::pair< Key, Value >;
    AVLTreeConstIterator();
    ~AVLTreeConstIterator() = default;
  private:
    Tree< data_t >* ptr_;
};

template< typename Key, typename Value, typename Compare >
AVLTreeConstIterator< Key, Value, Compare >::AVLTreeConstIterator():
  ptr_(nullptr)
{
}

#endif