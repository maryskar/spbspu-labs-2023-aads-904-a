#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "commands.h"
#include "../common/printmessages.h"//#include <printmessages.h>
void splitString(std::vector< std::string > &elems, const std::string &line, char del)
{
  std::string word;
  size_t startPos = 0;
  size_t endPos = line.find(del);
  while (endPos != std::string::npos)
  {
    word = line.substr(startPos, endPos - startPos);
    elems.push_back(word);
    startPos = endPos + 1;
    endPos = line.find(del, startPos);
  }
  word = line.substr(startPos, endPos);
  elems.push_back(word);
}
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
    splitString(lineWords, line, ' ');
    if (line.empty())
    {
      printEmpty(std::cout) << "\n";
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
    commandDictionary[traversalType](std::cout, mapData);
  }
  catch (...)
  {
    std::cerr << "Error while performing traversal.";
    return 2;
  }
}
