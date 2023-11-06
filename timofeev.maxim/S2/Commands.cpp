#include "Commands.h"
#include "commandSet.h"
namespace timofeev
{
  void doPrint(std::istream& in, dictOfDicts& dict, std::ostream& out)
  {
    std::string dictName;
    in >> dictName;
    if (dict.contains(dictName))
    {
      dictionary dict_t = dict.at(dictName);
      if (!dict_t.empty())
      {
        out << dictName;
        for (auto &i: dict_t)
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
  void doComplement(std::istream& in, dictOfDicts& dict)
  {
    std::string newDict, first, second;
    in >> newDict >> first >> second;
    if (dict.count(first) == 0 || dict.count(second) == 0)
    {
      throw std::invalid_argument("Logic error");
    }
    dictionary dict1 = dict.at(first);
    dictionary dict2 = dict.at(second);
    dictionary complDict;
    for (const auto &tmp: dict1)
    {
      if (!dict2.contains(tmp.first))
      {
        complDict.insert(tmp);
      }
    }
    dict[newDict] = complDict;

  }
  void doIntersect(std::istream& in, dictOfDicts& dict)
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
      dictionary intersDict;
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

  void doUnion(std::istream& in, dictOfDicts& dict)
  {
    std::string newDict, first, second;
    in >> newDict >> first >> second;
    if (dict.count(first) == 0 || dict.count(second) == 0)
    {
      throw std::invalid_argument("Logic error");
    }
    const auto& dict1 = dict.at(first);
    const auto& dict2 = dict.at(second);
    dictionary unDict = dict1;
    for (const auto& entry: dict2)
    {
      if (!unDict.contains(entry.first))
      {
        unDict.insert(entry);
      }
    }
    dict[newDict] = unDict;
  }
}
