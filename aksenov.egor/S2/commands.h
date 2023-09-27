#ifndef COMMANDMAP_H
#define COMMANDMAP_H
#include <iostream>
#include <string>
#include "Dictionary.h"

namespace aksenov
{
  using dictionary = Dictionary<int, std::string>;

  void printDictionary(const std::string &dataset, std::ostream &out);

  void complement(const std::string &newdataset, const std::string &dataset1, const std::string &dataset2);

  void intersect(const std::string &newdataset, const std::string &dataset1, const std::string &dataset2);

  void unite(const std::string &newdataset, const std::string &dataset1, const std::string &dataset2);

  using commandMap = Dictionary< std::string, void (*)(const std::string &, const std::string &, const std::string &) >;
  void createCommandMap(commandMap &commands);
}
#endif
