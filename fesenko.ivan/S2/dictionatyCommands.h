#ifndef DICTIONARYCOMMANDS_H
#define DICTIONARYCOMMANDS_H
#include "dictionary.h"
#include "messages.h"

namespace fesenko
{
  template< typename Key, typename Value, typename Compare >
  void print(const std::pair< std::string, Dictionary< Key, Value, Compare > > &rhs, std::ostream &out)
  {
    auto dict = rhs.second;
    if (dict.size() == 0) {
      outEmptyMessage(out);
      return;
    }
    const_iterator cit = dict.cbegin();
    out << rhs.first();
    while (cit != cend()) {
      out << " " << cit->first << " " << cit->second;
      cit++;
    }
    out << "\n";
  }
}
#endif
