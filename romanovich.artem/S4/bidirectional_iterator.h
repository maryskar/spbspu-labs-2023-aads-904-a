#ifndef BIDIRECTIONAL_ITERATOR_H
#define BIDIRECTIONAL_ITERATOR_H
#include <iterator>
#include "tree_node.h"
template< typename Key, typename Value, typename Compare >
class BidirectionalIterator
{
public:
  using iterator_category = std::bidirectional_iterator_tag;
  BidirectionalIterator(TreeNode< Key, Value > *node, TreeNode< Key, Value > *fakeNode);
  BidirectionalIterator &operator++();
  BidirectionalIterator operator++(int);
  BidirectionalIterator &operator--();
  BidirectionalIterator operator--(int);
};
#endif
