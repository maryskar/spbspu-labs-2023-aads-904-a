#include "inputtree.hpp"
#include <istream>
#include <string>
#include <avltree.hpp>

void hrushchev::inputTree(std::istream& input, hrushchev::AVLTree< long long, std::string >& tree)
{
  size_t key;
  std::string value;
  while (input >> key >> value)
  {
    tree.insert(key, value);
  }
  input.clear();
}
