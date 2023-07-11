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
    std::cin >> dictName;
    if (!std::cin)
    {
      throw std::runtime_error("Error while printing dictionary.");
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
        std::cout << dictName;
        for (const auto &item: dictData)
        {
          std::cout << " " << item.first << " " << item.second;
        }
        std::cout << "\n";
      }
    }
    else
    {
      throw std::runtime_error("Error: dictionary not found.");
    }
  }
  void complementCommand(std::istream &in, std::ostream &out, container_type &dictionary)
  {
  }
  void intersectCommand(std::istream &in, std::ostream &out, container_type &dictionary)
  {
  }
  void unionCommand(std::istream &in, std::ostream &out, container_type &dictionary)
  {
  }
}