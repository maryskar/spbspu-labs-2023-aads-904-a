#ifndef COMMANDS_H
#define COMMANDS_H
#include <iostream>
#include "../common/redblack_tree.h"
namespace romanovich
{
  using map_t = RedBlackTree< int, std::string >;
  using map_value_t = std::pair< int, std::string >;
  using CommandHandler = std::function< void(std::ostream &, map_t &) >;
  using command_map_t = RedBlackTree< std::string, CommandHandler >;
  void performCommand(std::ostream &out, map_t &map, const CommandHandler &operation);
  command_map_t createCommandDictionary();
}
#endif