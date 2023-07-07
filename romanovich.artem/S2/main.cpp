#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "dict.h"
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
  using dict_type = Dictionary< int, std::string, std::less< int > >;
  using dict_value_type = std::pair< int, std::string >;
  using container_type = Dictionary< std::string, dict_type, std::less< std::string > >;
  using container_value_type = std::pair< std::string, dict_type >;
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
      std::cout << key << " " << val << "\n";
      dictData.emplace(dict_value_type(key, val));
    }
    dictionary.emplace(container_value_type(dictName, dictData));
    std::cout << "\n";
  }
  for (const auto &entry: dictionary)
  {
    std::cout << "Dictionary name: " << entry.first << "\n";
    const auto &dict = entry.second;
    for (const auto &item: dict)
    {
      std::cout << "Key: " << item.first << ", Value: " << item.second << "\n";
    }
    std::cout << "\n";
  }
}
