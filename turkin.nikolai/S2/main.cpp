#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>
#include <functional>
#include <utility>
#include <limits>
#include "dictionary.hpp"
#include "cmd-work.hpp"
#include "file-work.hpp"
#include "forward-list.hpp"

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

  using dict_t = turkin::Dictionary< std::size_t, std::string, std::less< std::size_t > >;
  using dict_a = turkin::Dictionary< std::string, dict_t, std::less< std::string > >;
  dict_a dict = turkin::genDicts(file);
  while (std::cin)
  {
    std::string cmd;
    std::cin >> cmd;
    if (!std::cin)
    {
      break;
    }
    if (cmd == "print")
    {
      std::string name;
      std::cin >> name;
      if (!std::cin)
      {
        std::cerr << "<INVALID COMMAND>\n";
        continue;
      }
      turkin::print(*dict.find(name), std::cout);
      continue;
    }
    if (cmd == "complement")
    {
      std::string set0;
      std::string set1;
      std::string set2;
      std::cin >> set0 >> set1 >> set2;
      if (!std::cin)
      {
        std::cerr << "<INVALID COMMAND>\n";
        continue;
      }
      dict_t temp = turkin::to_complement(dict.find(set1)->second, dict.find(set2)->second);
      dict.emplace(std::make_pair(set0, temp));
      continue;
    }
    if (cmd == "intersect")
    {
      std::string set0;
      std::string set1;
      std::string set2;
      std::cin >> set0 >> set1 >> set2;
      if (!std::cin)
      {
        std::cerr << "<INVALID COMMAND>\n";
        continue;
      }
      dict_t temp = turkin::to_intersect(dict.find(set1)->second, dict.find(set2)->second);
      dict.emplace(std::make_pair(set0, temp));
      continue;
    }
    if (cmd == "union")
    {
      std::string set0;
      std::string set1;
      std::string set2;
      std::cin >> set0 >> set1 >> set2;
      if (!std::cin)
      {
        std::cerr << "<INVALID COMMAND>\n";
        continue;
      }
      dict_t temp = turkin::to_union(dict.find(set1)->second, dict.find(set2)->second);
      dict.emplace(std::make_pair(set0, temp));
      continue;
    }
    std::cerr << "<INVALID COMMAND>\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  return 0;
}
