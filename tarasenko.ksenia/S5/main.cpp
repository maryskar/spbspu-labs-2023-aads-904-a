#include <iostream>
#include <fstream>
#include <string>
#include <RedBlackTree.h>
#include <map.h>
#include <message.h>
#include "readDataForTree.h"
#include "printer.h"

int main(int argc, char* argv[])
{
  if (argc != 3)
  {
    std::cout << "Incorrect input\n";
    return 1;
  }
  std::ifstream input(argv[2]);
  if (!input.is_open())
  {
    std::cout << "File not found\n";
    return 1;
  }
  using tree_t = tarasenko::RedBlackTree< std::pair< long long, std::string >, std::less<> >;
  tree_t tree;
  tarasenko::readDataForTree(input, tree);

  using printer = tarasenko::Printer;
  printer print(std::cout);
  tarasenko::Map< std::string, printer(tree_t::*)(printer f), std::less<> > directs;
  directs.push("ascending", &tree_t::traverse_lnr< printer >);
  directs.push("descending", &tree_t::traverse_rnl< printer >);
  directs.push("breadth", &tree_t::traverse_breadth< printer >);

  if (tree.isEmpty()) {
    tarasenko::outMessageEmpty(std::cout);
  }
  std::string direct = argv[1];
  auto it = directs.find(direct);
  if (directs.find(direct) == directs.end()) {
    tarasenko::outMessageInvalidCommand(std::cout);
  }
  (tree.*(it->second))(print);
  std::cout << "\n";
}