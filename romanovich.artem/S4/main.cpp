#include <iostream>
#include "redblack_tree.h"
void insertAndPrint(romanovich::RedBlackTree< int, int, std::less<> > &rbTree, int i)
{
  rbTree.insert({i, 10 * i});
  rbTree.rotBst_.printNode(rbTree.rotBst_.bst_.root_, false, "");
  std::cout << "-------------\n";
}
int main()
{
  // Создаем красно-черное дерево для целых чисел
  romanovich::RedBlackTree< int, int, std::less<> > rbTree;
//  insertAndPrint(rbTree, 24);
//  insertAndPrint(rbTree, 5);
//  insertAndPrint(rbTree, 1);

  insertAndPrint(rbTree, 1);
  insertAndPrint(rbTree, 3);
  insertAndPrint(rbTree, 4);
  insertAndPrint(rbTree, 7);
  insertAndPrint(rbTree, 10);
  insertAndPrint(rbTree, 13);
  insertAndPrint(rbTree, 1000);

  // Выводим элементы дерева в возрастающем порядке
  for (const auto &node: rbTree)
  {
    std::cout << "Key: " << node.first << ", Value: " << node.second << std::endl;
  }
  return 0;
}
