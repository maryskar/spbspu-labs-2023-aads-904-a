#ifndef DICTIONARIESVAULT_H
#define DICTIONARIESVAULT_H
#include <vector>
#include <string>
#include "hashtable.h"
namespace romanovich
{
  class DictionariesVault
  {
  public:
    using value_t = std::vector< std::pair< std::string, HashTable>>;
    DictionariesVault &operator=(DictionariesVault &&) = delete;
    static DictionariesVault::value_t *instance();
  };
}
#endif
