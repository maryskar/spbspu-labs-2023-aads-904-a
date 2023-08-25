#include <iostream>
#include <fstream>
#include <avltree.hpp>
#include <string>
#include <exception>
#include "inputtree.hpp"
#include "keysummator.hpp"
#include "stringcreator.hpp"

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
  hrushchev::inputTree(input, avlTree);
  if (avlTree.empty())
  {
    std::cout << "<EMPTY>" << "\n";
    return 0;
  }

  std::string traverse = argv[1];
  if ((traverse == "ascending") || (traverse == "descending") || (traverse == "breadth"))
  {
    try
    {
      hrushchev::KeySummator summator;
      summator = avlTree.traverse_lnr(summator);
      std::cout << summator.result_;
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << "\n";
      return 1;
    }
    hrushchev::StringCreator creator;
    if ((traverse == "ascending"))
    {
      creator = avlTree.traverse_lnr(creator);
      std::cout << creator.result_ << "\n";
    }
    if ((traverse == "descending"))
    {
      creator = avlTree.traverse_rnl(creator);
      std::cout << creator.result_ << "\n";
    }
    if ((traverse == "breadth"))
    {
      creator = avlTree.traverse_breadth(creator);
      std::cout << creator.result_ << "\n";
    }
  }
  else
  {
    std::cerr << "invalid traverse\n";
    return 1;
  }
}
