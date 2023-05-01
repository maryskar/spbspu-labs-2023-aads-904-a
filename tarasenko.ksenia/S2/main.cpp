#include <iostream>
#include <fstream>
#include <string>
#include "commands.h"
#include "dictionary.h"

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
  if (!input.is_open())
  {
    std::cout << "File not found\n";
    return 1;
  }
  using dict_type = tarasenko::Dictionary< size_t, std::string, std::less<> >;
  tarasenko::Dictionary< std::string, dict_type, std::greater<> > dict_of_dict;
  while (input)
  {
    std::string name_of_dict = "";
    while (input >> name_of_dict)
    {
      size_t key;
      std::string value;
      dict_type dict;
      while (input >> key >> value)
      {
        dict.push(key, value);
      }
      dict_of_dict.push(name_of_dict, dict);
      input.clear();
    }
  }
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
