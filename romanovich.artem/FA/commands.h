#ifndef COMMANDS_H
#define COMMANDS_H
#include <functional>
#include <iosfwd>
#include "../common/redblack_tree.h"
#include "hashtable.h"
namespace romanovich
{
  using CommandHandler = std::function< void(std::istream &, std::ostream &, HashTable &) >;
  void addWordCommand(std::istream &in, std::ostream &out, HashTable &hashTable);
  RedBlackTree< std::string, CommandHandler > createCommandDictionary(HashTable &hashTable);
}
#endif
