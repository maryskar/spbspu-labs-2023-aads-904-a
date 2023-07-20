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

   void get(const std::string& key, std::function< std::ostream&(std::ostream&,
        const std::string&, const dict_type&) >& command)
   {
     try
     {
       command = type_print.at(key);
     }
     catch (const std::out_of_range&)
     {
       throw std::out_of_range("Not found");
     }
   }

   void get(const std::string& key, std::function< dict_type(const dict_type&, const dict_type&) >& command)
   {
     try
     {
       command = type_create.at(key);
     }
     catch (const std::out_of_range&)
     {
       throw std::out_of_range("Not found");
     }
   }

   bool findInTypePrint(const std::string& key) const
   {
     return type_print.find(key) != type_print.cend();
   }

   bool findInTypeCreate(const std::string& key) const
   {
     return type_create.find(key) != type_create.cend();
   }

  private:
   Dictionary< std::string,
     std::function< dict_type(const dict_type&, const dict_type&) >, Compare > type_create;
   Dictionary< std::string,
     std::function< std::ostream&(std::ostream&, const std::string&, const dict_type&) >, Compare > type_print;
  };
}
#endif
