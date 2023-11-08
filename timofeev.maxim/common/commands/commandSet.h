#ifndef COMMANDSET_H
#define COMMANDSET_H
#include <string>
#include "Commands.h"
#include "Dictionary.h"
namespace timofeev
{
  template< typename T >
  void doPrint(std::istream& in, T& dict, std::ostream& out)
  {
    std::string dictName;
    in >> dictName;
    if (dict.contains(dictName))
    {
      auto dict_t = dict.at(dictName);
      if (!dict_t.empty())
      {
        out << dictName;
        for (auto & i : dict_t)
        {
          out << " " << i.first << " " << i.second;
        }
        out << "\n";
      }
      else
      {
        throw std::out_of_range("EMPTY");
      }
    }
    else
    {
      throw std::invalid_argument("Logic error");
    }
  }
  template< typename T, typename B >
  T cmdSet()
  {
    T command;
    command["complement"] = doComplement;
    command["intersect"] = doIntersect;
    command["union"] = doUnion;
    return command;
  }
}
#endif
