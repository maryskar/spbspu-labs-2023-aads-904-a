#ifndef COMMANDS_H
#define COMMANDS_H
#include <functional>
#include <iosfwd>
#include <memory>
#include "../common/redblack_tree.h"
#include "hashtable.h"
namespace
{
  romanovich::HashTable *hashTablePtr_;
  std::shared_ptr< std::vector< std::pair< std::string, romanovich::HashTable > > > langDicts_;
}
namespace romanovich
{
  void addWordCommand(std::istream &in);
  void addDictCommand(std::istream &in);
  using CommandHandler = std::function< void(std::istream &, std::ostream &) >;
  RedBlackTree< std::string, CommandHandler > createCommandDictionary(const HashTable *hashTable);
}
#endif
