#ifndef S2_CREATE_COMMAND_DICTIONARY_HPP
#define S2_CREATE_COMMAND_DICTIONARY_HPP
#include "map.hpp"

namespace chemodurov
{
  using dic_t = chemodurov::Map< int, std::string >;
  using union_t = void(*)(std::istream &, Map< std::string, dic_t > &);
  using print_t = void(*)(std::istream &, std::ostream & out, const Map< std::string, dic_t > &);
  std::pair< Map< std::string, union_t >, Map< std::string, print_t > > createCommandDictionary();
  std::ostream & outEmpty(std::ostream & out);
  std::ostream & outInvalidCommand(std::ostream & out);
}
#endif
