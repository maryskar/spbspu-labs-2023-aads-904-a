#include <iostream>
#include "rb-tree.hpp"

int main()
{
  chemodurov::RBTree< int > tree;
  for (int i = 0; i < 20; ++i)
  {
    int a = std::rand() % 1000;
    tree.insert(a);
    std::cout << a << ' ';
  }
  std::cout << '\n';
  tree.erase(690);
  for (auto i = tree.cbegin(); i != tree.cend(); ++i)
  {
    std::cout << *i << ' ';
  }
  std::cout << '\n';
  return 0;
}