#include <iostream>
#include <fstream>
#include <string>
#include "callCommands.h"
#include "map.h"
#include "readDictsInDict.h"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cout << "Incorrect input\n";
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input.is_open())
  {
    std::cout << "File not found\n";
    return 1;
  }
  using dict_t = tarasenko::Map< size_t, std::string, std::less<> >;
  tarasenko::Map< std::string, dict_t, std::greater<> > dict_of_dict;
  readDictsInDict(input, dict_of_dict);
  std::string name_of_command = "";
  while (std::cin >> name_of_command)
  {
    try
    {
      call(name_of_command, dict_of_dict, std::cin, std::cout);
    }
    catch (const std::exception& e)
    {
      std::cout << e.what() << "\n";
      return 1;
    }
  }
}
