#ifndef INPUTCOMMANDS_H
#define INPUTCOMMANDS_H

#include <iostream>
#include <string>
#include "workWithIO.h"
#include "dictionary.h"

namespace potapova
{
  template< bool (*compareFunc)(const long long&, const long long&),
      bool (*compareDict)(const std::string& first, const std::string& second) >
  void runCommand(const std::string& command,
      Dictionary< std::string, Dictionary< long long, std::string, compareFunc >, compareDict >& variables)
  {
    if (command == "print")
    {
      std::string name;
      std::cin >> name;
      Dictionary< long long, std::string, compareFunc > dict = variables[name];
      if (!dict.empty())
      {
        std::cout << name << " ";
      }
      std::cout << dict;
    }
    else if (command == "complement")
    {
      std::string new_name;
      std::string first_name;
      std::string second_name;
      std::cin >> new_name >> first_name >> second_name;
      variables[new_name] = variables.at(first_name).complement(variables.at(second_name));
    }
    else if (command == "intersect")
    {
      std::string new_name;
      std::string first_name;
      std::string second_name;
      std::cin >> new_name >> first_name >> second_name;
      Dictionary< long long, std::string, compareFunc > first_dict = variables[first_name];
      Dictionary< long long, std::string, compareFunc > second_dict = variables[second_name];
      if (first_dict.empty() || second_dict.empty())
      {
        throw std::runtime_error("<EMPTY>");
      }
      variables[new_name] = first_dict.intersect(second_dict);
    }
    else if (command == "union")
    {
      std::string new_name;
      std::string first_name;
      std::string second_name;
      std::cin >> new_name >> first_name >> second_name;
      variables[new_name] = variables.at(first_name).join(variables.at(second_name));
    }
  }
}

#endif
