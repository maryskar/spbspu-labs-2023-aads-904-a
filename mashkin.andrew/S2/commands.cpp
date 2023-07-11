#include "commands.h"
#include <iostream>
#include "IOrealization.h"

namespace mashkin
{
  void print(std::istream& inp, dictionaries& dicts)
  {
    std::string dictionary;
    inp >> dictionary;
    if (dicts.contains(dictionary))
    {
      auto iter = dicts.find(dictionary);
      std::cout << iter->first << iter->second << "\n";
    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
      inp.setstate(std::ios::failbit);
    }
  }

  void complement(std::istream& inp, dictionaries& dicts)
  {
    std::string newDict;
    inp >> newDict;
    std::string first;
    inp >> first;
    std::string second;
    inp >> second;
    if (!dicts.contains(second) || first == second || !dicts.contains(first) || dicts.contains(newDict))
    {
      std::cout << "<INVALID COMMAND>\n";
      inp.setstate(std::ios::failbit);
      return;
    }
    dict newDictionary;
    auto firstDict = dicts.find(first);
    auto firstBegin = firstDict->second.begin();
    auto firstEnd = firstDict->second.end();
    for (auto i = firstBegin; i != firstEnd; i++)
    {
      if (!dicts.find(second)->second.contains(i->first))
      {
        newDictionary.insert(*i);
      }
    }
    auto secondDict = dicts.find(second);
    auto secondBegin = secondDict->second.begin();
    auto secondEnd = secondDict->second.end();
    for (auto i = secondBegin; i != secondEnd; i++)
    {
      if (!dicts.find(first)->second.contains(i->first))
      {
        newDictionary.insert(*i);
      }
    }
    dicts.insert({newDict, newDictionary});
  }
}
