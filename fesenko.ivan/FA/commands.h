#ifndef COMMANDS_H
#define COMMANDS_H
#include <iostream>
#include <functional>
#include <dictionary/forward-list/forwardList.h>
#include "hashTable.h"
namespace fesenko
{
  class Commands
  {
   public:
    using list_t = ForwardList< size_t >;
    using hash_t = HashTable< list_t >;
    using data_t = HashTable< hash_t >;
    Commands();
    void make(const std::string &command, data_t &data, std::istream &in, std::ostream &out);
   private:
    using commands1 = std::function< void(data_t &, std::istream &) >;
    using commands2 = std::function< std::ostream &(const data_t &, std::istream &, std::ostream &) >;
    HashTable< commands1 > type1;
    HashTable< commands2 > type2;
  };
}
#endif
