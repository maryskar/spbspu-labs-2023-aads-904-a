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
        }
        else
        {
          out << "<EMPTY>" << '\n';
          return;
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
      if (!dict.contains(second) || !dict.contains(first))
      {
        throw std::logic_error("Logic error");
      }
      dictionary complDict;
      const auto &firstDict = dict[first];
      const auto &secondDict = dict[second];
      for (const auto &entry: firstDict)
      {
        bool firstFlag = false;
        for (const auto &tmp: secondDict)
        {
          if (entry.first == tmp.first)
          {
            firstFlag = true;
            break;
          }
        }
        if (!firstFlag)
        {
          complDict.insert(entry);
        }
      }
      if (first == newDict)
      {
        dict[first].clear();
        dict[first].insert(complDict.begin(), complDict.end());
      }
      else if (second == newDict)
      {
        dict[second].clear();
        dict[second].insert(complDict.begin(), complDict.end());
      }
      else
      {
        dict.insert({newDict, complDict});
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
      if (!dict.contains(first) || dict.contains(second))
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
    if (!dict.contains(first) || dict.contains(second))
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
