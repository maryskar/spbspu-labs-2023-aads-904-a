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
    auto iter_first = one.cbegin();
    auto iter_first_end = one.cend();
    auto iter_second = two.cbegin();
    auto iter_second_end = two.cend();
    C comp = C{};
    while (iter_first != iter_first_end && iter_second != iter_second_end)
    {
      while (iter_second != iter_second_end && comp(iter_second->first, iter_first->first))
      {
        iter_second++;
      }
      if (iter_second == iter_second_end)
      {
        break;
      }
      if (iter_first->first != iter_second->first)
      {
        result.emplace(*iter_first);
      }
      iter_first++;
    }
    while (iter_first != iter_first_end)
    {
      result.emplace(*iter_first);
      iter_first++;
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
