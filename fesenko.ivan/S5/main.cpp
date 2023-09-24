#include <iostream>
#include <fstream>
#include <avl/AVL.h>
#include <messages.h>
#include "createTreeWithTraverses.h"
#include "functionalObjects.h"

int main(int argc, char *argv[])
{
  if (argc != 3) {
    std::cerr << "Invalid number of arguments\n";
    return 2;
  }
  std::ifstream in(argv[2]);
  if (!in.is_open()) {
    std::cerr << "Can`t open the file\n";
    return 2;
  }
  using tree = fesenko::AVL< int, std::string, std::less< > >;
  using tree_elem = std::pair< int, std::string >;
  tree tr;
  try {
    int key = 0;
    std::string value = "";
    while (in) {
      in >> key >> value;
      if (!in) {
        break;
      }
      tr.insert(tree_elem(key, value));
    }
    if (tr.empty()) {
      fesenko::outEmptyMessage(std::cout);
    }
  } catch (const std::exception &e) {
    std::cerr << e.what() << "\n";
    return 2;
  }
  try {
    auto int_list = fesenko::createTreeWithTraverses< fesenko::IntSummator >();
    fesenko::IntSummator intSum;
    auto str_list = fesenko::createTreeWithTraverses< fesenko::StrSummator >();
    fesenko::StrSummator strSum;
    std::cout << (tr.*int_list.at(argv[1]))(intSum).getSum() << " " << (tr.*str_list.at(argv[1]))(strSum).getSum() << "\n";
  } catch (...) {
    fesenko::outInvalidCommandMessage(std::cout);
    std::cout << "\n";
    return 2;
  }
}
