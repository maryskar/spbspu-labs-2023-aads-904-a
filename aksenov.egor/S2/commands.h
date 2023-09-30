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
      out << " " << pairElement.first;
      out << " " << pairElement.second;
    }
  }

  template< typename dictOfDicts >
  dictOfDicts doComplement(const dictOfDicts &first, const dictOfDicts &second)
  {
    dictOfDicts res;
    /*if (std::addressof(first) == std::addressof(second))
    {
      return res;
    }
    auto firstIt = first.cbegin();
    auto secIt = second.cbegin();
    auto cmp = std::less<>();
    while (firstIt != first.cend() && secIt != second.cend())
    {
      while (secIt != second.cend() && cmp(secIt->first, firstIt->first))
      {
        ++secIt;
      }
      if (secIt == second.cend())
      {
        break;
      }
      if (firstIt->first != secIt->first)
      {
        res.insert(*firstIt);
      }
      ++firstIt;
    }
    while (firstIt != first.cend())
    {
      res.insert(*firstIt);
      ++firstIt;
    }
    return res;*/
    for (const auto& pair : first)
    {
      if (second.count(pair.first) == 0)
      {
        res.insert(pair);
      }
    }

    return res;
  }

  //void intersect(const std::string &newdataset, const std::string &dataset1, const std::string &dataset2);

  //void unite(const std::string &newdataset, const std::string &dataset1, const std::string &dataset2);

  //using commandMap = Dictionary< std::string, void (*)(const std::string &, const std::string &, const std::string &) >;
  //void createCommandMap(commandMap &commands);
}
#endif
