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

  void complement(const std::string& newdataset, const std::string& dataset1, const std::string& dataset2) {
    if (dictionaries.find(dataset1) == dictionaries.end() || dictionaries.find(dataset2) == dictionaries.end()) {
      std::cout << "<INVALID COMMAND>" << "\n";
      return;
    }

    const dictionary& dict1 = dictionaries[dataset1];
    const dictionary& dict2 = dictionaries[dataset2];

    dictionary result_dict;

    for (const auto& pair : dict1) {
      if (dict2.find(pair.first) == dict2.end()) {
        result_dict[pair.first] = pair.second;
      }
    }

    dictionaries[newdataset] = result_dict;
  }

  void intersect(const std::string& newdataset, const std::string& dataset1, const std::string& dataset2) {
    if (dictionaries.find(dataset1) == dictionaries.end() || dictionaries.find(dataset2) == dictionaries.end()) {
      std::cout << "<INVALID COMMAND>" << "\n";
      return;
    }

    const dictionary& dict1 = dictionaries[dataset1];
    const dictionary& dict2 = dictionaries[dataset2];

    dictionary result_dict;

    for (const auto& pair : dict1) {
      if (dict2.find(pair.first) != dict2.end()) {
        result_dict[pair.first] = pair.second;
      }
    }

    dictionaries[newdataset] = result_dict;
  }

  void unite(const std::string& newdataset, const std::string& dataset1, const std::string& dataset2) {
    if (dictionaries.find(dataset1) == dictionaries.end() || dictionaries.find(dataset2) == dictionaries.end()) {
      std::cout << "<INVALID COMMAND>" << "\n";
      return;
    }

    const dictionary& dict1 = dictionaries[dataset1];
    const dictionary& dict2 = dictionaries[dataset2];

    dictionary result_dict = dict1;

    for (const auto& pair : dict2) {
      result_dict[pair.first] = pair.second;
    }

    dictionaries[newdataset] = result_dict;
  }

  void createCommandMap(commandMap &commands)
  {
    commands["complement"] = complement;
    commands["intersect"] = intersect;
    commands["union"] = unite;
  }
}
