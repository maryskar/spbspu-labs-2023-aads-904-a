#ifndef WORKWITHIO_H
#define WORKWITHIO_H

#include <istream>
#include <ostream>
#include <string>
#include <sstream>
#include "dictionary.h"

namespace potapova
{
  template< typename Comparator >
  std::istream& inputDict(std::istream& in, Dictionary< long long, std::string, Comparator >& dict)
  {
    std::string dict_data;
    if (!std::getline(in, dict_data))
    {
      return in;
    }
    std::stringstream dict_data_stream(dict_data);
    long long key = 0;
    std::string value;
    while (dict_data_stream >> key && dict_data_stream >> value)
    {
      dict.insert(key, value);
    }
    if (!dict_data_stream.eof())
    {
      in.setstate(std::ios_base::failbit);
    }
    return in;
  }

  template< typename Key, typename Value, typename Comparator >
  std::ostream& printDict(std::ostream& out, const Dictionary< Key, Value, Comparator >& dict)
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
