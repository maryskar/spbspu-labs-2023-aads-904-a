#include <iostream>
#include <fstream>
#include <functional>
#include <utility>
#include <dictionary/dictionary.hpp>
#include <dictionary/forward-list/forward-list.hpp>
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

  using dict_t = turkin::Dictionary< std::size_t, std::string, std::less< > >;
  using dict_a = turkin::Dictionary< std::string, dict_t, std::less< > >;
  using dict_c = turkin::Dictionary< std::string, dict_t (*)(const dict_t &, const dict_t &), std::less< > >;

  dict_c commands;
  commands.insert("complement", turkin::to_complement< dict_t, std::less< > >);
  commands.insert("intersect", turkin::to_intersect< dict_t >);
  commands.insert("union", turkin::to_union< dict_t >);

  dict_a dict = turkin::genDicts< dict_a, dict_t >(file);

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
        dict_t dict1 = dict.at(set1);
        dict_t dict2 = dict.at(set2);
        auto func = commands.at(cmd);
        dict_t temp = func(dict1, dict2);
        dict.emplace(set0, temp);
      }
    }
    catch (...)
    {
      turkin::outInvalidCMD(std::cout);
    }
  }
  return 0;
}
