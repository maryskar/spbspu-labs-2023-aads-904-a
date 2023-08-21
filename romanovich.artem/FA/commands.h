#ifndef COMMANDS_H
#define COMMANDS_H
#include <functional>
#include <iosfwd>
#include "../common/redblack_tree.h"
#include "hashtable.h"
namespace romanovich
{
  void addWordCommand(std::istream &in, HashTable &hashTable);
  void addDictCommand(std::istream &in, HashTable &hashTable);
  using CommandHandler = std::function< void(std::istream &, std::ostream &, HashTable &) >;
  RedBlackTree< std::string, CommandHandler > createCommandDictionary(HashTable &hashTable);
}
#endif
