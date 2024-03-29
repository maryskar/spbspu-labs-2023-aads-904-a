#ifndef COMMANDMAP_H
#define COMMANDMAP_H
#include <iostream>
#include <string>
#include <stdexcept>
#include "Dictionary.h"

namespace aksenov
{
  template< typename dictOfDicts >
  void print(const std::string &name, const dictOfDicts &rhs, std::ostream &out)
  {
    if (rhs.isEmpty())
    {
      throw std::invalid_argument("empty");
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
      if (!second.contains(pair.first))
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
    for (auto it = second.begin(); it != second.end(); ++it)
    {
      res.insert(*it);
    }
    return res;
  }

  template< class Storage >
  void createCommandDict(Storage &commands)
  {
    commands["intersect"] = intersect;
    commands["union"] = unite;
    commands["complement"] = doComplement;
  }
}
#endif
