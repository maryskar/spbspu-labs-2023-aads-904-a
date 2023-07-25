#include <iostream>
#include "tree_node.h"
#include "bidirectional_iterator.h"
using intint = std::pair< int, int >;
// Function for creating the tree with elements
TreeNode< intint > *createTestTree()
{
  // Create a tree with elements
  //        5
  //      /   \
    //     3     7
  //    / \   / \
    //   2   4 6   8
  TreeNode< intint > *fakeNode = new TreeNode< intint >(intint(0, 0));
  TreeNode< intint > *root = new TreeNode< intint >(intint(5, 50));
  root->left = new TreeNode< intint >(intint(3, 30));
  root->right = new TreeNode< intint >(intint(7, 70));
  root->left->left = new TreeNode< intint >(intint(2, 20));
  root->left->right = new TreeNode< intint >(intint(4, 40));
  root->right->left = new TreeNode< intint >(intint(6, 60));
  root->right->right = new TreeNode< intint >(intint(8, 80));
  return root;
}
int main()
{
  TreeNode< intint > *root = createTestTree();
  BidirectionalIterator< int, int, std::less< int>> it(root, root, nullptr);

  // Prefix Increment Test
  ++it;
  std::cout << "Current key after prefix increment: " << it->first << std::endl; // Expect: 3

  // Postfix Increment Test
  BidirectionalIterator< int, int, std::less< int>> it_postfix = it++;
  std::cout << "Current key after postfix increment: " << it->first << std::endl; // Expect: 4
  std::cout << "Previous key after postfix increment: " << it_postfix->first << std::endl; // Expect: 3

  // Prefix Decrement Test
  --it;
  std::cout << "Current key after prefix decrement: " << it->first << std::endl; // Expect: 3

  // Postfix Decrement Test
  BidirectionalIterator< int, int, std::less< int>> it_postfix_decrement = it--;
  std::cout << "Current key after postfix decrement: " << it->first << std::endl; // Expect: 2
  std::cout << "Previous key after postfix decrement: " << it_postfix_decrement->first << std::endl; // Expect: 3

  delete root;
  return 0;
}
