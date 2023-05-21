#include <iostream>
#include "rb-tree.hpp"

int main()
{
  chemodurov::RBTree< int > tree = {1, 90, 8, 6, -64, 8, 3, 2, 8};
  for (auto i = tree.cbegin(); i != tree.cend(); ++i)
  {
    std::cout << *i << ' ';
  }
  std::cout << '\n';
  return 0;
}