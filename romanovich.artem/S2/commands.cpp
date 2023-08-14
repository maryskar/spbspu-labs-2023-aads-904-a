#include "commands.h"
#include <istream>
#include "printmessages.h"
namespace
{
  using dict_ref = romanovich::dict_type &;
  using const_dict_ref = const romanovich::dict_type &;
  struct ComplementOperation
  {
    void operator()(dict_ref newDict, const_dict_ref firstDict, const_dict_ref secondDict) const
    {
      for (const auto &entry: firstDict)
      {
        if (secondDict.count(entry.first) == 0)
        {
          newDict[entry.first] = entry.second;
        }
      }
    }
  };
  struct IntersectOperation
  {
    void operator()(dict_ref newDict, const_dict_ref firstDict, const_dict_ref secondDict) const
    {
      for (const auto &entry: firstDict)
      {
        if (secondDict.count(entry.first) > 0)
        {
          newDict[entry.first] = entry.second;
        }
      }
    }
  };
  struct UnionOperation
  {
    void operator()(dict_ref newDict, const_dict_ref firstDict, const_dict_ref secondDict) const
    {
      for (auto &entry: secondDict)
      {
        newDict[entry.first] = entry.second;
      }
      for (auto &entry: firstDict)
      {
        newDict[entry.first] = entry.second;
      }
    }
  };
}
namespace romanovich
{
  Dictionary< std::string, CommandHandler > createCommandDictionary(container_type &dictionary)
  {
    std::string printCall = "print";
    std::string complementCall = "complement";
    std::string intersectCall = "intersect";
    std::string unionCall = "union";
    Dictionary< std::string, CommandHandler > commands;
    using namespace std::placeholders;
    commands[printCall] = std::bind(printCommand, _1, _2, std::ref(dictionary));
    commands[complementCall] = std::bind(performCommand, _1, _2, std::ref(dictionary), ComplementOperation());
    commands[intersectCall] = std::bind(performCommand, _1, _2, std::ref(dictionary), IntersectOperation());
    commands[unionCall] = std::bind(performCommand, _1, _2, std::ref(dictionary), UnionOperation());
    return commands;
  }
  void performCommand(std::istream &in,
                        std::ostream &out,
                        container_type &dictionary,
                        const std::function< void(dict_type &, const dict_type &, const dict_type &) > &operation)
  {
    std::string newDictName, dictName1, dictName2;
    in >> newDictName >> dictName1 >> dictName2;
    if (!in)
    {
      throw std::runtime_error("Error while reading command arguments.");
    }
    if (dictionary.count(dictName1) == 0 && dictionary.count(dictName2) == 0)
    {
      throw std::runtime_error("Error: both dictionaries not found.");
    }
    if (dictionary.count(dictName1) == 0 || dictionary.count(dictName2) == 0)
    {
      std::string errDictName = dictionary.count(dictName1) == 0 ? dictName1 : dictName2;
      throw std::runtime_error("Error: dictionary \"" + errDictName + "\" not found.");
    }
    if (dictionary.empty())
    {
      printEmpty(out) << "\n";
    }
    else
    {
      const auto &dict1 = dictionary[dictName1];
      const auto &dict2 = dictionary[dictName2];
      dict_type newDict;
      operation(newDict, dict1, dict2);
      dictionary[newDictName] = newDict;
    }
  }
  void printCommand(std::istream &in, std::ostream &out, container_type &dictionary)
  {
    std::string dictName;
    in >> dictName;
    if (!in)
    {
      throw std::runtime_error("Error while reading command arguments.");
    }
    if (dictionary.count(dictName) <= 0)
    {
      throw std::runtime_error("Error: dictionary not found.");
    }
    else
    {
      const auto &dictData = dictionary[dictName];
      if (dictData.empty())
      {
        printEmpty(out) << "\n";
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
  }
}
