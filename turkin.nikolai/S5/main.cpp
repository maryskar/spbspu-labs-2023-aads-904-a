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
    turkin::KeySum key;
    turkin::StrSum str;
    auto key_result = key.get();
    auto str_result = str.get();
    std::string type = argv[1];
    if (type == "ascending")
    {
      key_result = dict.traverse_lnr(key).get();
      str_result = dict.traverse_lnr(str).get();
    }
    if (type == "descending")
    {
      key_result = dict.traverse_lnr(key).get();
      str_result = dict.traverse_lnr(str).get();
    }
    if (type == "breadth")
    {
      key_result = dict.traverse_lnr(key).get();
      str_result = dict.traverse_lnr(str).get();
    }
    std::cout << key_result << str_result << "\n";
  }
  catch (...)
  {
    turkin::outInvalidCMD(std::cout);
  }
  return 0;
}
