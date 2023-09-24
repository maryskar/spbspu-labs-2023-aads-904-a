#include "commands.h"
#include <iostream>
#include <stdexcept>

std::ostream& skarlygina::print(std::ostream& out, const std::string& name, const Dictis& dictis)
{
  auto it = dictis.cfind(name);
  if (it == dictis.cend())
    throw std::invalid_argument("Unknown dictionary");
  if (it->second.is_empty())
  {
    return out << "<EMPTY>" << std::endl;
  }
  out << name;
  for (auto&& data : it->second)
    out << ' ' << data.first << ' ' << data.second;
  out << std::endl;
  return out;
}
skarlygina::Dictionary< int, std::string > skarlygina::complement(const std::string&, const std::string&, const Dictis&);
skarlygina::Dictionary< int, std::string > skarlygina::intersect(const std::string&, const std::string&, const Dictis&);
skarlygina::Dictionary< int, std::string > skarlygina::unite(const std::string&, const std::string&, const Dictis&);
