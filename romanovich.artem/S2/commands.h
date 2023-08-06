#ifndef COMMANDS_H
#define COMMANDS_H
#include <unordered_map>
#include <iomanip>
#include "dict.h"
namespace romanovich
{
  using dict_t = Dictionary< int, std::string >;
  using dict_value_t = std::pair< int, std::string >;
  using container_t = Dictionary< std::string, dict_t >;
  using container_value_t = std::pair< std::string, dict_t >;
  using CommandHandler = std::function< void(std::istream &, std::ostream &, container_t &) >;
  void printCommand(std::istream &in, std::ostream &out, container_t &dictionary);
  void performCommand(std::istream &in, std::ostream &out, container_t &dictionary,
                      const std::function< void(dict_t &, const dict_t &, const dict_t &) > &operation);
  std::unordered_map< std::string, CommandHandler > createCommandDictionary(container_t &dictionary);
}
#endif
