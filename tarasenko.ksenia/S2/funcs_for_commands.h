#ifndef FUNCS_FOR_COMMANDS_H
#define FUNCS_FOR_COMMANDS_H

#include <iostream>
#include <string>
#include <functional>
#include "dictionary.h"

namespace tarasenko
{
  template< class Key, class Value, class Compare >
  Dictionary<Key, Value, Compare > complement(const Dictionary<Key, Value, Compare >& lhs,
      const Dictionary<Key, Value, Compare >& rhs)
  {
    auto result = lhs;
    if (!lhs.isEmpty() && !rhs.isEmpty())
    {
      auto iter_lhs = lhs.cbegin();
      for (; iter_lhs != lhs.cend(); iter_lhs++)
      {
        if (rhs.find((*iter_lhs).first) != lhs.cend())
        {
          result.remove((*iter_lhs).first);
        }
      }
    }
    return result;
  }

  template< class Key, class Value, class Compare >
  Dictionary<Key, Value, Compare > intersect(const Dictionary<Key, Value, Compare >& lhs,
      const Dictionary<Key, Value, Compare >& rhs)
  {
    if (rhs.isEmpty())
    {
      return rhs;
    }
    Dictionary<Key, Value, Compare > result;
    if (!lhs.isEmpty())
    {
      auto iter_lhs = lhs.cbegin();
      for (; iter_lhs != lhs.cend(); iter_lhs++)
      {
        if (rhs.find((*iter_lhs).first) != rhs.cend())
        {
          result.push((*iter_lhs).first, (*iter_lhs).second);
        }
      }
    }
    return result;
  }

  template< class Key, class Value, class Compare >
  Dictionary<Key, Value, Compare > unionWith(const Dictionary<Key, Value, Compare >& lhs,
      const Dictionary<Key, Value, Compare >& rhs)
  {
    if (lhs.isEmpty())
    {
      return rhs;
    }
    auto result = lhs;
    if (!rhs.isEmpty())
    {
      auto iter_rhs = rhs.cbegin();
      for (; iter_rhs != rhs.cend(); iter_rhs++)
      {
        if (lhs.find((*iter_rhs).first) == lhs.cend())
        {
          result.push((*iter_rhs).first, (*iter_rhs).second);
        }
      }
    }
    return result;
  }

  template< class Key, class Value, class Compare >
  std::ostream& print(std::ostream& output, const Dictionary<Key, Value, Compare >& dict)
  {
    if (!dict.isEmpty())
    {
      auto iter = dict.cbegin();
      output << iter->first << " " << iter->second;
      ++iter;
      while (iter != dict.cend())
      {
        output << " " << iter->first << " " << iter->second;
        ++iter;
      }
    }
    return output;
  }
}
#endif
