#ifndef INPUTCOMMANDS_H
#define INPUTCOMMANDS_H

#include <iostream>
#include <string>
#include "workWithIO.h"
#include "dictionary.h"

namespace potapova
{
  template< bool (*Int64Comp)(const long long&, const long long&)>
  using VariableT = Dictionary< long long, std::string, Int64Comp >;
  template< bool (*Int64Comp)(const long long&, const long long&),
      bool (*StringComp)(const std::string& first, const std::string& second) >
  using VariablesT = Dictionary< std::string, VariableT< Int64Comp >, StringComp >;

  template< bool (*Int64Comp)(const long long&, const long long&),
      bool (*StringComp)(const std::string& first, const std::string& second) >
  bool runCommand(const std::string& command,
      VariablesT< Int64Comp, StringComp >& variables)
  {
    using VariablesTConstIterator = typename VariablesT< Int64Comp, StringComp >::ConstIterator;
    
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
      using MethodType = VariableT< Int64Comp >(VariableT< Int64Comp >::*)(const VariableT< Int64Comp >&) const;
      Dictionary< std::string, MethodType, StringComp > commands;
      commands.insert("complement", &VariableT< Int64Comp >::complement);
      commands.insert("intersect", &VariableT< Int64Comp >::intersect);
      commands.insert("union", &VariableT< Int64Comp >::join);
      const typename Dictionary< std::string, MethodType, StringComp >::Iterator method_ptr = commands.find(command);
      if (method_ptr == commands.end())
      {
        return false;
      }
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
      const VariableT< Int64Comp >& first_dict = first_dict_ptr->value;
      const VariableT< Int64Comp >& second_dict = second_dict_ptr->value;
      variables[new_name] = (first_dict.*(method_ptr->value))(second_dict);
    }
    return true;
  }
}

#endif
