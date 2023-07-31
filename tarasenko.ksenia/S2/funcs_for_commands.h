#ifndef FUNCS_FOR_COMMANDS_H
#define FUNCS_FOR_COMMANDS_H

#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <compare.h>
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
    for ( ; it != dict_of_dict.cend(); it++)
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

  template< class Key, class Value, class Compare >
  void deleteDicts(std::istream& input, Dictionary< std::string,
     Dictionary< Key, Value, Compare >, std::greater<> >& dict_of_dict)
  {
    ForwardList< std::string > keys = getKeys(input);
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
    ForwardList< std::string > keys = getKeys(input);
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
    for ( ; it != dict_of_dict.end(); it++)
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
    ForwardList< std::string > keys = getKeys(input);
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

//  update <dataset-1> <dataset-2>
//  (обновляет значения первого словаря значениями из второго словаря по совпадающим ключам)
//  first 1 base 2 market 3 cats
//  second 1 name 2 sec 4 mouse
//
//  update first second
//  print first
//  1 name 2 sec 3 cats

//    merge <dataset-1> <dataset-2> (добавляет ключи из второго словаря в первый.
//    Если ключи дублируются, в качестве значения выбираются данные из правого операнда)
//
//    merge first second
//    print first
//    1 name 2 sec 3 cats 4 mouse
//    random <newdataset> <size><dataset-1><dataset-2>...
//    (создает, новый словарь с заданный количеством случайным слов из указанных словарей)

//  random four 4
//  print four
//  1 dog 2 tree 3 fish 4 frogs

//  subset <dataset-1> <dataset-2> ( проверяет, является ли первый словарь подмножеством второго)
//  subset second first
//  true
}
#endif
