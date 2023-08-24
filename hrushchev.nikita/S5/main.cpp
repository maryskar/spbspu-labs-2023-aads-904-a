#include <iostream>
#include <avltree.hpp>
#include <string>
int main()
{
  hrushchev::AVLTree<int, std::string> avlTree;

  avlTree.insert(1, "one");
  avlTree.insert(2, "two");
  avlTree.insert(3, "free");
  avlTree.insert(4, "four");
  avlTree.insert(5, "five");

  avlTree.traverse_lnr([](const auto& data)
  {
      std::cout << "(" << data.first << ", " << data.second << ") ";
  });
  std::cout << "\n";
  
  avlTree.traverse_rnl([](const auto& data)
  {
      std::cout << "(" << data.first << ", " << data.second << ") ";
  });
  std::cout << "\n";
}
