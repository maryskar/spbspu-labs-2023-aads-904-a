#ifndef FA_FUNCS_FOR_MAP_COMMANDS_H
#define FA_FUNCS_FOR_MAP_COMMANDS_H

#include <iostream>
#include <fstream>
#include <string>
#include "dictionary.h"
#include "funcs_for_commands.h"

namespace tarasenko
{
  template< class Key, class Value, class Compare >
  using dict_tt = Dictionary< Key, Value, Compare >;
  template< class Key, class Value, class Compare >
  using dict_of_dict_t = Dictionary< std::string, dict_tt< Key, Value, Compare >, std::greater<> >;

  template< typename Key, typename Value, typename Compare >
  std::pair< dict_tt< Key, Value, Compare >, dict_tt< Key, Value, Compare > > getTwoDicts(std::istream& in,
     const dict_of_dict_t< Key, Value, Compare >& dict_of_dict)
  {
    std::string name_dict1 = " ";
    std::string name_dict2 = " ";
    in >> name_dict1 >> name_dict2;
    auto dict1 = dict_of_dict.at(name_dict1);
    auto dict2 = dict_of_dict.at(name_dict2);
    return std::make_pair(dict1, dict2);
  }

  template< typename Key, typename Value, typename Compare >
  std::istream& complementCommand(std::istream& in, dict_of_dict_t< Key, Value, Compare >& dict_of_dict)
  {
    std::string name_new_dict = " ";
    in >> name_new_dict;
    auto res = getTwoDicts(in, dict_of_dict);
    auto new_dict = complement(res.first, res.second);
    dict_of_dict.push(name_new_dict, new_dict);
    return in;
  }

  template< typename Key, typename Value, typename Compare >
  std::istream& intersectCommand(std::istream& in, dict_of_dict_t< Key, Value, Compare >& dict_of_dict)
  {
    std::string name_new_dict = " ";
    in >> name_new_dict;
    auto res = getTwoDicts(in, dict_of_dict);
    auto new_dict = intersect(res.first, res.second);
    dict_of_dict.push(name_new_dict, new_dict);
    return in;
  }

  template< typename Key, typename Value, typename Compare >
  std::istream& unionCommand(std::istream& in, dict_of_dict_t< Key, Value, Compare >& dict_of_dict)
  {
    std::string name_new_dict = " ";
    in >> name_new_dict;
    auto res = getTwoDicts(in, dict_of_dict);
    auto new_dict = unionWith(res.first, res.second);
    dict_of_dict.push(name_new_dict, new_dict);
    return in;
  }

  template< typename Key, typename Value, typename Compare >
  std::istream& mergeCommand(std::istream& in, dict_of_dict_t< Key, Value, Compare >& dict_of_dict)
  {
    std::string name_new_dict = " ";
    in >> name_new_dict;
    auto res = getTwoDicts(in, dict_of_dict);
    auto new_dict = merge(res.first, res.second);
    dict_of_dict.push(name_new_dict, new_dict);
    return in;
  }

  template< class Key, class Value, class Compare >
  std::ostream& printCommand(std::ostream& out, std::istream& in,
     const dict_of_dict_t< Key, Value, Compare >& dict_of_dict)
  {
    std::string name_of_dict = " ";
    in >> name_of_dict;
    Dictionary< Key, Value, Compare > given_dict = dict_of_dict.at(name_of_dict);
    if (given_dict.isEmpty())
    {
      throw std::invalid_argument("Empty");
    }
    printDict(out, name_of_dict, given_dict);
    return out << "\n";
  }

  template< class Key, class Value, class Compare >
  std::ostream& printIfCommand(std::ostream& out, std::istream& in,
     const dict_of_dict_t< Key, Value, Compare >& dict_of_dict)
  {
    Key key;
    in >> key;
    auto it = dict_of_dict.cbegin();
    bool was_out = false;
    for (; it != dict_of_dict.cend(); it++)
    {
      if (it->second.find(key) != it->second.cend())
      {
        if (was_out)
        {
          out << " " << it->first;
        }
        else
        {
          out << it->first;
          was_out = true;
        }
      }
    }
    return out << "\n";
  }

  template< class Key, class Value, class Compare >
  std::istream& addCommand(std::istream& in, dict_of_dict_t< Key, Value, Compare >& dict_of_dict)
  {
    add(in, dict_of_dict);
    return in;
  }

  template< class Key, class Value, class Compare >
  std::istream& deleteCommand(std::istream& in, dict_of_dict_t< Key, Value, Compare >& dict_of_dict)
  {
    ForwardList< std::string > keys = details::getKeys(in);
    for (auto i: keys)
    {
      dict_of_dict.remove(i);
    }
    return in;
  }

  template< class Key, class Value, class Compare >
  std::ostream& writeCommand(std::ostream& output, std::istream& in,
     const dict_of_dict_t< Key, Value, Compare >& dict_of_dict)
  {
    std::string filename = " ";
    in >> filename;
    std::ofstream out;
    out.open(filename);
    if (!out.is_open())
    {
      throw std::invalid_argument("File not found");
    }
    ForwardList< std::string > keys = details::getKeys(in);
    for (auto i: keys)
    {
      printDict(out, i, dict_of_dict.at(i)) << "\n";
    }
    return output;
  }

  template< class Key, class Value, class Compare >
  std::istream& resortCommand(std::istream& in, dict_of_dict_t< Key, Value, Compare >& dict_of_dict)
  {
    std::string sort = " ";
    in >> sort;
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
      dict_of_dict[it->first] = details::resortDict(it->second, comp);
    }
    return in;
  }

  template< class Key, class Value, class Compare >
  std::istream& putCommand(std::istream& in, dict_of_dict_t< Key, Value, Compare >& dict_of_dict)
  {
    Key new_key;
    Value new_val;
    in >> new_key >> new_val;
    if (!in)
    {
      throw std::invalid_argument("Incorrect data");
    }
    ForwardList< std::string > keys = details::getKeys(in);
    for (auto i: keys)
    {
      dict_of_dict[i].push(new_key, new_val);
    }
    return in;
  }

  template< class Key, class Value, class Compare >
  std::istream& swapCommand(std::istream& in, dict_of_dict_t< Key, Value, Compare >& dict_of_dict)
  {
    std::string name_dict1 = " ";
    std::string name_dict2 = " ";
    in >> name_dict1 >> name_dict2;
    auto dict1 = dict_of_dict.at(name_dict1);
    auto dict2 = dict_of_dict.at(name_dict2);
    swap(dict1, dict2);
    dict_of_dict[name_dict1] = dict1;
    dict_of_dict[name_dict2] = dict2;
    return in;
  }

  template< class Key, class Value, class Compare >
  std::istream& copyCommand(std::istream& in, dict_of_dict_t< Key, Value, Compare >& dict_of_dict)
  {
    std::string name_dict = " ";
    std::string name_new_dict = " ";
    in >> name_dict >> name_new_dict;
    auto dict = dict_of_dict.at(name_dict);
    dict_of_dict.push(name_new_dict, dict);
    return in;
  }

  template< class Key, class Value, class Compare >
  std::istream& updateCommand(std::istream& in, dict_of_dict_t< Key, Value, Compare >& dict_of_dict)
  {
    std::string name_dict1 = " ";
    std::string name_dict2 = " ";
    in >> name_dict1 >> name_dict2;
    auto dict1 = dict_of_dict.at(name_dict1);
    auto dict2 = dict_of_dict.at(name_dict2);
    update(dict1, dict2);
    dict_of_dict[name_dict1] = dict1;
    dict_of_dict[name_dict2] = dict2;
    return in;
  }

  template< class Key, class Value, class Compare >
  std::istream& randomCommand(std::istream& in, dict_of_dict_t< Key, Value, Compare >& dict_of_dict)
  {
    std::string name_new_dict = " ";
    size_t size = 0;
    in >> name_new_dict >> size;
    if (!in)
    {
      throw std::invalid_argument("Incorrect data");
    }
    ForwardList< std::string > names_of_dicts = details::getKeys(in);

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

    dict_of_dict.push(name_new_dict, details::createRandomDict(size, dict_of_elems));
    return in;
  }

  template< class Key, class Value, class Compare >
  std::ostream& subsetCommand(std::ostream& out, std::istream& in,
     const dict_of_dict_t< Key, Value, Compare >& dict_of_dict)
  {
    auto dicts = getTwoDicts(in, dict_of_dict);
    return out << std::boolalpha << isSubset(dicts.first, dicts.second) << "\n";
  }
}
#endif
