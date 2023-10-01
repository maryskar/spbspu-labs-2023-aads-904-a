#include "runCommands.h"
#include <iostream>
#include <string>
#include "workWithIO.h"
#include "dictionary.h"

namespace potapova
{
  template< bool (*compareFunc)(const long long&, const long long&), bool (*compareDict)(const std::string& first, const std::string& second) >
  void runCommand(std::string& command, Dictionary< std::string, Dictionary< long long, std::string, compareFunc >, compareDict > variables)
  {
    if (command == "print")
    {
      std::string name;
      std::cin >> name;
      std::cout << name << " " << variables[name] << '\n';
    }
    else if (command == "complement")
    {
      std::string new_name;
      std::string first_name;
      std::string second_name;
      std::cin >> new_name >> first_name >> second_name;
      variables.insert(new_name, variables.at(first_name).complement(variables.at(second_name)));
    }
    else if (command == "intersect")
    {
      std::string new_name;
      std::string first_name;
      std::string second_name;
      std::cin >> new_name >> first_name >> second_name;
      variables.insert(new_name, variables.at(first_name).intersect(variables.at(second_name)));
    }
    else if (command == "union")
    {
      std::string new_name;
      std::string first_name;
      std::string second_name;
      std::cin >> new_name >> first_name >> second_name;
      variables.insert(new_name, variables.at(first_name).join(variables.at(second_name)));
    }
  }
}
