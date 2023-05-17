#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <functional>
#include "dictionary.h"
#include "funcs_for_commands.h"

namespace tarasenko
{
  template< typename Key, typename Value, typename Compare >
  class Commands
  {
   using dict_type = Dictionary< Key, Value, Compare >;
  public:
   Commands():
     type_create(),
     type_print()
   {
     type_create.push("complement", &complement< Key, Value, Compare >);
     type_create.push("intersect", &intersect< Key, Value, Compare >);
     type_create.push("union", &unionWith< Key, Value, Compare >);

     type_print.push("print", &print< Key, Value, Compare >);
   }

   std::function< std::ostream&(std::ostream&, std::string, const dict_type&) >& printType(const std::string& key)
   {
     return type_print.at(key);
   }

   std::function< dict_type(const dict_type&, const dict_type&) >& createType(const std::string& key)
   {
     return type_create.at(key);
   }

   bool findInTypePrint(std::string name_of_command)
   {
     return type_print.find(name_of_command) != type_print.cend();
   }

   bool findInTypeCreate(std::string name_of_command)
   {
     return type_create.find(name_of_command) != type_create.cend();
   }

  private:
   Dictionary< std::string,
     std::function< dict_type(const dict_type&, const dict_type&) >, Compare > type_create;
   Dictionary< std::string,
     std::function< std::ostream&(std::ostream&, std::string, const dict_type&) >, Compare > type_print;
  };
}
#endif
