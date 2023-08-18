#ifndef AVLTREECONSTITERATOR
#define AVLTREECONSTITERATOR

#include <utility>

template< typename T >
class Tree;

template< typename Key, typename Value, typename Compare >
class AVLTree;

template< typename Key, typename Value, typename Compare >
class AVLTreeIterator;

template< typename Key, typename Value, typename Compare >
class AVLTreeConstIterator
{
  friend class AVLTree< Key, Value, Compare >;
  friend class AVLTreeIterator< Key, Value, Compare >;
  public:
    using data_t = std::pair< Key, Value >;
    AVLTreeConstIterator();
    explicit AVLTreeConstIterator(Tree< data_t >* rhs);
    AVLTreeConstIterator(const AVLTreeIterator< Key, Value, Compare >& rhs);
    ~AVLTreeConstIterator() = default;
  private:
    Tree< data_t >* ptr_;
};

template< typename Key, typename Value, typename Compare >
AVLTreeConstIterator< Key, Value, Compare >::AVLTreeConstIterator():
  ptr_(nullptr)
{
}

template< typename Key, typename Value, typename Compare >
AVLTreeConstIterator< Key, Value, Compare >::AVLTreeConstIterator(Tree< data_t >* rhs):
  ptr_(rhs)
{
}

template< typename Key, typename Value, typename Compare >
AVLTreeConstIterator< Key, Value, Compare >::AVLTreeConstIterator(const AVLTreeIterator< Key, Value, Compare >& rhs):
  ptr_(rhs.ptr_)
{
}

#endif