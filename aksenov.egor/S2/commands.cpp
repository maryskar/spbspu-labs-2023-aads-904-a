#include "commands.h"
#include <stdexcept>
#include <iostream>

namespace aksenov
{
  Dictionary<std::string, dictionary> dictionaries;

  void printDictionary(const std::string& dataset, std::ostream &out)
  {
    if (dictionaries.find(dataset) == dictionaries.end()) {
      out << "<EMPTY>" << "\n";
      return;
    }
    const dictionary &dict = dictionaries[dataset];
    for (const auto &pair : dict)
    {
      out << pair.first << " " << pair.second << " ";
    }
    out << "\n";
  }
}