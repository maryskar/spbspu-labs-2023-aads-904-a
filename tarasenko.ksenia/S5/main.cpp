#include <iostream>
#include <fstream>
#include <string>
#include <RedBlackTree.h>
#include <map.h>
#include <message.h>
#include "readDataForTree.h"

class Printer
{
public:
 void operator()(const std::pair< long long, std::string >& key_value)
 {
   std::cout << key_value.second << " ";
 }
};

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

  Printer print;
  tarasenko::Map< std::string, Printer(tree_t::*)(Printer f), std::less<> > directs;
  directs.push("ascending", &tree_t::traverse_lnr< Printer >);
  directs.push("descending", &tree_t::traverse_rnl< Printer >);
  directs.push("breadth", &tree_t::traverse_breadth< Printer >);

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