#include <iostream>
#include "avltree.hpp"

template<typename Key, typename Value>
void inOrderTraversal(Tree<std::pair<Key, Value>>* node)
{
  if (node)
  {
    inOrderTraversal(node->left_);
    std::cout << node->data_.first << " " << node->data_.second << " " << node->height_ << "\n";
    inOrderTraversal(node->right_);
  }
}

template<typename Key, typename Value>
void printTree(Tree<std::pair<Key, Value>>* node, int indent = 0)
{
  if (node)
  {
    printTree(node->right_, indent + 4);
    std::cout << std::string(indent, ' ') << node->data_.first << "\n";
    printTree(node->left_, indent + 4);
  }
}

int main() {
    AVLTree<int, std::string> avlTree;
    avlTree.insert(5, "five");
    avlTree.insert(3, "three");
    avlTree.insert(7, "seven");
    avlTree.insert(2, "two");
    avlTree.insert(4, "four");
    avlTree.insert(8, "eight");
    avlTree.insert(10, "ten");
    avlTree.insert(9, "nine");
    avlTree.erase(9);
    printTree(avlTree.node_);
  
    inOrderTraversal(avlTree.node_);
    return 0;
}
