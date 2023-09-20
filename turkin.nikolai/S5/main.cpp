#include <iostream>
#include <fstream>
#include <string>
#include <avl-tree/avl-tree.hpp>
#include <out-msg.hpp>
#include <file-work.hpp>

#include "func-objects.hpp"
#include "traverse-list.hpp"

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

  using tree_t = turkin::AVLtree< int, std::string, std::less< > >;
  auto dict = turkin::genDict< tree_t >(file);
  if (dict.empty())
  {
    turkin::outEmptyCMD(std::cout);
    return 0;
  }

  auto key_list = turkin::make_trvs< turkin::KeySum >();
  auto str_list = turkin::make_trvs< turkin::StrSum >();
  turkin::KeySum key;
  turkin::StrSum str;

  try
  {
    std::cout << (dict.*key_list.at(argv[1]))(key).get() << (dict.*str_list.at(argv[1]))(str).get() << "\n";
  }
  catch (...)
  {
    turkin::outInvalidCMD(std::cout);
    return 1;
  }
  return 0;
}
