#ifndef S4_COMMANDS_H
#define S4_COMMANDS_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <functional>
#include <message.h>
#include "map.h"
#include "funcsForCommands.h"

namespace tarasenko
{
  std::istream& readTrash(std::istream& input)
  {
    input.clear();
    std::string trash = " ";
    getline(input, trash);
    return input;
  }

  template< typename Key, typename Value, typename Compare >
  class Commands
  {
   using dict_type = Map< Key, Value, Compare >;
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

   void call(const std::string& name_of_command,
      Map< std::string, dict_type, std::greater<> >& dict_of_dict,
      std::istream& input, std::ostream& output)
   {
     try
     {
       if (findInTypePrint(name_of_command))
       {
         callPrint(name_of_command, dict_of_dict, input, output);
       }
       else if (findInTypeCreate(name_of_command))
       {
         callCreate(name_of_command, dict_of_dict, input);
       }
       else
       {
         throw std::out_of_range("Invalid command");
       }
     }
     catch (const std::out_of_range& e)
     {
       output << outMessageInvalidCommand << "\n";
       readTrash(input);
     }
     catch (const std::invalid_argument& e)
     {
       output << outMessageEmpty << "\n";
       readTrash(input);
     }
   }

  private:
   Map< std::string, std::function< dict_type(const dict_type&, const dict_type&) >, Compare > type_create;
   Map< std::string,
      std::function< std::ostream&(std::ostream&, const std::string&, const dict_type&) >, Compare > type_print;

   bool findInTypePrint(const std::string& key) const;
   bool findInTypeCreate(const std::string& key) const;
   void callCreate(const std::string& name_of_command,
      Map< std::string, dict_type, std::greater<> >& dict_of_dict, std::istream& input);
   void callPrint(const std::string& name_of_command,
      Map< std::string, dict_type, std::greater<> >& dict_of_dict,
      std::istream& input, std::ostream& output);
  };

  template< typename Key, typename Value, typename Compare >
  bool Commands< Key, Value, Compare >::findInTypePrint(const std::string& key) const
  {
    return type_print.find(key) != type_print.cend();
  }

  template< typename Key, typename Value, typename Compare >
  bool Commands< Key, Value, Compare >::findInTypeCreate(const std::string& key) const
  {
    return type_create.find(key) != type_create.cend();
  }

  template< typename Key, typename Value, typename Compare >
  void Commands< Key, Value, Compare >::callCreate(const std::string& name_of_command,
     Map< std::string, dict_type, std::greater<> >& dict_of_dict, std::istream& input)
  {
    std::string name_new_dict = " ";
    std::string name_dict1 = " ";
    std::string name_dict2 = " ";
    input >> name_new_dict >> name_dict1 >> name_dict2;
    dict_type dict1 = dict_of_dict.at(name_dict1);
    dict_type dict2 = dict_of_dict.at(name_dict2);
    auto new_dict = type_create.at(name_of_command)(dict1, dict2);
    dict_of_dict.push(name_new_dict, new_dict);
  }

  template< typename Key, typename Value, typename Compare >
  void Commands< Key, Value, Compare >::callPrint(const std::string& name_of_command,
     Map< std::string, dict_type, std::greater<> >& dict_of_dict,
     std::istream& input, std::ostream& output)
  {
    std::string name_of_dict = " ";
    input >> name_of_dict;
    dict_type given_dict;
    given_dict = dict_of_dict.at(name_of_dict);
    if (given_dict.isEmpty())
    {
      throw std::invalid_argument("Empty");
    }
    type_print.at(name_of_command)(output, name_of_dict, given_dict);
    output << "\n";
  }
}
#endif
