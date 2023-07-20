#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <string>
#include "dictionary.hpp"

using dict_t = Dictionary< size_t, std::string >;

void print(std::string name, Dictionary< std::string, dict_t >& dict_of_dict, std::ostream& out);
void unionDict(std::string name, std::string first, std::string second, Dictionary< std::string, dict_t >& dict_of_dict);

#endif
