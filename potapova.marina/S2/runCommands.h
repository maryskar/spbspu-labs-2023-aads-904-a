#ifndef INPUTCOMMANDS_H
#define INPUTCOMMANDS_H

#include <iostream>
#include <string>
#include "workWithIO.h"
#include "dictionary.h"

namespace potapova
{
  template< bool (*compareLongLong)(const long long&, const long long&) >
  using VariableT = Dictionary< long long, std::string, compareLongLong >;
  template< bool (*compareLongLong)(const long long&, const long long&),
      bool (*compareString)(const std::string& first, const std::string& second) >
  using VariablesT = Dictionary< std::string, VariableT< compareLongLong >, compareString >;

  template< bool (*compareLongLong)(const long long&, const long long&),
      bool (*compareString)(const std::string& first, const std::string& second) >
  bool runCommand(const std::string& command,
      VariablesT< compareLongLong, compareString >& variables)
  {
    using VariablesTConstIterator = typename VariablesT< compareLongLong, compareString >::ConstIterator;
    if (command == "print")
    {
      std::string name;
      std::cin >> name;
      const VariablesTConstIterator dict_ptr = variables.find(name);
      if (dict_ptr == variables.cend())
      {
        return false;
      }
      if (!dict_ptr->value.empty())
      {
        std::cout << name << ' ';
      }
      std::cout << dict_ptr->value;
    }
    else
    {
      std::string new_name;
      std::string first_name;
      std::string second_name;
      std::cin >> new_name >> first_name >> second_name;
      const VariablesTConstIterator first_dict_ptr = variables.find(first_name);
      const VariablesTConstIterator second_dict_ptr = variables.find(second_name);
      if (first_dict_ptr == variables.cend() || second_dict_ptr == variables.cend())
      {
        return false;
      }
      const VariableT< compareLongLong >& first_dict = first_dict_ptr->value;
      const VariableT< compareLongLong >& second_dict = second_dict_ptr->value;
      if (command == "complement")
      {
        variables[new_name] = first_dict.complement(second_dict);
      }
      else if (command == "intersect")
      {
        variables[new_name] = first_dict.intersect(second_dict);
      }
      else if (command == "union")
      {
        variables[new_name] = first_dict.join(second_dict);
      }
    }
    return true;
  }
}

#endif
