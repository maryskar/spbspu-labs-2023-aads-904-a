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
  Dictionary< Key, Value, Compare > merge(const Dictionary< Key, Value, Compare >& lhs,
     const Dictionary< Key, Value, Compare >& rhs)
  {
    if (rhs.isEmpty())
    {
      return lhs;
    }
    auto result = rhs;
    for (auto it = lhs.cbegin(); it != lhs.cend(); it++)
    {
      if (rhs.find(it->first) != rhs.cend())
      {
        result[it->first] = lhs.at(it->first);
      }
      else
      {
        result.insert(*it);
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

  namespace details
  {
    template< typename Key, typename Value, typename Compare >
    Dictionary< Key, Value, Compare > resortDict(const Dictionary< Key, Value, Compare >& dict, Compare comp)
    {
      Dictionary< Key, Value, Compare > new_dict(comp);
      for (auto it = dict.cbegin(); it != dict.cend(); it++)
      {
        new_dict.insert(*it);
      }
      return new_dict;
    }
  }

  template< class Key, class Value, class Compare >
  void swap(Dictionary< Key, Value, Compare >& lhs, Dictionary< Key, Value, Compare >& rhs)
  {
    lhs.swap(rhs);
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

  namespace details
  {
    template< class Key, class Value, class Compare >
    Dictionary< Key, Value, Compare > createRandomDict(size_t size, const Dictionary< Key, Value, Compare >& range)
    {
      Dictionary< Key, Value, Compare > random_dict(range.key_comp());
      while (random_dict.size() != size)
      {
        auto random_elem = *takeRandomElem(range.cbegin(), range.cend());
        random_dict.insert(random_elem);
      }
      return random_dict;
    }
  }

  template< class Key, class Value, class Compare >
  bool isSubset(const Dictionary< Key, Value, Compare > &lhs, const Dictionary< Key, Value, Compare > &rhs)
  {
    if (lhs.isEmpty() || rhs.isEmpty())
    {
      return false;
    }
    auto it = lhs.cbegin();
    for (; it != lhs.cend(); it++)
    {
      if (rhs.find(it->first) == rhs.cend())
      {
        return false;
      }
    }
    return true;
  }
}
#endif
