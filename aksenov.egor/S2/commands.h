#ifndef COMMANDMAP_H
#define COMMANDMAP_H
#include <iostream>
#include <string>
#include "Dictionary.h"

namespace aksenov
{
  using dict = aksenov::Dictionary< int, std::string, std::less< > >;
  using dictOfDicts = aksenov::Dictionary< std::string, dict, std::less< > >;
  template< typename dictOfDicts, typename dict>
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

  void complement(const std::string &newdataset, const std::string &dataset1, const std::string &dataset2);

  void intersect(const std::string &newdataset, const std::string &dataset1, const std::string &dataset2);

  void unite(const std::string &newdataset, const std::string &dataset1, const std::string &dataset2);

  using commandMap = Dictionary< std::string, void (*)(const std::string &, const std::string &, const std::string &) >;
  void createCommandMap(commandMap &commands);
}
#endif
