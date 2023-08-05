#include <iostream>
#include "rotatable_binary_search_tree.h"
int main()
{
  romanovich::RotatableBinarySearchTree< int, int, std::less< int > > rotatableBinarySearchTree;

  // Тест insert
  rotatableBinarySearchTree.insert({1, 10});
  rotatableBinarySearchTree.insert({2, 20});
  if (rotatableBinarySearchTree.size() != 2)
  {
    std::cout << "Test insert failed" << std::endl;
    return 1;
  }

  // Тест find
  auto it = rotatableBinarySearchTree.find({2, 20});
  if (it == rotatableBinarySearchTree.end())
  {
    std::cout << "Test find failed" << std::endl;
    return 1;
  }

  // Тест erase
  rotatableBinarySearchTree.erase({1, 10});
  if (rotatableBinarySearchTree.size() != 1)
  {
    std::cout << "Test erase failed" << std::endl;
    return 1;
  }

  // Тест rotate
/*  auto node = rotatableBinarySearchTree.begin().node();
  rotatableBinarySearchTree.rotateLeftLeft(node);
  if (node->parent != nullptr)
  {
    std::cout << "Test rotate failed" << std::endl;
    return 1;
  }
  std::cout << "All tests passed!" << std::endl;
  return 0;*/
}