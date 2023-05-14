#ifndef S2_CREATE_COMMAND_DICTIONARY_HPP
#define S2_CREATE_COMMAND_DICTIONARY_HPP
#include "dictionary.hpp"

namespace chemodurov
{
  using dic_t = chemodurov::Dictionary< int, std::string >;
  using union_t = void(*)(std::istream &, Dictionary< std::string, dic_t > &);
  using print_t = void(*)(std::istream &, std::ostream & out, const Dictionary< std::string, dic_t > &);
  std::pair< Dictionary< std::string, union_t >, Dictionary< std::string, print_t > > createCommandDictionary();
}
#endif
