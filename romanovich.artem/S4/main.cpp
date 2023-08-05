#include <iostream>
#include "rotatable_binary_search_tree.h"
int main()
{
  romanovich::RotatableBinarySearchTree< int, int > bst;

  // Вставка узлов
  bst.insert({4, 40});
  bst.insert({2, 20});
  bst.insert({6, 60});
  bst.insert({1, 10});
  bst.insert({3, 30});
  bst.insert({5, 50});
  bst.insert({7, 70});

  // Проверка порядка обхода
  int prev = 0;
  for (auto &node: bst)
  {
    if (node.first <= prev)
    {
      std::cout << "Wrong order!" << std::endl;
      return 1;
    }
    prev = node.first;
  }

  bst.printNode(bst.getBst().getRoot(), false, "");

  // Вращение влево-влево в корне
  auto root = bst.getBst().getRoot();
  bst.rotateLeftLeft(root);

  bst.printNode(bst.getBst().getRoot(), false, "");

  // Проверка нового корня
  if (bst.getBst().getRoot()->data.first != 2)
  {
    std::cout << "Root check failed!" << std::endl;
    return 1;
  }

  // Проверка порядка обхода после вращения
  prev = 0;
  for (auto &node: bst)
  {
    if (node.first <= prev)
    {
      std::cout << "Wrong order after rotation!" << std::endl;
      return 1;
    }
    prev = node.first;
  }
  std::cout << "All tests passed!" << std::endl;
  return 0;
}