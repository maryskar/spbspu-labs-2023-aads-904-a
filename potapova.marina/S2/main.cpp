#include <iostream>
#include <stdexcept>
#include <fstream>
#include "forwardList.h"
#include "dictionary.h"
#include "workWithIO.h"
#include "runCommands.h"

bool compareLongLong(const long long& first, const long long& second)
{
  return first > second;
}

bool compareString(const std::string& first, const std::string& second)
{
  return first.size() > second.size();
}

int main(int argc, char* argv[])
{
  using namespace potapova;
  std::ifstream input_file;
  if (argc > 2)
  {
    std::cerr << "Incorrect number of arguments\n";
    return 1;
  }
  else if (argc == 2)
  {
    input_file.open(argv[1]);
    if (!input_file.is_open())
    {
      std::cerr << "Failed to open file\n";
      return 1;
    }
  }
  else
  {
    std::cerr << "No file to open\n";
    return 1;
  }
  std::string name;
  VariablesT< compareLongLong, compareString > variables;
  std::string command;
  try
  {
    while (!input_file.eof())
    {
      input_file >> name;
      input_file >> variables[name];
    }
    while (std::cin >> command)
    {
      if (!runCommand(command, variables))
      {
        std::cout << "<INVALID COMMAND>";
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
