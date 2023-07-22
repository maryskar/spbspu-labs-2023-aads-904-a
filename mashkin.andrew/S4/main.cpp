#include <iostream>
#include <map>
#include <fstream>
#include <limits>
#include <string>
#include <utility>
#include "DictWithCommands.h"
#include "IOrealization.h"
#include "AVL.h"
#include "AVL_iterator.h"
#include "AVL_reverse_iter.h"
#include "const_AVL_iterator.h"
#include "const_AVL_reverse_iter.h"
#include "tree.h"

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cerr << "Wrong number of arguments\n";
    return 1;
  }
  else
  {
    std::ifstream input;
    input.open(argv[1]);
    if (!input.is_open())
    {
      std::cerr << "Can't open file\n";
      return 1;
    }
    using dict = mashkin::AVL< int, std::string >;
    using dictionaries = mashkin::AVL< std::string, dict >;
    constexpr auto maxSize = std::numeric_limits< std::streamsize >::max();
    dictionaries dicts;
    while (!input.eof())
    {
      input >> dicts;
      if (input.fail())
      {
        input.clear();
        input.ignore(maxSize, '\n');
      }
    }
    mashkin::AVL< std::string, void (*)(std::istream&, dictionaries&) > commands;
    mashkin::createDictWithCommnads(commands);
    std::string command;
    while (!std::cin.eof())
    {
      std::cin >> command;
      if (std::cin.eof())
      {
        break;
      }
      if (commands.contains(command))
      {
        commands[command](std::cin, dicts);
      }
      else
      {
        std::cout << "<INVALID COMMAND>\n";
        std::cin.setstate(std::ios::failbit);
      }
      if (std::cin.fail())
      {
        std::cin.clear();
        std::cin.ignore(maxSize, '\n');
      }
    }
  }
  return 0;
}
