#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <functional>
#include <message.h>
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
     type_1(),
     type_2(),
     type_3()
   {
     type_1.push("complement", &complement< Key, Value, Compare >);
     type_1.push("intersect", &intersect< Key, Value, Compare >);
     type_1.push("union", &unionWith< Key, Value, Compare >);

     type_2.push("print", &print< Key, Value, Compare >);
     type_2.push("print_if", &printIf< Key, Value, Compare >);

     type_3.push("add", &add< std::string, dict_type, std::greater<> >);
     type_3.push("delete", &deleteDicts< Key, Value, Compare >);
     type_3.push("write", &writeDicts< Key, Value, Compare >);
     type_3.push("resort", &resort< Key, Value, Compare >);
     type_3.push("put", &put< Key, Value, Compare >);
   }

   void call(const std::string& name_of_command,
      Dictionary< std::string, dict_type, std::greater<> >& dict_of_dict,
      std::istream& input, std::ostream& output)
   {
     if (findInType1(name_of_command))
     {
       callType1(name_of_command, dict_of_dict, input, output);
     }
     else if (findInType2(name_of_command))
     {
       callType2(name_of_command, dict_of_dict, input, output);
     }
     else if (findInType3(name_of_command))
     {
       callType3(name_of_command, dict_of_dict, input, output);
     }
     else
     {
       output << outMessageInvalidCommand << "\n";
       std::string trash = " ";
       getline(input, trash);
     }
   }

  private:
   Dictionary< std::string,
     std::function< dict_type(const dict_type&, const dict_type&) >, Compare > type_1;
   Dictionary< std::string,
     std::function< std::ostream&(std::ostream&, const std::string&,
     const Dictionary< std::string, dict_type, std::greater<> >&) >, Compare > type_2;
   Dictionary< std::string,
     std::function< void(std::istream&, Dictionary< std::string, dict_type, std::greater<> >&) >, Compare > type_3;

   bool findInType1(const std::string& key) const;
   bool findInType2(const std::string& key) const;
   bool findInType3(const std::string& key) const;
   void callType1(const std::string& name_of_command,
      Dictionary< std::string, dict_type, std::greater<> >& dict_of_dict,
      std::istream& input, std::ostream& output);
   void callType2(const std::string& name_of_command,
      Dictionary< std::string, dict_type, std::greater<> >& dict_of_dict,
      std::istream& input, std::ostream& output);
   void callType3(const std::string& name_of_command,
      Dictionary< std::string, dict_type, std::greater<> >& dict_of_dict,
      std::istream& input, std::ostream& output);
  };

  template< typename Key, typename Value, typename Compare >
  bool Commands< Key, Value, Compare >::findInType1(const std::string& key) const
  {
    return type_1.find(key) != type_1.cend();
  }

  template< typename Key, typename Value, typename Compare >
  bool Commands< Key, Value, Compare >::findInType2(const std::string& key) const
  {
    return type_2.find(key) != type_2.cend();
  }

  template< typename Key, typename Value, typename Compare >
  bool Commands< Key, Value, Compare >::findInType3(const std::string& key) const
  {
    return type_3.find(key) != type_3.cend();
  }

  template< typename Key, typename Value, typename Compare >
  void Commands< Key, Value, Compare >::callType1(const std::string& name_of_command,
      Dictionary< std::string, dict_type, std::greater<> >& dict_of_dict,
      std::istream& input, std::ostream& output)
  {
    std::string name_new_dict = " ";
    std::string name_dict1 = " ";
    std::string name_dict2 = " ";
    input >> name_new_dict >> name_dict1 >> name_dict2;
    dict_type dict1;
    dict_type dict2;
    try
    {
      dict1 = dict_of_dict.at(name_dict1);
      dict2 = dict_of_dict.at(name_dict2);
    }
    catch (const std::out_of_range& e)
    {
      output << outMessageInvalidCommand << "\n";
      return;
    }
    auto new_dict = type_1.at(name_of_command)(dict1, dict2);
    dict_of_dict.push(name_new_dict, new_dict);
  }

  template< typename Key, typename Value, typename Compare >
  void Commands< Key, Value, Compare >::callType2(const std::string& name_of_command,
     Dictionary< std::string, dict_type, std::greater<> >& dict_of_dict,
     std::istream& input, std::ostream& output)
  {
    std::string key = " ";
    input >> key;
    try
    {
      type_2.at(name_of_command)(output, key, dict_of_dict);
    }
    catch (const std::out_of_range& e)
    {
      output << outMessageInvalidCommand << "\n";
    }
    catch (...)
    {
      output << outMessageEmpty << "\n";
    }
  }

  template< typename Key, typename Value, typename Compare >
  void Commands< Key, Value, Compare >::callType3(const std::string& name_of_command,
     Dictionary< std::string, dict_type, std::greater<> >& dict_of_dict,
     std::istream& input, std::ostream& output)
  {
    try
    {
      type_3.at(name_of_command)(input, dict_of_dict);
    }
    catch (const std::exception&)
    {
      output << outMessageInvalidCommand << "\n";
    }
  }
}
#endif
