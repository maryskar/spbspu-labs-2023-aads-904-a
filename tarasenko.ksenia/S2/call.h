#ifndef CALL_H
#define CALL_H

#include <iostream>
#include <stdexcept>
#include <string>
#include "dictionary.h"
#include "commands.h"

namespace tarasenko
{
  std::ostream& outMessageInvalidCommand(std::ostream& out)
  {
    return out << "<INVALID COMMAND>";
  }

  std::ostream& outMessageEmpty(std::ostream& out)
  {
    return out << "<EMPTY>";
  }

  template< typename Key, typename Value, typename Compare >
  void call(const std::string& name_of_command, Dictionary< Key, Value, Compare >& dict_of_dict, std::istream& input,
            std::ostream& output)
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
      auto command = commands.printType(name_of_command);
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
      auto command = commands.createType(name_of_command);
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
