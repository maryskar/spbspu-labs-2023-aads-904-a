#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>
#include <functional>
#include <utility>
#include <avl-tree/avl-tree.hpp>
#include <out-msg.hpp>
#include <cmd-work.hpp>
#include <file-work.hpp>

int main(int argc, char * argv[])
{
  if (argc == 1)
  {
    std::cerr << "no file\n";
    return 1;
  }

  std::ifstream file;
  file.open(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "cannot open file\n";
    return 1;
  }

  using tree_t = turkin::AVLtree< std::size_t, std::string, std::less< > >;
  using tree_a = turkin::AVLtree< std::string, tree_t, std::less< > >;
  using tree_c = turkin::AVLtree< std::string, tree_t (*)(const tree_t &, const tree_t &), std::less< > >;

  tree_c commands;
  commands.insert("complement", turkin::to_complement< tree_t, std::less< > >);
  commands.insert("intersect", turkin::to_intersect< tree_t >);
  commands.insert("union", turkin::to_union< tree_t >);

  auto dict = turkin::genDicts< tree_a, tree_t >(file);

  while (std::cin)
  {
    std::string cmd;
    std::cin >> cmd;
    if (!std::cin)
    {
      break;
    }
    try
    {
      if (cmd == "print")
      {
        std::string name;
        std::cin >> name;
        turkin::print(std::make_pair(name, dict.at(name)), std::cout);
      }
      else
      {
        std::string set0;
        std::string set1;
        std::string set2;
        std::cin >> set0 >> set1 >> set2;
        tree_t dict1 = dict.at(set1);
        tree_t dict2 = dict.at(set2);
        auto func = commands.at(cmd);
        tree_t temp = func(dict1, dict2);
        dict.insert(set0, temp);
      }
    }
    catch (...)
    {
      turkin::outInvalidCMD(std::cout);
    }
  }
  return 0;
}
