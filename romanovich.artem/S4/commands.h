#ifndef COMMANDS_H
#define COMMANDS_H
#include <unordered_map>
#include <iomanip>
#include <redblack_tree.h>
namespace romanovich
{
  using map_t = RedBlackTree< int, std::string >;
  using map_value_t = std::pair< int, std::string >;
  using container_t = RedBlackTree< std::string, map_t >;
  using container_value_t = std::pair< std::string, map_t >;
  using CommandHandler = std::function< void(std::istream &, std::ostream &, container_t &) >;
  void printCommand(std::istream &in, std::ostream &out, container_t &map);
  void performCommand(std::istream &in,
      std::ostream &out,
      container_t &map, const std::function< void(map_t &, const map_t &, const map_t &) > &operation);
  std::unordered_map< std::string, CommandHandler > createCommandDictionary(container_t &map);
}
#endif
