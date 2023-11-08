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
      outEmpty(out) << '\n';
      return;
    }
    out << rhs.first;
    while (cit != dict.cend())
    {
      out << " " << cit->first << " " << cit->second;
      cit++;
    }
    out << '\n';
  }

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare > make_comp(const Dictionary< Key, Value, Compare > & first_,
    const Dictionary< Key, Value, Compare > & second_)
  {
    Dictionary< Key, Value, Compare > res;
    if (std::addressof(first_) == std::addressof(second_))
    {
      return res;
    }
    auto iter_first_begin = first_.cbegin();
    auto iter_first_end = first_.cend();
    auto iter_second_begin = second_.cbegin();
    auto iter_second_end = second_.cend();
    Compare comp = Compare{};
    while (iter_first_begin != iter_first_end && iter_second_begin != iter_second_end)
    {
      while (iter_second_begin != iter_second_end && comp((*iter_second_begin).first, (*iter_first_begin).first))
      {
        iter_second_begin++;
      }
      if (iter_second_begin == iter_second_end)
      {
        break;
      }
      if (iter_first_begin->first != iter_second_begin->first)
      {
        res.insert(*iter_first_begin);
      }
      iter_first_begin++;
    }
    while (iter_first_begin != iter_first_end)
    {
      res.insert(*iter_first_begin);
      iter_first_begin++;
    }
    return res;
  }

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare > make_intersection(const Dictionary< Key, Value, Compare > & first_,
    const Dictionary< Key, Value, Compare > & second_)
  {
    Dictionary< Key, Value, Compare > result;
    Compare comp = Compare{};
    for (auto i = second_.cbegin(); i != second_.cend(); i++)
    {
      auto res = second_.cend();
      for (auto j = first_.cbegin(); j != first_.cend(); j++)
      {
        if (!comp(i->first, j->first) && !comp(j->first, i->first))
        {
          res = j;
          break;
        }
      }
      if (res != second_.cend())
      {
        result.insert(*res);
      }
    }
    return result;
  }

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare > make_union(const Dictionary< Key, Value, Compare > & first,
    const Dictionary< Key, Value, Compare > & second)
  {
    Dictionary< Key, Value, Compare > res(first);
    auto it = second.cbegin();
    while (it != second.cend())
    {
      res.insert(*it);
      it++;
    }
    return res;
  }

}

#endif
