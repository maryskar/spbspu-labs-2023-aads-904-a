#include "commands.hpp"
#include <string>
#include <ostream>
#include "dictionary.hpp"

using dict_t = Dictionary< size_t, std::string >;

void print(std::string name, Dictionary< std::string, dict_t >& dict_of_dict, std::ostream& out)
{
  out << name << " ";
  dict_t dict = dict_of_dict.get(name);
  for (auto i = dict.begin(); i != dict.end(); i++)
  {
    out << i->first << " " << i->second << " ";
  }
}
