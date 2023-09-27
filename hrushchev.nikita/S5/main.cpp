#include <iostream>
#include <fstream>
#include <avltree.hpp>
#include <string>
#include <exception>
#include "inputtree.hpp"
#include "keysummator.hpp"
#include "stringcreator.hpp"
#include "traverses.hpp"

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

  hrushchev::StringCreator creator;
  auto traverses = hrushchev::createDict< hrushchev::StringCreator >();

  try
  {
    creator = traverses.at(argv[1])(avlTree, creator);
    hrushchev::KeySummator summator;
    summator = avlTree.traverse_lnr(summator);
    std::cout << summator.result_;
    std::cout << creator.result_ << "\n";
  }
  catch (...)
  {
    std::cerr << "invalid traverse\n";
    return 1;
  }
}
