#ifndef S4_COMMANDS_H
#define S4_COMMANDS_H
#include <iostream>
#include <string>

namespace mashkin
{
  template< class T >
  void print(std::istream& inp, T& dicts)
  {
    std::string dictionary;
    inp >> dictionary;
    if (dicts.contains(dictionary))
    {
      auto iter = dicts.find(dictionary);
      if (iter->second.size() == 0)
      {
        std::cout << "<EMPTY>\n";
      }
      else
      {
        std::cout << iter->first << iter->second << "\n";
      }
    }
    else
    {
      throw std::logic_error("Logic error");
    }
  }

  template< class T >
  void complement(std::istream& inp, T& dicts)
  {
    std::string newDict;
    inp >> newDict;
    std::string first;
    inp >> first;
    std::string second;
    inp >> second;
    if (!dicts.contains(second) || !dicts.contains(first))
    {
      throw std::logic_error("Logic error");
    }
    decltype(dicts.begin()->second) newDictionary;
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
    if (first == newDict)
    {
      dicts.find(first)->second.clear();
      dicts.find(first)->second.insert(newDictionary.begin(), newDictionary.end());
      return;
    }
    else if (second == newDict)
    {
      dicts.find(second)->second.clear();
      dicts.find(second)->second.insert(newDictionary.begin(), newDictionary.end());
      return;
    }
    else
    {
      dicts.insert({newDict, newDictionary});
    }
  }

  template< class T >
  void intersect(std::istream& inp, T& dicts)
  {
    std::string newDict;
    inp >> newDict;
    std::string first;
    inp >> first;
    std::string second;
    inp >> second;
    if (dicts.contains(newDict) && newDict != first && newDict != second)
    {
      dicts.find(newDict)->second.clear();
    }
    if (!dicts.contains(second) || !dicts.contains(first))
    {
      throw std::logic_error("Logic error");
    }
    decltype(dicts.begin()->second) newDictionary;
    auto firstDict = dicts.find(first);
    auto firstBegin = firstDict->second.begin();
    auto firstEnd = firstDict->second.end();
    for (auto i = firstBegin; i != firstEnd; i++)
    {
      if (dicts.find(second)->second.contains(i->first))
      {
        newDictionary.insert(*i);
      }
    }
    if (first == newDict)
    {
      dicts.find(first)->second.clear();
      dicts.find(first)->second.insert(newDictionary.begin(), newDictionary.end());
      return;
    }
    else if (second == newDict)
    {
      dicts.find(second)->second.clear();
      dicts.find(second)->second.insert(newDictionary.begin(), newDictionary.end());
      return;
    }
    else
    {
      dicts.insert({newDict, newDictionary});
    }
  }

  template< class T >
  void unionDicts(std::istream& inp, T& dicts)
  {
    std::string newDict;
    inp >> newDict;
    std::string first;
    inp >> first;
    std::string second;
    inp >> second;
    if (!dicts.contains(second) || !dicts.contains(first))
    {
      throw std::logic_error("Logic error");
    }
    decltype(dicts.begin()->second) newDictionary = dicts.find(first)->second;
    auto secondDict = dicts.find(second);
    auto secondBegin = secondDict->second.begin();
    auto secondEnd = secondDict->second.end();
    for (auto i = secondBegin; i != secondEnd; i++)
    {
      if (!newDictionary.contains(i->first))
      {
        newDictionary.insert(*i);
      }
    }
    if (first == newDict)
    {
      dicts.find(first)->second.clear();
      dicts.find(first)->second.insert(newDictionary.begin(), newDictionary.end());
      return;
    }
    else if (second == newDict)
    {
      dicts.find(second)->second.clear();
      dicts.find(second)->second.insert(newDictionary.begin(), newDictionary.end());
      return;
    }
    else
    {
      dicts.insert({newDict, newDictionary});
    }
  }
}
#endif
