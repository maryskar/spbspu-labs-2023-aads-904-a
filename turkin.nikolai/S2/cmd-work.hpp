#ifndef CMD_WORK_HPP
#define CMD_WORK_HPP

#include <cstddef>
#include <string>
#include <fstream>
#include <functional>
#include "dictionary.hpp"

namespace turkin
{
  template< typename K, typename V, typename C >
  void print(const std::pair< std::string, Dictionary< K, V, C > > & rhs, std::ostream & out)
  {
    auto name = rhs.first;
    auto ret = rhs.second;
    if (ret.size() == 0)
    {
      out << "<EMPTY>\n";
      return;
    }
    out << name;
    for (auto ins = ret.cbegin(); ins != ret.cend(); ins++)
    {
      out << " " << ins->first << " " << ins->second;
    }
    out << "\n";
  }

  template< typename K, typename V, typename C >
  Dictionary< K, V, C > to_complement(const Dictionary< K, V, C > & one, const Dictionary< K, V, C > & two)
  {
    Dictionary< K, V, C > result;
    if (std::addressof(one) == std::addressof(two))
    {
      return result;
    }
    for (auto ins = one.cbegin(); ins != one.cend(); ins++)
    {
      if (ins->first != two.find(ins->first)->first)
      {
        result.emplace(*ins);
      }
    }
    return result;
  }

  template< typename K, typename V, typename C >
  Dictionary< K, V, C > to_intersect(const Dictionary< K, V, C > & one, const Dictionary< K, V, C > & two)
  {
    Dictionary< K, V, C > result;
    for (auto ins = two.cbegin(); ins != two.cend(); ins++)
    {
      auto res = two.cend();
      for (auto i = one.cbegin(); i != one.cend(); i++)
      {
        if (ins->first == i->first)
        {
          res = i;
          break;
        }
      }
      if (res != two.cend())
      {
        result.emplace(*res);
      }
    }
    return result;
  }

  template< typename K, typename V, typename C >
  Dictionary< K, V, C > to_union(const Dictionary< K, V, C > & one, const Dictionary< K, V, C > & two)
  {
    Dictionary< K, V, C > result(one);
    auto ins = two.cbefore_begin();
    do
    {
      ins++;
      if (result.find(ins->first)->first != ins->first)
      {
        result.emplace(*ins);
      }
    }
    while (ins != two.cend());
    return result;
  }
}

#endif
