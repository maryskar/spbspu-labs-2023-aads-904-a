#include <iostream>
#include <string>
#include <dictionary.h>
#include <read_dicts_in_dict.h>
#include <commands.h>
#include <compare.h>

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
  using dict_t = tarasenko::Dictionary< size_t, std::string, tarasenko::Comp >;
  tarasenko::Dictionary< std::string, dict_t, std::greater<> > dict_of_dict;
  readDictsInDict(input, dict_of_dict);
  tarasenko::Commands< size_t , std::string, tarasenko::Comp > commands;
  std::string name_of_command = " ";
  while (std::cin >> name_of_command)
  {
    try
    {
      commands.call(name_of_command, dict_of_dict, std::cin, std::cout);
    }
    catch (const std::exception& e)
    {
      std::cout << e.what() << "\n";
      return 1;
    }
  }
}

