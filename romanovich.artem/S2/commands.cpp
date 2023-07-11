#include "commands.h"
#include <iostream>
using namespace std::placeholders;
namespace romanovich
{
  std::unordered_map< std::string, CommandHandler > createCommandDictionary(container_type &dictionary)
  {
    std::string printCall = "print";
    std::string complementCall = "complement";
    std::string intersectCall = "intersect";
    std::string unionCall = "union";
    std::unordered_map< std::string, CommandHandler > commands;
    commands[printCall] = std::bind(printCommand, _1, _2, std::ref(dictionary));
    commands[complementCall] = std::bind(complementCommand, _1, _2, std::ref(dictionary));
    commands[intersectCall] = std::bind(intersectCommand, _1, _2, std::ref(dictionary));
    commands[unionCall] = std::bind(unionCommand, _1, _2, std::ref(dictionary));
    return commands;
  }
  void printCommand(std::istream &in, std::ostream &out, container_type &dictionary)
  {
    std::string dictName;
    in >> dictName;
    if (!in)
    {
      throw std::runtime_error("Error while reading command arguments.");
    }
    if (dictionary.count(dictName) > 0)
    {
      const auto &dictData = dictionary[dictName];
      if (dictData.empty())
      {
        throw std::runtime_error("Error: empty dictionary.");
      }
      else
      {
        out << dictName;
        for (const auto &item: dictData)
        {
          out << " " << item.first << " " << item.second;
        }
        out << "\n";
      }
    }
    else
    {
      throw std::runtime_error("Error: dictionary not found.");
    }
  }
  void complementCommand(std::istream &in, std::ostream &out, container_type &dictionary)
  {
    if (out){}
    std::string newDictName, dictName1, dictName2;
    in >> newDictName >> dictName1 >> dictName2;
    if (!in)
    {
      throw std::runtime_error("Error while reading command arguments.");
    }
    if (dictionary.count(dictName1) == 0 || dictionary.count(dictName2) == 0)
    {
      throw std::runtime_error("Error: dictionary not found.");
    }
    const auto &dict1 = dictionary[dictName1];
    const auto &dict2 = dictionary[dictName2];
    dict_type newDict;
    for (const auto &entry: dict1)
    {
      if (dict2.count(entry.first) == 0)
      {
        newDict[entry.first] = entry.second;
      }
    }
    dictionary[newDictName] = newDict;
  }
  void intersectCommand(std::istream &in, std::ostream &out, container_type &dictionary)
  {
    if (out){}
    if (in){}
    if (dictionary.empty()){}
  }
  void unionCommand(std::istream &in, std::ostream &out, container_type &dictionary)
  {
    if (out){}
    if (in){}
    if (dictionary.empty()){}
  }
}
