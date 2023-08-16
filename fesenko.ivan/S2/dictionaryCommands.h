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
  }

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare > make_complementation(const Dictionary< Key, Value, Compare > &one,
      const Dictionary< Key, Value, Compare > &two)
  {
    Dictionary< Key, Value, Compare > result;
    if (std::addressof(one) == std::addressof(two)) {
      return result;
    }
    auto it_one = one.cbegin();
    auto it_two = two.cbegin();
    Compare comp = Compare{};
    while (it_one != one.cend() && it_two != two.cend()) {
      while (it_two != two.cend() && comp(it_two->first, it_one->first)) {
        it_two++;
      }
      if (it_two == two.cend()) {
        break;
      }
      if (it_one->first != it_two->first) {
        result.insert(*it_one);
      }
      it_one++;
    }
    while (it_one != one.cend()) {
      result.insert(*it_one);
      it_one++;
    }
    return result;
  }

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare > make_intersection(const Dictionary< Key, Value, Compare > &one,
      const Dictionary< Key, Value, Compare > &two)
  {
    Dictionary< Key, Value, Compare > result;
    Compare comp = Compare{};
    for (auto i = two.cbegin(); i != two.cend(); i++) {
      auto res = two.cend();
      for (auto j = one.cbegin(); j != one.cend(); j++) {
        if (!comp(i->first, j->first) && !comp(j->first, i->first)) {
          res = j;
          break;
        }
      }
      if (res != two.cend()) {
        result.insert(*res);
      }
    }
    return result;
  }

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare > make_union(const Dictionary< Key, Value, Compare > &one,
      const Dictionary< Key, Value, Compare > &two)
  {
    Dictionary< Key, Value, Compare > result(one);
    auto it = two.cbegin();
    while (it != two.cend()) {
      result.insert(*it);
      it++;
    }
    return result;
  }
}
#endif
