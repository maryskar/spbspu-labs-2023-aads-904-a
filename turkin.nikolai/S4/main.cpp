#include <iostream>
#include <cstddef>
#include <string>
#include <functional>
#include "rb-tree.hpp"
#include "out-msg.hpp"

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

  using tree_t = turkin::RBtree< std::size_t, std::string, std::less< std::size_t > >;
  using tree_a = turkin::RBtree< std::string, tree_t, std::less< std::string > >;
  using tree_c = turkin::RBtree< std::string, tree_t (*)(const tree_t &, const tree_t &), std::less< std::string > >;

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
        //turkin::print(std::make_pair(name, dict.at(name)), std::cout);
      }
      else
      {
        std::string set0;
        std::string set1;
        std::string set2;
        std::cin >> set0 >> set1 >> set2;
        //dict_t dict1 = dict.at(set1);
        //dict_t dict2 = dict.at(set2);
        //auto func = commands.at(cmd);
        //dict_t temp = func(dict1, dict2);
        //dict.emplace(set0, temp);
      }
    }
    catch (...)
    {
      turkin::outInvalidCMD(std::cout);
    }
  }
  return 0;
}
