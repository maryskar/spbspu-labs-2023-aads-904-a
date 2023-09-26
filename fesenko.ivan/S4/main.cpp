#include <iostream>
#include <fstream>
#include <utility>
#include <avl/AVL.h>
#include <commands.h>
#include "genDictOfDicts.h"

int main(int argc, char *argv[])
{
  if (argc != 2) {
    std::cerr << "Invalid number of arguments\n";
    return 2;
  }
  std::ifstream in(argv[1]);
  if (!in.is_open()) {
    std::cerr << "Can`t open the file\n";
    return 2;
  }
  using tree = fesenko::AVL< int, std::string, std::less< > >;
  using tree_of_tree = fesenko::AVL< std::string, tree, std::less< > >;
  using tree_c = fesenko::AVL< std::string, tree (*)(const tree &, const tree &), std::less< > >;
  tree_of_tree container = fesenko::genDictOfDicts< tree_of_tree, tree >(in);
  tree_c commands;
  commands.insert(std::make_pair("complement", fesenko::make_complementation< tree >));
  commands.insert(std::make_pair("intersect", fesenko::make_intersection< tree >));
  commands.insert(std::make_pair("union", fesenko::make_union< tree >));
  while (std::cin) {
    std::string command;
    std::cin >> command;
    if (!std::cin) {
      break;
    }
    try {
      if (command == "print") {
        std::string name;
        std::cin >> name;
        fesenko::print(std::make_pair(name, container.at(name)), std::cout);
        std::cout << "\n";
      } else {
        auto func = commands.at(command);
        std::string newTreeName;
        std::string treeName1;
        std::string treeName2;
        std::cin >> newTreeName >> treeName1 >> treeName2;
        tree tree1 = container.at(treeName1);
        tree tree2 = container.at(treeName2);
        tree newTree = func(tree1, tree2);
        if (!container.insert(std::make_pair(newTreeName, newTree)).second) {
          auto it = container.find(newTreeName);
          container.at(it->first) = newTree;
        }
      }
    } catch (...) {
      fesenko::outInvalidCommandMessage(std::cout);
      std::cout << "\n";
    }
  }
}
