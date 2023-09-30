#include "dictionariesvault.h"
romanovich::DictionariesVault::value_t *romanovich::DictionariesVault::instance()
{
  static value_t *ptrVault_ = nullptr;
  if (!ptrVault_)
  {
    ptrVault_ = new DictionariesVault::value_t;
  }
  return ptrVault_;
}
