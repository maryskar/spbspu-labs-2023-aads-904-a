#ifndef COMMANDS_H
#define COMMANDS_H
#include <iostream>
#include <redblack_tree.h>
namespace romanovich
{
  using map_t = RedBlackTree< long long, std::string >;
  using map_value_t = std::pair< long long, std::string >;
  using CommandHandler = std::function< void(map_t &) >;
  using command_map_t = RedBlackTree< std::string, CommandHandler >;
  command_map_t createCommandDictionary();
}
#endif