#ifndef COMMAND_H
#define COMMAND_H
#include <iostream>
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
}
#endif
