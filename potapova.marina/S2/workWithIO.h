#ifndef WORKWITHIO_H
#define WORKWITHIO_H

#include <istream>
#include <ostream>
#include <string>
#include "dictionary.h"

namespace potapova
{
  template< typename Comparator >
  std::istream& operator>>(std::istream& in, Dictionary< long long, std::string, Comparator >& dict)
  {
    long long key = 0;
    std::string value;
    while (in.rdbuf()->sgetc() != '\n' && !in.eof())
    {
      if (!(in >> key) || !(in >> value))
      {
        return in;
      }
      dict.insert(key, value);
    }
    return in;
  }

  template< typename Key, typename Value, typename Comparator >
  std::ostream& operator<<(std::ostream& out, const Dictionary< Key, Value, Comparator >& dict)
  {
    using ConstIterator = typename Dictionary< Key, Value, Comparator >::ConstIterator;
    if (dict.empty())
    {
      out << "<EMPTY>" << '\n';
      return out;
    }
    ConstIterator cur_node_ptr = dict.begin();
    out << cur_node_ptr->key << ' ' << cur_node_ptr->value;
    ++cur_node_ptr;
    for (; cur_node_ptr != dict.end(); ++cur_node_ptr)
    {
      out << ' ' << cur_node_ptr->key << ' ' << cur_node_ptr->value;
    }
    return out << '\n';
  }
}

#endif
