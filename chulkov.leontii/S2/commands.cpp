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
}
