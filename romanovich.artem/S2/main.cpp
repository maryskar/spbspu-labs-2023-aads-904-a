#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "commands.h"
void
printDictionary(const Dictionary< std::string, Dictionary< int, std::string > > &dictionary)
{
  for (const auto &entry: dictionary)
  {
    std::cout << entry.first;
    const auto &dictData = entry.second;
    for (const auto &item: dictData)
    {
      std::cout << " " << item.first << " " << item.second;
    }
    std::cout << "\n";
  }
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
  container_type dictionary;
  std::string line;
  while (std::getline(input, line))
  {
    std::vector< std::string > lineWords;
    splitString(lineWords, line, ' ');
    std::string dictName = lineWords[0];
    dict_type dictData;
    for (size_t i = 1; i < lineWords.size(); i += 2)
    {
      int key = std::stoi(lineWords[i]);
      std::string val = lineWords[i + 1];
      dictData.emplace(dict_value_type(key, val));
      dictData.emplace(dict_value_type(key, val));
    }
    dictionary.emplace(container_value_type(dictName, dictData));
  }
  auto commandDictionary = romanovich::createCommandDictionary(dictionary);
  while (std::cin)
  {
    std::string command;
    std::cin >> command;
    std::cout << command << ": ";
    commandDictionary[command];
  }
}
