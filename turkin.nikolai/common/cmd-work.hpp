#ifndef CMD_WORK_HPP
#define CMD_WORK_HPP

#include <fstream>
#include <functional>
#include <out-msg.hpp>
#include <comparator.hpp>

namespace turkin
{
  template< class Storage >
  void print(const std::pair< std::string, Storage > & rhs, std::ostream & out)
  {
    auto name = rhs.first;
    auto ret = rhs.second;
    if (ret.empty())
    {
      outEmptyCMD(out);
      return;
    }
    out << name;
    for (auto ins: ret)
    {
      out << " " << ins.first << " " << ins.second;
    }
    out << "\n";
  }

  template< class Storage, typename C >
  Storage to_complement(const Storage & one, const Storage & two)
  {
    Storage result;
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
        result.insert(*iter_first);
      }
      iter_first++;
    }
    while (iter_first != iter_first_end)
    {
      result.insert(*iter_first);
      iter_first++;
    }
    return result;
  }

  template< class Storage >
  Storage to_intersect(const Storage & one, const Storage & two)
  {
    Storage result;
    for (auto ins: two)
    {
      auto res = *two.cend();
      for (auto i: one)
      {
        if (ins.first == i.first)
        {
          res = i;
          break;
        }
      }
      if (res != *two.cend())
      {
        result.insert(res);
      }
    }
    return result;
  }

  template< class Storage >
  Storage to_union(const Storage & one, const Storage & two)
  {
    Storage result(one);
    for (auto ins: two)
    {
      if (result.find(ins.first)->first != ins.first)
      {
        result.insert(ins);
      }
    }
    return result;
  }
}

#endif
