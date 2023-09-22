#ifndef S2_COMMANDS_H
#define S2_COMMANDS_H
#include <iostream>
#include <string>
#include "Dictionary.h"
#include "ForwardList.h"

namespace chulkov {
  using Dicts = Dictionary< std::string, Dictionary< int, std::string > >;
  std::ostream& print(std::ostream&, const std::string&, const Dicts&);
  Dictionary< int, std::string > complement(const std::string&, const std::string&, const Dicts&);
  Dictionary< int, std::string > intersect(const std::string&, const std::string&, const Dicts&);
  Dictionary< int, std::string > unite(const std::string&, const std::string&, const Dicts&);
  std::ostream& printEmptyCommand(std::ostream& out);
  std::ostream& printInvalidCommand(std::ostream& out);
}

#endif
