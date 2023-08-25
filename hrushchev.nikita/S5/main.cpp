#include <iostream>
#include <fstream>
#include <avltree.hpp>
#include <string>
#include <exception>
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

  hrushchev::AVLTree< long long, std::string > avlTree;
  inputTree(input, avlTree);
  if (avlTree.empty())
  {
    std::cerr << "<EMPTY>";
    return 1;
  }

  std::string traverse = argv[1];
  if ((traverse == "ascending") || (traverse == "descending") || (traverse == "breadth"))
  {
    try
    {
      KeySummator summator;
      summator = avlTree.traverse_lnr(summator);
      std::cout << summator.result_ << " ";
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << "\n";
      return 1;
    }
  }
  else
  {
    std::cerr << "invalid traverse\n";
    return 1;
  }
}
