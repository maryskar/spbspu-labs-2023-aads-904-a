#ifndef WORKWITHIO_H
#define WORKWITHIO_H

#include <istream>
#include <ostream>
#include <string>
#include "dictionary.h"

namespace potapova
{
  const char* parseKey(const char* cur_sym_ptr, long long& key)
  {
    char* end_conv_ptr = nullptr;
    key = std::strtoll(cur_sym_ptr, &end_conv_ptr, 10);
    if (errno == ERANGE || *end_conv_ptr != ' ' && *end_conv_ptr != '\0')
    {
      return nullptr;
    }
    return end_conv_ptr;
  }

  const char* parseValue(const char* cur_sym_ptr, std::string& value)
  {
    while (*cur_sym_ptr != ' ')
    {
      value.push_back(*cur_sym_ptr);
      ++cur_sym_ptr;
    }
    return cur_sym_ptr;
  }

  template< bool (*Compare)(const long long&, const long long&) >
  std::istream& inputDict(std::istream& in, const Dictionary< long long, std::string, Compare >& dict, std::string& name)
  {
    in >> name;
    in.ignore(1);
    std::string keys_and_values;
    if (!std::getline(in, keys_and_values))
    {
      return in;
    }
    const char* cur_sym_ptr(keys_and_values.c_str());
    while (*cur_sym_ptr != '\0')
    {
      long long new_key = 0;
      if ((cur_sym_ptr = parseKey(cur_sym_ptr, new_key)) == nullptr)
      {
        in.setstate(std::ios_base::failbit);
        break;
      }
      std::string new_value;
      cur_sym_ptr = parseValue(++cur_sym_ptr, new_value);
    }
    return in;
  }

  template< typename Key, typename Value, bool (*Compare)(const Key&, const Key&) >
  std::ostream& operator<<(std::ostream& out, const Dictionary< Key, Value, Compare >& dict)
  {
    using ConstIterator = Dictionary< Key, Value, Compare >::ConstIterator;
    if (data_.empty())
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
    out << '\n';
  }
}

#endif
