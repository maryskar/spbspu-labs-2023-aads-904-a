#include <iostream>
#include "rb-tree.hpp"

int main()
{
  chemodurov::RBTree< int > tree;
  tree.insert(5);
  tree.insert(5);
  for (auto i = tree.cbegin(); i != tree.cend(); ++i)
  {
    std::cout << *i << ' ';
  }
  std::cout << '\n';
  return 0;
}