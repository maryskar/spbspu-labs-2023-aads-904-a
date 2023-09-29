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
  void print(const std::pair< std::string, dictOfDicts > &rhs, std::ostream &out)
  {
    auto cont = rhs.second;
    auto cit = cont.cbegin();
    if (cit == cont.cend())
    {
      out << "dict is empty" << "\n";
      return;
    }
    out << rhs.first;
    while (cit != cont.cend())
    {
      out << " " << cit->first;
      out << " " << cit->second;
      ++cit;
    }
  }

  /*template< typename dictOfDicts >
  dictOfDicts doComplement(const dictOfDicts &first, const dictOfDicts &second)
  {
    dictOfDicts res;
    if (std::addressof(first) == std::addressof(second))
    {
      return res;
    }
    auto firstIt = first.cbegin();
    auto secIt = second.cbegin();
    auto cmp = std::less<>();
    while (firstIt != first.cend() && secIt != second.cend())
    {
      if (cmp(firstIt->first, secIt->first)) {
        res.insert(*firstIt);
        ++firstIt;
      } else if(cmp(secIt->first, firstIt->first)) {
        ++secIt;
      } else {
        ++firstIt;
        ++secIt;
      }
    }
    while (firstIt != first.cend())
    {
      res.insert(*firstIt);
      ++firstIt;
    }
    return res;
  }*/

  //void intersect(const std::string &newdataset, const std::string &dataset1, const std::string &dataset2);

  //void unite(const std::string &newdataset, const std::string &dataset1, const std::string &dataset2);

  //using commandMap = Dictionary< std::string, void (*)(const std::string &, const std::string &, const std::string &) >;
  //void createCommandMap(commandMap &commands);

  template< typename dictOfDicts >
  dictOfDicts doComplement(const dictOfDicts &first, const dictOfDicts &second)
  {
    dictOfDicts res;
    if (std::addressof(first) == std::addressof(second))
    {
      return res;
    }
    auto firstIt = first.cbegin();
    auto secIt = second.cbegin();
    auto cmp = std::less<>();
    while (firstIt != first.cend() && secIt != second.cend())
    {
      if (cmp(firstIt->first, secIt->first)) {
        res[firstIt->first] = firstIt->second;
        ++firstIt;
      } else if(cmp(secIt->first, firstIt->first)) {
        ++secIt;
      } else {
        ++firstIt;
        ++secIt;
      }
    }
    while (firstIt != first.cend())
    {
      res[firstIt->first] = firstIt->second;
      ++firstIt;
    }
    return res;
  }
}
#endif
