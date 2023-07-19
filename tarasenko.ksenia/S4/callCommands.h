#ifndef S4_CALLCOMMANDS_H
#define S4_CALLCOMMANDS_H

#include <iostream>
#include <stdexcept>
#include <string>
#include "map.h"
#include "commands.h"
#include <message.h>

namespace tarasenko
{
  template< typename Key, typename Value, typename Compare >
  void call(const std::string& name_of_command, Map< Key, Value, Compare >& dict_of_dict,
     std::istream& input, std::ostream& output)
  {
    tarasenko::Commands< size_t, std::string, std::less<> > commands;
    if (commands.findInTypePrint(name_of_command))
    {
      std::string name_of_dict = "";
      input >> name_of_dict;
      Value given_dict;
      try
      {
        given_dict = dict_of_dict.at(name_of_dict);
      }
      catch (const std::out_of_range& e)
      {
        output << outMessageInvalidCommand << "\n";
        return;
      }
      if (given_dict.isEmpty())
      {
        output << outMessageEmpty << "\n";
        return;
      }
      std::function< std::ostream&(std::ostream&, const std::string&, const Value&) > command;
      commands.get(name_of_command, command);
      command(output, name_of_dict, given_dict);
      output << "\n";
    }
    else if (commands.findInTypeCreate(name_of_command))
    {
      std::string name_new_dict = "";
      std::string name_dict1 = "";
      std::string name_dict2 = "";
      input >> name_new_dict >> name_dict1 >> name_dict2;
      Value dict1;
      Value dict2;
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
      std::function< Value(const Value&, const Value&) > command;
      commands.get(name_of_command, command);
      auto new_dict = command(dict1, dict2);
      dict_of_dict.push(name_new_dict, new_dict);
    }
    else
    {
      output << outMessageInvalidCommand << "\n";
      std::string trash = "";
      getline(input, trash);
    }
  }
}

#endif
