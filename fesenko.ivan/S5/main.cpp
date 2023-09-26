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
    auto list = fesenko::createTreeWithTraverses< fesenko::Summator >();
    fesenko::Summator sum;
    auto result = (tr.*list.at(argv[1]))(sum).getSum();
    std::cout << result.first << " " << result.second << "\n";
  } catch (...) {
    fesenko::outInvalidCommandMessage(std::cout);
    std::cout << "\n";
    return 2;
  }
}
