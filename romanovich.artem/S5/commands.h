#ifndef COMMANDS_H
#define COMMANDS_H
#include <iostream>
#include "../common/redblack_tree.h"//#include <redblack_tree.h>
namespace romanovich
{
  using map_t = RedBlackTree< long long, std::string >;
  using map_value_t = std::pair< long long, std::string >;
  using CommandHandler = std::function< void(std::ostream &, map_t &) >;
  using command_map_t = RedBlackTree< std::string, CommandHandler >;
  command_map_t createCommandDictionary();
}
#endif