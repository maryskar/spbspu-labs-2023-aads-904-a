#ifndef ITERATOR_DTO_H
#define ITERATOR_DTO_H
#include <utility>
#include "tree_node.h"
template< typename Key, typename Value >
struct IteratorDto
{
  const TreeNode< std::pair< Key, Value > > *root;
  const TreeNode< std::pair< Key, Value > > *node;
  const TreeNode< std::pair< Key, Value > > *fakeNode;
};
#endif
