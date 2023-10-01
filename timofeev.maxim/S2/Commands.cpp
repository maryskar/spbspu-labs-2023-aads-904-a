#include "Commands.h"
#include "commandSet.h"
namespace timofeev
{
  void Print(std::istream& in, dictOfDicts& dict, std::ostream& out)
  {
    try
    {
      std::string dictName;
      in >> dictName;
      if (dict.contains(dictName))
      {
        dictionary dict_t = dict.at(dictName);
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
          throw std::logic_error("logic_error");
        }
      }
      else
      {
        return;
      }
    }
    catch (...)
    {
      throw;
    }
  }
  void Complement(std::istream& in, dictOfDicts& dict)
  {
    try
    {
      std::string newDict, first, second;
      in >> newDict >> first >> second;
      if (dict.count(first) == 0 || dict.count(second) == 0)
      {
        throw std::logic_error("Logic error");
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
      dict.push(newDict, complDict);
    }
    catch (...)
    {
      throw;
    }
  }
  void Intersect(std::istream& in, dictOfDicts& dict)
  {
    try
    {
      std::string newDict, first, second;
      in >> newDict >> first >> second;
      if (dict.count(first) == 0 || dict.count(second) == 0)
      {
        throw std::logic_error("Logic error");
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
        dict.push(newDict, intersDict);
      }
    }
    catch (...)
    {
      throw;
    }
  }

  void Union(std::istream& in, dictOfDicts& dict)
  {
    std::string newDict, first, second;
    in >> newDict >> first >> second;
    if (dict.count(first) == 0 || dict.count(second) == 0)
    {
      throw std::logic_error("Logic error");
    }
    const auto& dict1 = dict.at(first);
    const auto& dict2 = dict.at(second);
    dictionary unDict = dict1;
    for (const auto& entry : dict2)
    {
      if (!unDict.contains(entry.first))
      {
        unDict.insert(entry);
      }
    }
    dict.push(newDict, unDict);
  }
}
