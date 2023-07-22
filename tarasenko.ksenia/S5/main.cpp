#include <iostream>
#include <fstream>
#include <string>
#include <RedBlackTree.h>
#include <map.h>
#include "readDataForTree.h"

class Printer
{
public:
 void operator()(const std::pair< int, std::string >& key_value)
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
  tarasenko::RedBlackTree< std::pair< long long, std::string >, std::less<> > tree;
  tarasenko::readDataForTree(input, tree);
  Printer print;
  tarasenko::Map< std::string, decltype(&tree_t::traverse_lnr< Printer >), std::less<> > directs;
  directs.push("ascending", &tree_t::traverse_lnr< Printer >);
  directs.push("descending", &tree_t::traverse_rnl< Printer >);
  directs.push("breadth", &tree_t::traverse_breadth< Printer >);

  if (tree.isEmpty()) {
    std::cout << "<EMPTY>";
  }
  std::string direct = argv[1];
  auto it = directs.find(direct);
  if (directs.find(direct) == directs.end()) {
    std::cout << "<INVALID COMMAND>";
  }
  (tree.*(it->second))(print);
  std::cout << "\n";
}