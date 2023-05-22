#include <iostream>
#include "rb-tree.hpp"

int main()
{
  chemodurov::RBTree< int > tree;
  for (int i = 0; i < 50; ++i)
  {
    int a = std::rand() % 100;
    tree.insert(a);
    std::cout << a << ' ';
  }
  std::cout << '\n';
  tree.erase(37);
  for (auto i = tree.cbegin(); i != tree.cend(); ++i)
  {
    std::cout << *i << ' ';
  }
  std::cout << '\n';
  return 0;
}