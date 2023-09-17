#ifndef DICTIONARIESVAULT_H
#define DICTIONARIESVAULT_H
class DictionariesVault
{
public:
  DictionariesVault& operator=(DictionariesVault &&) = delete;
  static DictionariesVault* instance();
};
#endif
