#include <iostream>
#include <fstream>
#include <string>
#include <avl-tree/avl-tree.hpp>
#include <out-msg.hpp>
#include <file-work.hpp>

#include "func-objects.hpp"

using tree_t = turkin::AVLtree< int, std::string, std::less< > >;

int main(int argc, char * argv[])
{
  if (argc != 3)
  {
    std::cerr << "input error\n";
    return 1;
  }

  std::ifstream file;
  file.open(argv[2]);
  if (!file.is_open())
  {
    std::cerr << "cannot open file\n";
    return 1;
  }

  auto dict = turkin::genDict< tree_t >(file);
  if (dict.empty())
  {
    turkin::outEmptyCMD(std::cout);
    return 0;
  }

  try
  {
    turkin::StrSum ks;
    auto result = ks.get();
    std::string type = argv[1];
    if (type == "ascending")
    {
      result = dict.traverse_lnr(ks).get();
    }
    if (type == "descending")
    {
      result = dict.traverse_lnr(ks).get();
    }
    if (type == "breadth")
    {
      result = dict.traverse_breadth(ks).get();
    }
    std::cout << "\b" << result << "\n";
  }
  catch (...)
  {
    turkin::outInvalidCMD(std::cout);
  }
  return 0;
}
