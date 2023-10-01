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
          for (auto & i: dict_t)
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
        throw std::invalid_argument("EMPTY");
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
      if (newDict == first)
      {
        dict[first] = complDict;
      }
      else if (newDict == second)
      {
        dict[second] = complDict;
      }
      else
      {
        dict.push(newDict, complDict);
      }
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
        if (newDict == first)
        {
          dict[first] = intersDict;
        }
        else if (newDict == second)
        {
          dict[second] = intersDict;
        }
        else
        {
          dict.push(newDict, intersDict);
        }
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
      throw std::invalid_argument("Logic error");
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
    if (newDict == first)
    {
      dict[first] = unDict;
    }
    else if (newDict == second)
    {
      dict[second] = unDict;
    }
    else
    {
      dict.push(newDict, unDict);
    }
  }
}
