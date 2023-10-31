#ifndef WORKWITHIO_H
#define WORKWITHIO_H

#include <istream>
#include <ostream>
#include <string>
#include "dictionary.h"

namespace potapova
{
  template< bool (*Compare)(const long long&, const long long&) >
  std::istream& operator>>(std::istream& in, Dictionary< long long, std::string, Compare >& dict)
  {
    std::istream::int_type cur_input_sym = in.rdbuf()->sgetc();
    while (cur_input_sym != '\n' && std::isspace(cur_input_sym))
    {
      in.ignore(1);
      cur_input_sym = in.rdbuf()->sgetc();
    }
    long long key;
    std::string value;
    while (cur_input_sym != '\n' && cur_input_sym != EOF)
    {
      if (!(in >> key) || !(in >> value))
      {
        return in;
      }
      dict.insert(key, value);
      cur_input_sym = in.rdbuf()->sgetc();
    }
    return in;
  }

  template< typename Key, typename Value, bool (*Compare)(const Key&, const Key&) >
  std::ostream& operator<<(std::ostream& out, const Dictionary< Key, Value, Compare >& dict)
  {
    using ConstIterator = typename Dictionary< Key, Value, Compare >::ConstIterator;
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
