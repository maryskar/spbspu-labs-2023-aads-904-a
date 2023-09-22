#include "commands.h"
#include <iostream>
#include <stdexcept>

namespace chulkov {
  std::string MESSAGE = "Unknown dictionary";

  std::ostream& printEmptyCommand(std::ostream& out)
  {
    return out << "<EMPTY>" << std::endl;
  }

  std::ostream& print(std::ostream& out, const std::string& name, const Dicts& dicts)
  {
    auto it = dicts.cfind(name);
    if (it == dicts.cend()) {
      throw std::invalid_argument(MESSAGE);
    }
    if (it->second.isEmpty()) {
      printEmptyCommand(out);
      return out;
    }
    out << name;
    for (std::pair< int, std::string >& data : it->second) {
      out << ' ' << data.first << ' ' << data.second;
    }
    out << std::endl;
    return out;
  }

  Dictionary< int, std::string > complement(const std::string& lhs, const std::string& rhs, const Dicts& dicts)
  {
    auto lhsCIterator = dicts.cfind(lhs);
    auto rhsCIterator = dicts.cfind(rhs);
    if ((lhsCIterator == dicts.cend()) || (rhsCIterator == dicts.cend())) {
      throw std::invalid_argument(MESSAGE);
    }
    if (lhsCIterator->second.isEmpty() || rhsCIterator->second.isEmpty()) {
      return lhsCIterator->second;
    }
    auto returnable = lhsCIterator->second;
    auto rhsIterator = rhsCIterator->second.cbegin();
    auto retIterator = returnable.begin();
    std::less< int > cmp;
    while ((retIterator != returnable.end()) && (rhsIterator != rhsCIterator->second.cend())) {
      if (cmp(retIterator->first, rhsIterator->first)) {
        while ((retIterator != returnable.end()) && cmp(retIterator->first, rhsIterator->first)) {
          ++retIterator;
        }
      } else if (cmp(rhsIterator->first, retIterator->first)) {
        while ((rhsIterator != rhsCIterator->second.cend()) && cmp(rhsIterator->first, retIterator->first)) {
          ++rhsIterator;
        }
      }
      if ((retIterator == returnable.end()) || (rhsIterator == rhsCIterator->second.cend())) {
        return returnable;
      }
      if (!cmp(retIterator->first, rhsIterator->first) && !cmp(rhsIterator->first, retIterator->first)) {
        ++retIterator;
        returnable.pop(rhsIterator->first);
        ++rhsIterator;
      } else {
        ++retIterator;
        ++rhsIterator;
      }
    }
    return returnable;
  }
}
