#include <cstddef>
#include <fstream>
#include <iostream>
#include <limits>
#include "DictWithCommands.h"
#include "dictionary.h"
#include "forwardConstIterator.h"
#include "forwardIterator.h"
#include "IOrealization.h"
#include "forwardList.h"

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
    using dict = mashkin::Dictionary< int, std::string >;
    using dictionaries = mashkin::Dictionary< std::string, dict >;
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
    mashkin::Dictionary< std::string, void (*)(std::istream&, dictionaries&) > commands;
    mashkin::createDictWithCommnads(commands);
    std::string command;
    while (!std::cin.eof())
    {
      std::cin >> command;
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
