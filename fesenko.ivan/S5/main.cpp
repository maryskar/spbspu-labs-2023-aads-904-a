#include <iostream>
#include <fstream>
#include <avl/AVL.h>
#include <messages.h>
#include "genDict.h"
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
  using tree = fesenko::AVL< long long, std::string, std::less< > >;
  tree tr = fesenko::genDict< tree >(in);
  if (tr.empty()) {
    fesenko::outEmptyMessage(std::cout);
    std::cout << "\n";
    return 0;
  }
  try {
    auto num_list = fesenko::createTreeWithTraverses< fesenko::NumSummator >();
    fesenko::NumSummator numSum;
    auto str_list = fesenko::createTreeWithTraverses< fesenko::StrSummator >();
    fesenko::StrSummator strSum;
    std::cout << (tr.*num_list.at(argv[1]))(numSum).getSum() << " " << (tr.*str_list.at(argv[1]))(strSum).getSum() << "\n";
  } catch (...) {
    fesenko::outInvalidCommandMessage(std::cout);
    std::cout << "\n";
    return 2;
  }
}
