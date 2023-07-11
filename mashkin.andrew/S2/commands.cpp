#include "commands.h"
#include <iostream>
#include "IOrealization.h"

namespace mashkin
{
  void print(std::istream& inp, dictionaries& dicts)
  {
    std::string command;
    inp >> command;
    if (dicts.contains(command))
    {
      auto iter = dicts.find(command);
      std::cout << iter->first << iter->second << "\n";
    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
      inp.setstate(std::ios::failbit);
    }
  }
}
