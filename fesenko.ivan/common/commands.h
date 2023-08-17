#ifndef DICTIONARYCOMMANDS_H
#define DICTIONARYCOMMANDS_H
#include <fstream>
#include <string>
#include "messages.h"

namespace fesenko
{
  template< typename Storage >
  void print(const std::pair< std::string, Storage > &rhs, std::ostream &out)
  {
    auto container = rhs.second;
    auto cit = container.cbegin();
    if (cit == container.cend()) {
      outEmptyMessage(out);
      return;
    }
    out << rhs.first;
    while (cit != container.cend()) {
      out << " " << cit->first << " " << cit->second;
      cit++;
    }
  }

  template< typename Storage >
  Storage make_complementation(const Storage &one, const Storage &two)
  {
    Storage result;
    if (std::addressof(one) == std::addressof(two)) {
      return result;
    }
    auto it_one = one.cbegin();
    auto it_two = two.cbegin();
    auto comp = std::less<>();
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

  template< typename Storage >
  Storage make_intersection(const Storage &one, const Storage &two)
  {
    Storage result;
    auto comp = std::less<>();
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

  template< typename Storage >
  Storage make_union(const Storage &one, const Storage &two)
  {
    Storage result(one);
    auto it = two.cbegin();
    while (it != two.cend()) {
      result.insert(*it);
      it++;
    }
    return result;
  }
}
#endif
