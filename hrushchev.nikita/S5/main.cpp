#include <iostream>
#include <fstream>
#include <avltree.hpp>
#include <string>
#include "inputtree.hpp"
#include "keysummator.hpp"

int main(int argc, char* argv[])
{
  if (argc != 3)
  {
    std::cout << "Error arg\n";
    return 1;
  }
  std::ifstream input(argv[2]);
  if (!input.is_open())
  {
    std::cout << "Error file\n";
    return 1;
  }

  hrushchev::AVLTree< size_t, std::string > avlTree;
  inputTree(input, avlTree);
  std::string traverse = argv[1];

  std::cout << traverse;

}