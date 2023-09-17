#include "dictionariesvault.h"
DictionariesVault *DictionariesVault::instance()
{
  static DictionariesVault* ptrVault_ = nullptr;
  if (!ptrVault_)
  {
    ptrVault_ = new DictionariesVault();
  }
  return ptrVault_;
}
