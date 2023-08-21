#ifndef COMMANDS_H
#define COMMANDS_H
#include <functional>
#include <iosfwd>
#include "../common/redblack_tree.h"
#include "hashtable.h"
namespace
{
  romanovich::HashTable *hashTablePtr_;
}
namespace romanovich
{
  void addWordCommand(std::istream &in, HashTable *hashTable);
  void addDictCommand(std::istream &in, HashTable &hashTable);
  using CommandHandler = std::function< void(std::istream &, std::ostream &) >;
  RedBlackTree< std::string, CommandHandler > createCommandDictionary(const HashTable *hashTable);
}
#endif
