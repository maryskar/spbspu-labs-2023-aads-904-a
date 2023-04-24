#ifndef COMMAND_H
#define COMMAND_H
#include <iostream>
#include "dictionary.h"
namespace tarasenko
{
  template< typename Key, typename Value, typename Compare >
  std::ostream& print(std::ostream& output, const tarasenko::Dictionary< Key, Value, Compare >& dict, const Key& name_of_dict)
  {
    try
    {
      Value result = dict.get(name_of_dict);
    }
    catch (const std::invalid_argument& e)
    {
      return output << e.what();
    }
    return output << name_of_dict << " " << dict.get(name_of_dict);
  }
}
#endif
