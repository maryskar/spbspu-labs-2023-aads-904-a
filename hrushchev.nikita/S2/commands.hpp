#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <string>
#include "dictionary.hpp"

using dict_t = Dictionary< size_t, std::string >;

void print(std::string name, Dictionary< std::string, dict_t >& dict_of_dict, std::ostream& out);

#endif
