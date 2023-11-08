#ifndef COMMANDS_H
#define COMMANDS_H
#include "commandSet.h"
#include "iostream"
namespace timofeev
{
  template< typename T, typename B >
  void doComplement(std::istream& in, T& dict, B complDict)
  {
    std::string newDict, first, second;
    in >> newDict >> first >> second;
    if (dict.count(first) == 0 || dict.count(second) == 0)
    {
      throw std::invalid_argument("Logic error");
    }
    const auto dict1 = dict.at(first);
    const auto dict2 = dict.at(second);
    for (const auto &tmp: dict1)
    {
      if (!dict2.contains(tmp.first))
      {
        complDict.insert(tmp);
      }
    }
    dict[newDict] = complDict;
  }

  template< typename T, typename B >
  void doIntersect(std::istream& in, T& dict, B intersDict)
  {
    std::string newDict, first, second;
    in >> newDict >> first >> second;
    if (dict.count(first) == 0 || dict.count(second) == 0)
    {
      throw std::invalid_argument("Logic error");
    }
    else
    {
      const auto &dict1 = dict.at(first);
      const auto &dict2 = dict.at(second);
      for (const auto &tmp: dict1)
      {
        if (dict2.contains(tmp.first))
        {
          intersDict.insert(tmp);
        }
      }
      dict[newDict] = intersDict;
    }
  }

  template< typename T, typename B >
  void doUnion(std::istream& in, T& dict, B unDict)
  {
    std::string newDict, first, second;
    in >> newDict >> first >> second;
    if (dict.count(first) == 0 || dict.count(second) == 0)
    {
      throw std::invalid_argument("Logic error");
    }
    const auto& dict2 = dict.at(second);
    unDict = dict.at(first);
    for (const auto& entry : dict2)
    {
      if (!unDict.contains(entry.first))
      {
        unDict.insert(entry);
      }
    }
    dict[newDict] = unDict;
  }

}

#endif
