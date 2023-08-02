#ifndef ITERATOR_DTO_H
#define ITERATOR_DTO_H
#include <utility>
#include "tree_node.h"
template< typename T >
struct IteratorDto
{
  const TreeNode< T > *root;
  const TreeNode< T > *node;
  const TreeNode< T > *fakeNode;
};
// to bi
#endif
