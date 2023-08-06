#include <iostream>
#include "redblack_tree.h"
int main()
{
  // Создаем красно-черное дерево для целых чисел
  romanovich::RedBlackTree< int, int, std::less<> > rbTree;

  // Вставляем элементы в дерево
  rbTree.rotBst_.printNode(rbTree.rotBst_.bst_.root_, false, ""); std::cout << "-------------\n";
  rbTree.insert({10, 100}); rbTree.rotBst_.printNode(rbTree.rotBst_.bst_.root_, false, ""); std::cout << "-------------\n";
  rbTree.insert({5, 50});rbTree.rotBst_.printNode(rbTree.rotBst_.bst_.root_, false, ""); std::cout << "-------------\n";
  rbTree.insert({15, 150});rbTree.rotBst_.printNode(rbTree.rotBst_.bst_.root_, false, ""); std::cout << "-------------\n";
  rbTree.insert({3, 30});rbTree.rotBst_.printNode(rbTree.rotBst_.bst_.root_, false, ""); std::cout << "-------------\n";
  rbTree.insert({7, 70});rbTree.rotBst_.printNode(rbTree.rotBst_.bst_.root_, false, ""); std::cout << "-------------\n";
  rbTree.insert({12, 120});rbTree.rotBst_.printNode(rbTree.rotBst_.bst_.root_, false, ""); std::cout << "-------------\n";
  rbTree.insert({17, 170});rbTree.rotBst_.printNode(rbTree.rotBst_.bst_.root_, false, ""); std::cout << "-------------\n";
  rbTree.insert({2, 20});rbTree.rotBst_.printNode(rbTree.rotBst_.bst_.root_, false, ""); std::cout << "-------------\n";
  rbTree.insert({4, 40});rbTree.rotBst_.printNode(rbTree.rotBst_.bst_.root_, false, ""); std::cout << "-------------\n";
  rbTree.insert({6, 60});rbTree.rotBst_.printNode(rbTree.rotBst_.bst_.root_, false, ""); std::cout << "-------------\n";
  rbTree.insert({8, 80});rbTree.rotBst_.printNode(rbTree.rotBst_.bst_.root_, false, ""); std::cout << "-------------\n";
  rbTree.insert({11, 110});rbTree.rotBst_.printNode(rbTree.rotBst_.bst_.root_, false, ""); std::cout << "-------------\n";
  rbTree.insert({13, 130});rbTree.rotBst_.printNode(rbTree.rotBst_.bst_.root_, false, ""); std::cout << "-------------\n";
  rbTree.insert({16, 160});rbTree.rotBst_.printNode(rbTree.rotBst_.bst_.root_, false, ""); std::cout << "-------------\n";
  rbTree.insert({18, 180});rbTree.rotBst_.printNode(rbTree.rotBst_.bst_.root_, false, ""); std::cout << "-------------\n";

  // Выводим элементы дерева в возрастающем порядке
  for (const auto &node: rbTree)
  {
    std::cout << "Key: " << node.first << ", Value: " << node.second << std::endl;
  }
  return 0;
}
