#ifndef COMMANDMAP_H
#define COMMANDMAP_H
#include <iostream>
#include <string>
#include "Dictionary.h"

namespace aksenov
{
  using dict = aksenov::Dictionary< int, std::string, std::less< > >;
  using dictOfDicts = aksenov::Dictionary< std::string, dict, std::less< > >;
  template< typename dictOfDicts >
  void print(const std::string &name, const dictOfDicts &rhs, std::ostream &out)
  {
    if (rhs.isEmpty())
    {
      out << "dict is empty" << "\n";
      return;
    }
    out << name;
    for(const auto& pairElement : rhs)
    {
      out << " " << pairElement.first << " " << pairElement.second;
    }
  }

  template< typename dictOfDicts >
  dictOfDicts doComplement(const dictOfDicts &first, const dictOfDicts &second)
  {
    dictOfDicts res;
    for (const auto& pair : first)
    {
      if (second.count(pair.first) == 0)
      {
        res.insert(pair);
      }
    }
    return res;
  }

  template< typename dictOfDicts >
  dictOfDicts intersect(const dictOfDicts &first, const dictOfDicts &second)
  {
    dictOfDicts res;
    for (const auto& pair : first)
    {
      if (second.count(pair.first) != 0)
      {
        res.insert(pair);
      }
    }
    return res;
  }

  template< typename dictOfDicts >
  dictOfDicts unite(const dictOfDicts &first, const dictOfDicts &second)
  {
    dictOfDicts res(first);
    for (auto it : second)
    {
      res.insert(*it);
    }
    return res;
  }

  //void intersect(const std::string &newdataset, const std::string &dataset1, const std::string &dataset2);

  //void unite(const std::string &newdataset, const std::string &dataset1, const std::string &dataset2);

  //using commandMap = Dictionary< std::string, void (*)(const std::string &, const std::string &, const std::string &) >;
  //void createCommandMap(commandMap &commands);
}
#endif
