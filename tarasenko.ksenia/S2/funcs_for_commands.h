#ifndef FUNCS_FOR_COMMANDS_H
#define FUNCS_FOR_COMMANDS_H

#include <iostream>
#include <fstream>
#include <string>
#include <compare.h>
#include <take_random_elem.h>
#include "dictionary.h"

namespace tarasenko
{
  template< class Key, class Value, class Compare >
  Dictionary< Key, Value, Compare > complement(const Dictionary< Key, Value, Compare >& lhs,
     const Dictionary< Key, Value, Compare >& rhs)
  {
    auto result = lhs;
    if (!lhs.isEmpty() && !rhs.isEmpty())
    {
      auto iter_lhs = lhs.cbegin();
      for (; iter_lhs != lhs.cend(); iter_lhs++)
      {
        if (rhs.find((*iter_lhs).first) != rhs.cend())
        {
          result.remove((*iter_lhs).first);
        }
      }
    }
    return result;
  }

  template< class Key, class Value, class Compare >
  Dictionary< Key, Value, Compare > intersect(const Dictionary< Key, Value, Compare >& lhs,
     const Dictionary< Key, Value, Compare >& rhs)
  {
    if (rhs.isEmpty())
    {
      return rhs;
    }
    Dictionary< Key, Value, Compare > result(lhs.key_comp());
    if (!lhs.isEmpty())
    {
      auto iter_lhs = lhs.cbegin();
      for (; iter_lhs != lhs.cend(); iter_lhs++)
      {
        if (rhs.find((*iter_lhs).first) != rhs.cend())
        {
          result.push((*iter_lhs).first, (*iter_lhs).second);
        }
      }
    }
    return result;
  }

  template< class Key, class Value, class Compare >
  Dictionary< Key, Value, Compare > unionWith(const Dictionary< Key, Value, Compare >& lhs,
     const Dictionary< Key, Value, Compare >& rhs)
  {
    if (lhs.isEmpty())
    {
      return rhs;
    }
    auto result = lhs;
    if (!rhs.isEmpty())
    {
      auto iter_rhs = rhs.cbegin();
      for (; iter_rhs != rhs.cend(); iter_rhs++)
      {
        if (lhs.find((*iter_rhs).first) == lhs.cend())
        {
          result.push((*iter_rhs).first, (*iter_rhs).second);
        }
      }
    }
    return result;
  }

  template< class Key, class Value, class Compare >
  std::ostream& printDict(std::ostream& output, const std::string& name_of_dict,
     const Dictionary< Key, Value, Compare >& dict)
  {
    if (!dict.isEmpty())
    {
      output << name_of_dict << " ";
      auto iter = dict.cbegin();
      output << iter->first << " " << iter->second;
      ++iter;
      while (iter != dict.cend())
      {
        output << " " << iter->first << " " << iter->second;
        ++iter;
      }
    }
    return output;
  }

  template< class Key, class Value, class Compare >
  std::ostream& print(std::ostream& output, const std::string& name_of_dict,
     const Dictionary< std::string, Dictionary< Key, Value, Compare >, std::greater<> >& dict_of_dict)
  {
    Dictionary< Key, Value, Compare > given_dict = dict_of_dict.at(name_of_dict);
    if (given_dict.isEmpty())
    {
      throw std::invalid_argument("Empty");
    }
    printDict(output, name_of_dict, given_dict) << "\n";
    return output;
  }

  template< class Key, class Value, class Compare >
  std::ostream& printIf(std::ostream& output, const std::string& key,
     const Dictionary< std::string, Dictionary< Key, Value, Compare >, std::greater<> >& dict_of_dict)
  {
    auto it = dict_of_dict.cbegin();
    auto key_dict = std::stoll(key);
    bool was_out = false;
    for (; it != dict_of_dict.cend(); it++)
    {
      if (it->second.find(key_dict) != it->second.cend())
      {
        if (was_out)
        {
          output << " " << it->first;
        }
        else
        {
          output << it->first;
          was_out = true;
        }
      }
    }
    return output << "\n";
  }

  template< class Key, class Value, class Compare >
  std::istream& operator>>(std::istream& input, Dictionary< Key, Value, Compare >& dict)
  {
    Key key;
    Value value;
    while (input >> key >> value)
    {
      dict.push(key, value);
    }
    return input;
  }

  template< class Key, class Value, class Compare >
  void add(std::istream& input, Dictionary< Key, Value, Compare >& dict)
  {
    while (input)
    {
      char begin = ' ';
      input >> begin;
      if (begin != '(')
      {
        input.putback(begin);
        break;
      }
      char end = ' ';
      while (input >> end)
      {
        if (end == ')')
        {
          break;
        }
        else
        {
          input.putback(end);
        }
        Key key;
        Value value;
        input >> key >> value;
        dict.push(key, value);
        input.clear();
      }
    }
  }

  namespace details
  {
    ForwardList< std::string > getKeys(std::istream& input)
    {
      ForwardList< std::string > keys;
      std::string line;
      std::getline(input, line);
      std::string key = "";
      for (size_t i = 0; i < line.size(); i++)
      {
        if (line[i] == ' ')
        {
          if (key != "")
          {
            keys.pushBack(key);
            key = "";
          }
        }
        else
        {
          key += line[i];
        }
      }
      if (key != "")
      {
        keys.pushBack(key);
      }
      return keys;
    }
  }

  template< class Key, class Value, class Compare >
  void deleteDicts(std::istream& input, Dictionary< std::string,
     Dictionary< Key, Value, Compare >, std::greater<> >& dict_of_dict)
  {
    ForwardList< std::string > keys = details::getKeys(input);
    for (auto i: keys)
    {
      dict_of_dict.remove(i);
    }
  }

  template< class Key, class Value, class Compare >
  void writeDicts(std::istream& input, Dictionary< std::string,
     Dictionary< Key, Value, Compare >, std::greater<> >& dict_of_dict)
  {
    std::string filename = " ";
    input >> filename;
    std::ofstream out;
    out.open(filename);
    if (!out.is_open())
    {
      throw std::invalid_argument("File not found");
    }
    ForwardList< std::string > keys = details::getKeys(input);
    for (auto i: keys)
    {
      printDict(out, i, dict_of_dict.at(i)) << "\n";
    }
  }

  template< class Key, class Value, class Compare >
  void resort(std::istream& input, Dictionary< std::string,
     Dictionary< Key, Value, Compare >, std::greater<> >& dict_of_dict)
  {
    std::string sort = " ";
    input >> sort;
    Comp comp;
    if (sort == "ascending")
    {
      Comp ascending(std::less<>{});
      comp = ascending;
    }
    else if (sort == "descending")
    {
      Comp descending(std::greater<>{});
      comp = descending;
    }
    else
    {
      throw std::invalid_argument("Invalid command");
    }
    auto it = dict_of_dict.begin();
    for (; it != dict_of_dict.end(); it++)
    {
      it->second.setCompare(comp);
    }
  }

  template< class Key, class Value, class Compare >
  void put(std::istream& input, Dictionary< std::string,
    Dictionary< Key, Value, Compare >, std::greater<> >& dict_of_dict)
  {
    Key new_key;
    Value new_val;
    input >> new_key >> new_val;
    if (!input)
    {
      throw std::invalid_argument("Incorrect data");
    }
    ForwardList< std::string > keys = details::getKeys(input);
    for (auto i: keys)
    {
      dict_of_dict[i].push(new_key, new_val);
    }
  }

  template< class Key, class Value, class Compare >
  void swap(Dictionary< Key, Value, Compare >& lhs, Dictionary< Key, Value, Compare >& rhs)
  {
    lhs.swap(rhs);
  }

  template< class Key, class Value, class Compare >
  void copy(std::istream& input, Dictionary< std::string,
     Dictionary< Key, Value, Compare >, std::greater<> >& dict_of_dict)
  {
    std::string name_dict = " ";
    std::string name_new_dict = " ";
    input >> name_dict >> name_new_dict;
    auto dict = dict_of_dict.at(name_dict);
    dict_of_dict.push(name_new_dict, dict);
  }

  template< class Key, class Value, class Compare >
  void update(Dictionary< Key, Value, Compare > &updated, Dictionary< Key, Value, Compare > &dict)
  {
    if (dict.isEmpty() || updated.isEmpty())
    {
      return;
    }
    auto it = updated.begin();
    for (; it != updated.end(); it++)
    {
      if (dict.find(it->first) != dict.end())
      {
        updated[it->first] = dict[it->first];
      }
    }
  }

  template< class Key, class Value, class Compare >
  void merge(Dictionary< Key, Value, Compare > &merging, Dictionary< Key, Value, Compare > &dict)
  {
    if (merging.isEmpty())
    {
      return;
    }
    auto it = merging.begin();
    for (; it != merging.end(); it++)
    {
      if (dict.find(it->first) != dict.end())
      {
        dict[it->first] = merging[it->first];
      }
      else
      {
        dict.insert(*it);
      }
    }
  }

  template< class Key, class Value, class Compare >
  void addRandomDict(std::istream& input, Dictionary< std::string,
    Dictionary< Key, Value, Compare >, std::greater<> >& dict_of_dict)
  {
    std::string name_new_dict = " ";
    size_t size = 0;
    input >> name_new_dict >> size;
    if (!input)
    {
      throw std::invalid_argument("Incorrect data");
    }
    ForwardList< std::string > names_of_dicts = details::getKeys(input);

    Dictionary< Key, Value, Compare > dict_of_elems;
    auto i = names_of_dicts.begin();
    for (; i != names_of_dicts.end(); i++)
    {
      auto dict = dict_of_dict.at(*i);
      for (auto j = dict.begin(); j != dict.end(); j++)
      {
        dict_of_elems.insert(*j);
      }
    }
    if (dict_of_elems.size() < size)
    {
      throw std::invalid_argument("Not enough elements");
    }

    Dictionary< Key, Value, Compare > random_dict;
    while (random_dict.size() != size)
    {
      auto random_elem = *takeRandomElem(dict_of_elems.begin(), dict_of_elems.end());
      random_dict.insert(random_elem);
    }
    dict_of_dict.push(name_new_dict, random_dict);
  }

//  subset <dataset-1> <dataset-2> ( проверяет, является ли первый словарь подмножеством второго)
//  subset second first
//  true
}
#endif
