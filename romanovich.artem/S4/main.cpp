#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include "commands.h"
std::ostream &printError(std::ostream &out)
{
  return out << "<INVALID COMMAND>";
}
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
  constexpr auto maxLLSize = std::numeric_limits< std::streamsize >::max();
  if (argc != 2)
  {
    std::cerr << "No file provided.\n";
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input)
  {
    std::cerr << "Cannot open file.\n";
    return 1;
  }
  romanovich::container_t map;
  std::string line;
  while (std::getline(input, line))
  {
    std::vector< std::string > lineWords;
    splitString(lineWords, line, ' ');
    std::string mapName = lineWords[0];
    romanovich::map_t mapData;
    for (size_t i = 1; i < lineWords.size(); i += 2)
    {
      int key = std::stoi(lineWords[i]);
      std::string val = lineWords[i + 1];
      mapData.emplace(romanovich::map_value_t(key, val));
    }
    mapData.rotBst_.printNode(mapData.rotBst_.bst_.root_, true, "");
    std::cout << "---------\n";
    map.emplace(romanovich::container_value_t(mapName, mapData));
  }
  auto commandDictionary = romanovich::createCommandDictionary(map);
  while (std::cin)
  {
    std::string command;
    std::cin >> command;
    if (!std::cin)
    {
      break;
    }
    try
    {
      commandDictionary[command](std::cin, std::cout, map);
    }
    catch (...)
    {
      printError(std::cout) << '\n';
      std::cin.ignore(maxLLSize, '\n');
    }
  }
}
