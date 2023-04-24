#include <iostream>
#include <fstream>
#include <string>
#include "dictionary.h"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cout << "Incorrect input\n";
    return 1;
  }
  std::fstream input(argv[1]);
  if (!input.is_open())
  {
    std::cout << "File not found\n";
    return 1;
  }
  using dict_type = tarasenko::Dictionary< int, std::string, std::less<> >;
  tarasenko::Dictionary< std::string, dict_type, std::greater<> > dict_of_dict;
  while (input)
  {
    std::string name = "";
    while (input >> name)
    {
      size_t key;
      std::string value;
      dict_type dict;
      while(input >> key >> value)
      {
        dict.push(key, value);
      }
      dict_of_dict.push(name, dict);
      input.clear();
    }
  }
  std::string name = "second";
  std::cout << dict_of_dict.get(name) << "\n";
  return 0;
}
