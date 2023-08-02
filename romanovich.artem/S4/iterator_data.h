#ifndef ITERATOR_DATA_H
#define ITERATOR_DATA_H
#include <utility>
#include "tree_node.h"
template< typename T >
struct IteratorData
{
  const TreeNode< T > *root;
  const TreeNode< T > *node;
  const TreeNode< T > *fakeNode;
};
#endif
