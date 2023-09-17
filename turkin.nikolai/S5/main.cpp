#include <iostream>
#include <fstream>
#include <string>
#include <avl-tree/avl-tree.hpp>
#include <out-msg.hpp>
#include <file-work.hpp>

#include "func-objects.hpp"

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

  turkin::KeySum key;
  auto lnr_key = dict.traverse_lnr(key);
  auto rnl_key = dict.traverse_rnl(key);
  auto brh_key = dict.traverse_breadth(key);
  turkin::AVLtree< std::string, decltype(lnr_key), std::less< > > traverse_key;
  traverse_key.insert("ascending", lnr_key);
  traverse_key.insert("descending", rnl_key);
  traverse_key.insert("breadth", brh_key);

  turkin::StrSum str;
  auto lnr_str = dict.traverse_lnr(str);
  auto rnl_str = dict.traverse_rnl(str);
  auto brh_str = dict.traverse_breadth(str);
  turkin::AVLtree< std::string, decltype(lnr_str), std::less< > > traverse_str;
  traverse_str.insert("ascending", lnr_str);
  traverse_str.insert("descending", rnl_str);
  traverse_str.insert("breadth", brh_str);

  try
  {
    auto key_result = key.get();
    auto str_result = str.get();
    std::string type = argv[1];
    key_result = traverse_key.at(type).get();
    str_result = traverse_str.at(type).get();
    std::cout << key_result << str_result << "\n";
  }
  catch (...)
  {
    turkin::outInvalidCMD(std::cout);
    return 1;
  }
  return 0;
}
