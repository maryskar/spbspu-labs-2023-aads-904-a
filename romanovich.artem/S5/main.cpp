#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <parsing.h>
#include <printmessages.h>
#include "commands.h"
int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    std::cerr << "Invalid arguments number.\n";
    return 1;
  }
  std::ifstream input(argv[2]);
  if (!input)
  {
    std::cerr << "Cannot open file.\n";
    return 1;
  }
  romanovich::map_t mapData;
  std::string line;
  if (std::getline(input, line))
  {
    std::vector< std::string > lineWords;
    romanovich::splitString(lineWords, line, ' ');
    if (line.empty())
    {
      romanovich::printEmpty(std::cout) << "\n";
      return 0;
    }
    for (size_t i = 0; i < lineWords.size(); i += 2)
    {
      long long key = std::stoll(lineWords[i]);
      std::string val = lineWords[i + 1];
      mapData.emplace(romanovich::map_value_t(key, val));
    }
  }
  auto commandDictionary = romanovich::createCommandDictionary();
  try
  {
    std::string traversalType = argv[1];
    commandDictionary[traversalType](mapData);
  }
  catch (...)
  {
    std::cerr << "Error while performing traversal.";
    return 2;
  }
}
