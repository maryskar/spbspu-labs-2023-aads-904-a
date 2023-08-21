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
    AVLTree< size_t, std::string> avlTree;
    avlTree.insert(1, "1");
    avlTree.insert(2, "2");
    avlTree.insert(3, "3");
    avlTree.insert(4, "4");
    avlTree.insert(5, "5");
    avlTree.insert(6, "6");
    avlTree.insert(7, "7");
    avlTree.insert(8, "8");
    avlTree.insert(9, "9");
    avlTree.insert(10, "10");
    printTree(avlTree.node_);
    std::cout << "\n\n\n\n";
    avlTree.erase(10);
    avlTree.erase(9);
    avlTree.erase(8);
    printTree(avlTree.node_);
    std::cout << "\n\n\n\n";
    inOrderTraversal(avlTree.node_);
    for (auto iter = avlTree.cbegin(); iter != avlTree.cend(); iter++)
    {
      std::cout << avlTree.at((*iter).first) << "\n";
    }
    using dict_t = AVLTree< size_t, std::string >;
    AVLTree< std::string, dict_t > dict_of_dict; 
    dict_of_dict.insert("test", avlTree);
    return 0;
}
