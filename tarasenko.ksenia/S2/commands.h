#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <stdexcept>
#include <string>
#include "dictionary.h"

namespace tarasenko
{
  template< typename Key, typename Value, typename Compare >
  using dict_type = tarasenko::Dictionary< Key, Value, Compare >;

  template< typename Key, typename Value, typename Compare >
  void call(const std::string& name_of_command, dict_type< Key, Value, Compare >& dict_of_dict, std::istream& input,
            std::ostream& output)
  {
    if (name_of_command == "print")
    {
      std::string name_of_dict = "";
      input >> name_of_dict;
      print(std::cout, dict_of_dict, name_of_dict);
      output << "\n";
    }
    else if (name_of_command == "complement" || name_of_command == "intersect" || name_of_command == "union")
    {
      std::string name_new_dict = "";
      std::string name_dict1 = "";
      std::string name_dict2 = "";
      input >> name_new_dict >> name_dict1 >> name_dict2;
      if (!dict_of_dict.find(name_dict1) || !dict_of_dict.find(name_dict2))
      {
        output << "<INVALID COMMAND>" << "\n";
        return;
      }
      auto dict1 = dict_of_dict.at(name_dict1);
      auto dict2 = dict_of_dict.at(name_dict2);
      if (name_of_command == "complement")
      {
        if (dict1.isEmpty())
        {
          output << "<INVALID COMMAND>" << "\n";
          return;
        }
        auto new_dict = dict1 - dict2;
        dict_of_dict.push(name_new_dict, new_dict);
      }
      else if (name_of_command == "intersect")
      {
        auto new_dict = dict1 && dict2;
        dict_of_dict.push(name_new_dict, new_dict);
      }
      else if (name_of_command == "union")
      {
        auto new_dict = dict1 || dict2;
        dict_of_dict.push(name_new_dict, new_dict);
      }
    }
    else
    {
      output << "<INVALID COMMAND>" << "\n";
      std::string trash = "";
      getline(input, trash);
    }
  }

  template< typename Key, typename Value, typename Compare >
  std::ostream& print(std::ostream& output, const dict_type< Key, Value, Compare >& dict, const Key& name_of_dict)
  {
    Value given_dict;
    try
    {
      given_dict = dict.at(name_of_dict);
    }
    catch (const std::out_of_range& e)
    {
      return output << "<INVALID COMMAND>";
    }
    if (given_dict.isEmpty())
    {
      return output << "<EMPTY>";
    }
    return output << name_of_dict << " " << given_dict;
  }
}
#endif
