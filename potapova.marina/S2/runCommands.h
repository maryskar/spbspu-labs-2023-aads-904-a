#ifndef INPUTCOMMANDS_H
#define INPUTCOMMANDS_H

#include <istream>
#include <ostream>
#include <string>
#include "workWithIO.h"
#include "dictionary.h"

namespace potapova
{
  template< typename Comparator = std::less< long long > >
  using VariableT = Dictionary< long long, std::string, Comparator >;
  template< typename Int64Comparator = std::less< long long >, typename StrComparator = std::less< std::string > >
  using VariablesT = Dictionary< std::string, VariableT< Int64Comparator >, StrComparator >;
  template< typename VarComparator = std::less< long long > >
  using CommandT = VariableT< VarComparator >(VariableT< VarComparator >::*)(const VariableT< VarComparator >&) const;
  template< typename VarComparator = std::less< long long > >
  using CommandsT = Dictionary< std::string, CommandT< VarComparator > >;

  template< typename VarComparator = std::less< long long > >
  CommandsT< VarComparator > getCommands()
  {
    CommandsT< VarComparator > commands;
    commands.insert("complement", &VariableT< VarComparator >::complement);
    commands.insert("intersect", &VariableT< VarComparator >::intersect);
    commands.insert("union", &VariableT< VarComparator >::join);
    return commands;
  }

  template< typename Int64Comparator, typename StrComparator >
  bool runCommand(std::istream& in,
    std::ostream& out,
    const std::string& command,
    VariablesT< Int64Comparator, StrComparator >& variables,
    const CommandsT< Int64Comparator >& commands)
  {
    using VariablesTConstIterator = typename VariablesT< Int64Comparator, StrComparator >::ConstIterator;
    
    if (command == "print")
    {
      std::string name;
      in >> name;
      const VariablesTConstIterator dict_ptr = variables.find(name);
      if (dict_ptr == variables.cend())
      {
        return false;
      }
      if (!dict_ptr->second.empty())
      {
        out << name << ' ';
      }
      printDict(out, dict_ptr->second);
    }
    else
    {
      typename CommandsT< Int64Comparator >::ConstIterator command_ptr = commands.find(command);
      if (command_ptr == commands.end())
      {
        return false;
      }
      std::string new_name;
      std::string first_name;
      std::string second_name;
      in >> new_name >> first_name >> second_name;
      const VariablesTConstIterator first_dict_ptr = variables.find(first_name);
      const VariablesTConstIterator second_dict_ptr = variables.find(second_name);
      if (first_dict_ptr == variables.cend() || second_dict_ptr == variables.cend())
      {
        return false;
      }
      const VariableT< Int64Comparator >& first_dict = first_dict_ptr->second;
      const VariableT< Int64Comparator >& second_dict = second_dict_ptr->second;
      variables[new_name] = (first_dict.*(command_ptr->second))(second_dict);
    }
    return true;
  }
}

#endif
