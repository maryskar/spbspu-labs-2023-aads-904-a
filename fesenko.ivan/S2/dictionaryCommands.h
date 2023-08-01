#ifndef DICTIONARYCOMMANDS_H
#define DICTIONARYCOMMANDS_H
#include <fstream>
#include <string>
#include "dictionary.h"
#include "messages.h"

namespace fesenko
{
  template< typename Key, typename Value, typename Compare >
  void print(const std::pair< std::string, Dictionary< Key, Value, Compare > > &rhs, std::ostream &out)
  {
    auto dict = rhs.second;
    auto cit = dict.cbegin();
    if (cit == dict.cend()) {
      outEmptyMessage(out);
      return;
    }
    out << rhs.first;
    while (cit != dict.cend()) {
      out << " " << cit->first << " " << cit->second;
      cit++;
    }
    out << "\n";
  }
}
#endif
