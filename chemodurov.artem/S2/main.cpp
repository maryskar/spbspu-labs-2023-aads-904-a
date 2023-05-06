#include <iostream>
#include <fstream>
#include <algorithm>
#include "read-dictionary-of-dictionary.hpp"
#include "create-command-dictionary.hpp"

int main(int argc, char ** argv)
{
  if (argc != 2)
  {
    std::cerr << "There is no file in parameters\n";
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input.is_open())
  {
    std::cerr << "The file doesn't opened\n";
    return 1;
  }
  auto dictionaries = chemodurov::readDictionaryOfDictionary(input);
  auto command_dic = chemodurov::createCommandDictionary();
  return 0;
}
