#ifndef INPUTCOMMANDS_H
#define INPUTCOMMANDS_H

#include <iostream>
#include <string>
#include "workWithIO.h"
#include "dictionary.h"

namespace potapova
{
  template< typename Int64Comparator = std::less< long long > >
  using VariableT = Dictionary< long long, std::string, Int64Comparator >;
  template< typename Int64Comparator = std::less< long long >, typename StrComparator = std::less< std::string > >
  using VariablesT = Dictionary< std::string, VariableT< Int64Comparator >, StrComparator >;

  template< typename Int64Comparator, typename StrComparator >
  bool runCommand(const std::string& command,
      VariablesT< Int64Comparator, StrComparator >& variables)
  {
    using VariablesTConstIterator = typename VariablesT< Int64Comparator, StrComparator >::ConstIterator;

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
      using MethodType = VariableT< Int64Comparator >(VariableT< Int64Comparator >::*)(const VariableT< Int64Comparator >&) const;
      Dictionary< std::string, MethodType, StrComparator > commands;
      commands.insert("complement", &VariableT< Int64Comparator >::complement);
      commands.insert("intersect", &VariableT< Int64Comparator >::intersect);
      commands.insert("union", &VariableT< Int64Comparator >::join);
      const typename Dictionary< std::string, MethodType, StrComparator >::Iterator method_ptr = commands.find(command);
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
      const VariableT< Int64Comparator >& first_dict = first_dict_ptr->value;
      const VariableT< Int64Comparator >& second_dict = second_dict_ptr->value;
      variables[new_name] = (first_dict.*(method_ptr->value))(second_dict);
    }
    return true;
  }
}

#endif
