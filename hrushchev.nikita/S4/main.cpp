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
    avlTree.insert(10, "10");
    avlTree.insert(8, "8");
    avlTree.insert(15, "15");
    avlTree.insert(12, "12");
    avlTree.insert(16, "16");
    printTree(avlTree.node_);
    std::cout << "\n\n\n\n";
    avlTree.rotateLeft(avlTree.node_);
    avlTree.rotateRight(avlTree.node_);
    printTree(avlTree.node_);
    std::cout << "\n\n\n\n";
    inOrderTraversal(avlTree.node_);
    for (auto iter = avlTree.cbegin(); iter != avlTree.cend(); iter++)
    {
      std::cout << *iter << "\n";
    }
    return 0;
}
