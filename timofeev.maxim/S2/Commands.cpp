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
}
