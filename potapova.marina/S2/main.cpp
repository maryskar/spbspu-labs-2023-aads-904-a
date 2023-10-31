#include <iostream>
#include <stdexcept>
#include <fstream>
#include "forwardList.h"
#include "dictionary.h"
#include "workWithIO.h"
#include "runCommands.h"

namespace
{
  bool int64Comp(const long long& first, const long long& second)
  {
    return first > second;
  }

  bool stringComp(const std::string& first, const std::string& second)
  {
    return first.size() > second.size();
  }
}

int main(const int argc, const char* argv[])
{
  using namespace potapova;
  if (argc != 2)
  {
    std::cerr << "Incorrect count of arguments\n";
    return 1;
  }
  std::ifstream input_file(argv[1]);
  if (!input_file.is_open())
  {
    std::cerr << "Failed to open file\n";
    return 1;
  }
  VariablesT<int64Comp, stringComp> variables;
  try
  {
    std::string name;
    while (input_file >> name)
    {
      if (!(input_file >> variables[name]))
      {
        std::cerr << "Incorrect data in file\n";
        return 1;
      }
    }
    std::string command;
    while (std::cin >> command)
    {
      if (!runCommand(command, variables))
      {
        std::cout << "<INVALID COMMAND>\n";
      }
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << '\n';
    return 1;
  }
  return 0;
}
