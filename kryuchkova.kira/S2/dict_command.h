#ifndef DICT_COMMAND_H
#define DICT_COMMAND_H
#include <string>
#include <fstream>
#include "dictionary.h"
#include "out_messages.h"

namespace kryuchkova
{
  template< typename Key, typename Value, typename Compare >
  void print(const std::pair< std::string, Dictionary< Key, Value, Compare > > & rhs, std::ostream & out)
  {
    auto dict = rhs.second;
    auto cit = dict.cbegin();
    if (cit == dict.cend())
    {
      outEmpty(out);
      return;
    }
    out << rhs.first;
    while (cit != dict.cend())
    {
      out << " " << cit->first << " " << cit->second;
      cit++;
    }
  }
}

#endif
