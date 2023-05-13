#ifndef S2_CREATE_COMMAND_DICTIONARY_HPP
#define S2_CREATE_COMMAND_DICTIONARY_HPP
#include "dictionary.hpp"

namespace chemodurov
{
  using dic_t = chemodurov::Dictionary< int, std::string >;
  using command_t = void(*)(std::istream &, std::ostream &, Dictionary< std::string, dic_t > &);
  Dictionary< std::string, command_t > createCommandDictionary();
}
#endif
