#ifndef COMMANDS_H
#define COMMANDS_H
#include <unordered_map>
#include <iomanip>
#include "dict.h"
namespace romanovich
{
  using dict_type = Dictionary< int, std::string >;
  using dict_value_type = std::pair< int, std::string >;
  using container_type = Dictionary< std::string, dict_type >;
  using container_value_type = std::pair< std::string, dict_type >;
  using CommandHandler = std::function< void(std::istream &, std::ostream &, container_type &) >;
  void printCommand(std::istream &in, std::ostream &out, container_type &dictionary);
  void performCommand(std::istream &in, std::ostream &out, container_type &dictionary,
                      const std::function< void(dict_type &, const dict_type &, const dict_type &) > &operation);
  std::unordered_map< std::string, CommandHandler > createCommandDictionary(container_type &dictionary);
}
#endif
