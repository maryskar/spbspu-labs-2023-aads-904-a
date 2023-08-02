#include <iostream>
#include "avltree.hpp"

int main()
{
  AVLTree< int, int > tree;
  tree.insert(1, 1);
  std::cout << tree.node_->data_.first;
}
