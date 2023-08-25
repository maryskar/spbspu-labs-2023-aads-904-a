#include "inputtree.hpp"
#include <istream>
#include <string>
#include <avltree.hpp>

void inputTree(std::istream& input, hrushchev::AVLTree< size_t, std::string >& tree)
{
  size_t key;
  std::string value;
  while (input >> key >> value)
  {
    tree.insert(key, value);
  }
  input.clear();
}