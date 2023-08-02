#include <iostream>
#include "avltree.hpp"


template<typename Key, typename Value>
void inOrderTraversal(Tree<std::pair<Key, Value>>* node)
{
  if (node)
  {
    inOrderTraversal(node->left_);
    std::cout << node->data_.first << " " << node->data_.second << "\n";
    inOrderTraversal(node->right_);
  }
}

int main()
{
  AVLTree<int, std::string> avlTree;
  avlTree.insert(5, "five");
  avlTree.insert(3, "three");
  avlTree.insert(7, "seven");
  avlTree.insert(2, "two");
  avlTree.insert(4, "four");
  avlTree.insert(6, "six");
  avlTree.insert(8, "eight");


  inOrderTraversal(avlTree.node_);
  std::cout << "\n";
  return 0;
}
