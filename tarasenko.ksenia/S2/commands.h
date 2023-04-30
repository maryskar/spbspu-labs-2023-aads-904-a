#ifndef COMMAND_H
#define COMMAND_H
#include <iostream>
#include <stdexcept>
#include "dictionary.h"
namespace tarasenko
{
  template< typename Key, typename Value, typename Compare >
  std::ostream& print(std::ostream& output, const tarasenko::Dictionary< Key, Value, Compare >& dict, const Key& name_of_dict)
  {
    Value given_dict;
    try
    {
      given_dict = dict.get(name_of_dict);
    }
    catch (const std::invalid_argument& e)
    {
      return output << e.what();
    }
    if (given_dict.isEmpty())
    {
      return output << "<EMPTY>";
    }
    return output << name_of_dict << " " << given_dict;
  }
  template< typename Key, typename Value, typename Compare >
  void complement(tarasenko::Dictionary< Key, Value, Compare >& dict_of_dict, std::string name_new_dict, std::string name_dict1, std::string name_dict2)
  {
    auto dict1 = dict_of_dict.get(name_dict1);
    if (dict1.isEmpty())
    {
      throw std::logic_error("The first dictionary is empty!");
    }
    auto dict2 = dict_of_dict.get(name_dict2);
    auto new_dict = dict1 - dict2;
    dict_of_dict.push(name_new_dict, new_dict);
  }
}
#endif
