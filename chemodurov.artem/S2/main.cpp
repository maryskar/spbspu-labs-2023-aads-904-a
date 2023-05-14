#include <iostream>
#include <fstream>
#include <algorithm>
#include "read-dictionary-of-dictionary.hpp"
#include "read-and-do-command.hpp"

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
  auto command_dics = chemodurov::createCommandDictionary();
  using namespace std::placeholders;
  auto read = std::bind(chemodurov::readCommand, std::ref(std::cin));
  auto doComm = std::bind(chemodurov::doCommand, read, command_dics, _1, std::ref(std::cin), std::ref(std::cout));
  do
  {
    try
    {
      doComm(dictionaries);
    }
    catch (const std::logic_error & e)
    {
      chemodurov::outInvalidCommand(std::cout);
      std::cout << '\n';
      std::string line;
      std::getline(std::cin, line);
      continue;
    }
    catch (const std::runtime_error & e)
    {
      break;
    }
  }
  while (std::cin);
  return 0;
}
