#ifndef COMMANDS_H
#define COMMANDS_H
#include <string>
#include <iostream>
#include <stdexcept>
#include "printMessages.h"

namespace chulkov
{
  template < typename AllDicts >
  std::ostream& print(std::ostream& out, const std::string& name, const AllDicts& dicts)
  {
    auto it = dicts.cfind(name);
    if (it == dicts.cend())
    {
      throw std::invalid_argument("Unknown dictionary");
    }
    if (it->second.isEmpty())
    {
      printEmpty(out);
      return out;
    }
    out << name;
    for (auto && data: it->second)
    {
      out << ' ' << data.first << ' ' << data.second;
    }
    out << std::endl;
    return out;
  }
  template < typename Dict, typename AllDicts >
  Dict complement(const std::string& lhsName, const std::string& rhsName, const AllDicts& dicts)
  {
    auto lhsCIt = dicts.cfind(lhsName);
    auto rhsCIt = dicts.cfind(rhsName);
    if ((lhsCIt == dicts.cend()) || (rhsCIt == dicts.cend()))
    {
      throw std::invalid_argument("Unknown dictionary");
    }
    if (lhsCIt->second.isEmpty() || rhsCIt->second.isEmpty())
    {
      return lhsCIt->second;
    }
    auto returnable = lhsCIt->second;
    auto rhsIt = rhsCIt->second.cbegin();
    auto retIt = returnable.begin();
    std::less< int > cmp;
    while ((retIt != returnable.end()) && (rhsIt != rhsCIt->second.cend()))
    {
      if (cmp(retIt->first, rhsIt->first))
      {
        while ((retIt != returnable.end()) && cmp(retIt->first, rhsIt->first))
        {
          ++retIt;
        }
      }
      else if (cmp(rhsIt->first, retIt->first))
      {
        while ((rhsIt != rhsCIt->second.cend()) && cmp(rhsIt->first, retIt->first))
        {
          ++rhsIt;
        }
      }
      if ((retIt == returnable.end()) || (rhsIt == rhsCIt->second.cend()))
      {
        return returnable;
      }
      if (!cmp(retIt->first, rhsIt->first) && !cmp(rhsIt->first, retIt->first))
      {
        ++retIt;
        returnable.pop(rhsIt->first);
        ++rhsIt;
      }
      else
      {
        ++retIt;
        ++rhsIt;
      }
    }
    return returnable;
  }
  template < typename Dict, typename AllDicts >
  Dict intersect(const std::string& lhsName, const std::string& rhsName, const AllDicts& dicts)
  {
    auto lhsCIt = dicts.cfind(lhsName);
    auto rhsCIt = dicts.cfind(rhsName);
    if ((lhsCIt == dicts.cend()) || (rhsCIt == dicts.cend()))
    {
      throw std::invalid_argument("Unknown dictionary");
    }
    if ((lhsCIt->second.isEmpty()) || (rhsCIt->second.isEmpty()))
    {
      return Dict();
    }
    auto returnable = Dict();
    auto lhsIt = lhsCIt->second.cbegin();
    auto rhsIt = rhsCIt->second.cbegin();
    std::less< int > cmp;
    while ((lhsIt != lhsCIt->second.cend()) && (rhsIt != rhsCIt->second.cend()))
    {
      if (cmp(lhsIt->first, rhsIt->first))
      {
        while ((lhsIt != lhsCIt->second.cend()) && cmp(lhsIt->first, rhsIt->first))
        {
          ++lhsIt;
        }
      }
      else if (cmp(rhsIt->first, lhsIt->first))
      {
        while ((rhsIt != rhsCIt->second.cend()) && cmp(rhsIt->first, lhsIt->first))
        {
          ++rhsIt;
        }
      }
      if ((lhsIt == lhsCIt->second.cend()) || (rhsIt == rhsCIt->second.cend()))
      {
        return returnable;
      }
      if (!cmp(lhsIt->first, rhsIt->first) && !cmp(rhsIt->first, lhsIt->first))
      {
        returnable.push(lhsIt->first, lhsIt->second);
      }
      ++lhsIt;
      ++rhsIt;
    }
    return returnable;
  }
  template < typename Dict, typename AllDicts >
  Dict unite(const std::string& lhsName, const std::string& rhsName, const AllDicts& dicts)
  {
    auto lhsCIt = dicts.cfind(lhsName);
    auto rhsCIt = dicts.cfind(rhsName);
    if ((lhsCIt == dicts.cend()) || (rhsCIt == dicts.cend()))
    {
      throw std::invalid_argument("Unknown dictionary");
    }
    if (lhsCIt->second.isEmpty())
    {
      return rhsCIt->second;
    }
    if (rhsCIt->second.isEmpty())
    {
      return lhsCIt->second;
    }
    auto returnable = lhsCIt->second;
    auto rhsIt = rhsCIt->second.cbegin();
    while (rhsIt != rhsCIt->second.cend())
    {
      if (returnable.cfind(rhsIt->first) == returnable.cend())
      {
        returnable.push(rhsIt->first, rhsIt->second);
      }
      ++rhsIt;
    }
    return returnable;
  }
}

#endif
